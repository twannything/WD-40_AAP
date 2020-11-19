#pragma once
#include "Basic Operation.h"

#define ZERORIZE


void array_init(word* a, int wordlen) {
	memset(a, 0x00, (wordlen * sizeof(word)));
}

void array_copy(word* a, word* b, int wordlen) {
	for (unsigned int i = 0; i < wordlen * sizeof(word); i++)
		a[i] = b[i];
}

void array_rand(word* dst, int wordlen) {
	byte* p = (byte*)dst;
	int cnt = wordlen * sizeof(word);
	while (cnt > 0) {
		*p = rand() & 0xff;
		p++;
		cnt--;
	}
}

void bi_delete(bigint** x) {
	if (*x == NULL) return;

#ifdef ZERORIZE
	array_init((*x)->a, (*x)->wordlen);
#endif
	free((*x)->a);
	free(*x);
	*x = NULL;
}

void bi_new(bigint** x, int wordlen) {
	if (*x != NULL)
		bi_delete(x);

	*x = (bigint*)malloc(sizeof(bigint));
	(*x)->sign = NONNEGATIVE;
	(*x)->wordlen = wordlen;
	(*x)->a = (word*)calloc(wordlen, sizeof(word));
}

void bi_set_by_array(bigint** x, int sign, word* a, int wordlen) {
	if (*x != NULL)
		bi_delete(x);
	bi_new(x, wordlen);
	(*x)->sign = sign;
	for (int i = 0, j = wordlen - 1; i < wordlen, j >= 0; i++, j--)
		(*x)->a[i] = a[j];
}

void bi_set_by_string(bigint** x, int sign, char* str, word base) {
	if (*x != NULL)
		bi_delete(x);


}

void bi_show_hex(bigint* x) {
	if (x->sign == NEGATIVE) printf("-");
	for (int i = x->wordlen - 1; i >= 0; i--) printf("%02x ", x->a[i]);
	printf("\n");
}
//
//void bi_show_dec(bigint* x) {
//	for (int i = 0; i < x->wordlen; i++)
//}

void bi_show_bin(bigint* x) {
	if (x->sign == NEGATIVE) printf("-");
	for (int i = x->wordlen - 1; i >= 0; i--) {
		for (int j = WORD_BITLEN - 1; j >= 0; j--) {
			int mask = 1 << j;
			printf("%d", x->a[i] & mask ? 1 : 0);
		}
		printf(" ");

	}
	printf("\n");
}

void bi_refine(bigint* x) {
	if (x == NULL)
		return;

	int new_wordlen = x->wordlen;
	while (new_wordlen > 1) {
		if (x->a[new_wordlen - 1] != 0)
			break;
		new_wordlen--;
	}

	if (x->wordlen != new_wordlen) {

		x->wordlen = new_wordlen;
		x->a = (word*)realloc(x->a, sizeof(word) * new_wordlen);
	}

	if ((x->wordlen == 1) && (x->a[0] = 0x0))
		x->sign = NONNEGATIVE;
}

void bi_assign(bigint** y, bigint* x) {
	if (*y != NULL)
		bi_delete(y);

	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	array_copy((*y)->a, x->a, x->wordlen);
}

void bi_gen_rand(bigint** x, int sign, int wordlen) {
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}

int get_word_length(bigint* x) {
	return x->wordlen;
}
int get_bit_length(bigint* x) {
	int total = x->wordlen * WORD_BITLEN;
	int mask = 1;

	for (int j = WORD_BITLEN - 1; j > 0; j--) {
		mask = 1 << j;
		if ((x->a[x->wordlen - 1] & mask) >> j == 0) {
			total--;
		}
		else return total;
	}
	return total;
}

int bit_of_bi(bigint* x, int j) {
	int rem = j % WORD_BITLEN;
	int j_word = j / WORD_BITLEN;
	int mask = 1 << rem;

	return (x->a[j_word] & mask) >> rem;
}

int get_sign_bi(bigint* x) {
	return x->sign;
}
void flip_sign_bi(bigint** x) {
	if ((*x)->sign == NONNEGATIVE)
		(*x)->sign = NEGATIVE;
	else (*x)->sign = NONNEGATIVE;
}

void bi_set_one(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NONNEGATIVE;
	(*x)->a[0] = 0x1;
}
void bi_set_zero(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NONNEGATIVE;
	(*x)->a[0] = 0x0;

}
int bi_is_zero(bigint* x) {
	if (x->sign == NEGATIVE || x->a[0] != 0) return 0;
	else {
		for (int j = x->wordlen - 1; j > 0; j--)
			if (x->a[j] != 0) return 0;
	}
	return 1;
}
int bi_is_one(bigint* x) {
	if (x->sign == NEGATIVE || x->a[0] != 1) return 0;
	else {
		for (int j = x->wordlen - 1; j > 0; j--)
			if (x->a[j] != 0) return 0;
	}
	return 1;
}

int compareABS(bigint* x, bigint* y)
{
	int i, n, m;
	n = x->wordlen;
	m = y->wordlen;

	if (n > m) return 1;
	else if (n < m) return -1;
	else if (n == m) {
		for (i = n - 1; i >= 0; i--)
		{
			if (x->a[i] > y->a[i]) return 1;
			else if (x->a[i] < y->a[i]) return -1;
		}
	}
	return 0;
}

int compareAB(bigint* x, bigint* y)
{
	int ret;

	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) return -1;
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) return 1;

	ret = compareABS(x, y);
	if (get_sign_bi(x) == NONNEGATIVE) return ret;
	else return ret - 1;

}


void bi_leftshift(bigint** x, int r)
{
	int k, rp, a;
	k = r / WORD_BITLEN;
	rp = r % WORD_BITLEN;
	word tmp = 0;
	word ttmp = 0;

	if (r % WORD_BITLEN == 0) // r�� W�� ����� ��
	{
		a = (*x)->wordlen;
		(*x)->wordlen += k;
		(*x)->a=(word*)realloc((*x)->a, (*x)->wordlen * sizeof(word));
		for (int i = a - 1; i >= 0; i--)
			(*x)->a[i + k] = (*x)->a[i];
		for (int j = 0; j < k; j++)
			(*x)->a[j] = 0x00;

	}
	else {
		a = (*x)->wordlen;
		(*x)->wordlen += 1 + k;
		(*x)->a = (word*)realloc((*x)->a, (*x)->wordlen * sizeof(word));
		tmp = (*x)->a[0];
		(*x)->a[0] = (*x)->a[0] << rp;
		for (int i = 1; i < a; i++) {
			ttmp = (*x)->a[i];
			(*x)->a[i] = ((*x)->a[i] << rp) ^ (tmp >> (WORD_BITLEN - rp));
			tmp = ttmp;
			ttmp = (*x)->a[i + 1];
		}
		(*x)->a[a] = tmp >> (WORD_BITLEN - rp);
		for (int i = a + 1; i >= 0; i--)
			(*x)->a[i + k] = (*x)->a[i];
		for (int j = 0; j < k; j++)
			(*x)->a[j] = 0x00;
	}
	bi_refine(*x);

}


void bi_rightshift(bigint** x, int r)
{
	int i, j, k, rp, a;
	k = r / WORD_BITLEN;
	rp = r % WORD_BITLEN;

	a = (*x)->wordlen;

	if (k >= (*x)->wordlen)
		for (i = 0; i < a; i++)
			(*x)->a[i] = 0x00;

	if (r % WORD_BITLEN == 0) // r�� W�� ����� ��
	{
		for (i = 0; i < a - k; i++)
			(*x)->a[i] = ((*x)->a[k + i]);
		for (j = i; j < a; j++)
			(*x)->a[j] = 0x00;
	}
	else {
		for (int i = 0; i < a - k - 1; i++)
			(*x)->a[i] = ((*x)->a[i + k] >> rp) ^ ((*x)->a[i + k + 1] << (WORD_BITLEN-rp));
		(*x)->a[a - k - 1] = (*x)->a[a - k-2] >> rp;
		for (int i = a - k; i < a; i++)
			(*x)->a[i] = 0x00;
	}
	//bi_refine(*x);
}


