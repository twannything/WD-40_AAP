#pragma once
#include "bi.h"

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

}
//
//void bi_show_dec(bigint* x) {
//	for (int i = 0; i < x->wordlen; i++)
//}

void bi_show_bin(bigint* x) {
	for (int i = x->wordlen-1; i >=0; i--){
		for (int j = WORD_BITLEN-1; j >= 0; j--) {
			int mask = 1 << j;
			printf("%d", x->a[i] & mask ? 1:0);
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

	if ((x -> wordlen == 1) && (x->a[0] = 0x0))
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
		if ((x->a[x->wordlen-1] & mask) >> j == 0) {
			total--;
		}
		else return total;
	}
	return;
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


void bi_leftshift(bigint** x, int r, word* aa, int wordlen)
{
	int i, j, k, rp, a, W;
	W = WORD_BITLEN;
	k = r / W;
	rp = r % W;

	if (r % W == 0) // r이 W의 배수일 때
	{
		(*x)->wordlen = wordlen + k;
		a = (*x)->wordlen;
		(*x)->a = (word*)realloc(aa, (a * sizeof(word)));

		for (int i = a - 1; i >= 0; i--)
			(*x)->a[i + k] = (*x)->a[i];
		for (j = 0; j < k; j++)
			(*x)->a[j] = 0x00;
	}
	else {
		(*x)->wordlen = wordlen + 1 + k;
		a = (*x)->wordlen;
		(*x)->a = (word*)realloc(aa, (a * sizeof(word)));

		(*x)->a[rp - 1] = (*x)->a[0];
		(*x)->a[a - 1] = (*x)->a[a - rp];
		for (i = 1; i < a; i++) {
			(((*x)->a[i]) << rp) || (((*x)->a[i - 1]) >> W - rp);
		}
	}
}


void bi_rightshift(bigint** x, int r, word* aa, int wordlen)
{
	int i, j, k, rp, a, W;
	W = WORD_BITLEN;
	k = r / W;
	rp = r % W;

	a = (*x)->wordlen;

	if (k >= a)
		for (i = 0; i < a; i++)
			(*x)->a[i] = 0x00;

	if (r % W == 0) // r이 W의 배수일 때
	{
		for (i = 0; i < a - k; i++)
			(*x)->a[i] = ((*x)->a[k + i]);
		for (j = i; j < a; j++)
			(*x)->a[j] = 0x00;
	}
	else {
		for (i = 0; i < a - k; i++)
			(*x)->a[i] = ((*x)->a[k + i]); // i = n-k
		for (j = i; j < a; j++)
			(*x)->a[j] = 0x00;
		for (j = 0; j < i - 1; j++) {
			(*x)->a[j] = ((*x)->a[j + 1] << (W - rp)) || ((*x)->a[j] >> rp);
		}
		(*x)->a[i - 1] = ((*x)->a[i - 1] >> rp);
	}
}

void bi_reduction(bigint** y , bigint* x, int r) {
	{
		word a = 1;
		int k = r / WORD_BITLEN;
		int rem = r % WORD_BITLEN;
		if (r > x->wordlen * WORD_BITLEN) {
			bi_assign(y, x); return;
		}
		else if (rem == 0) {
			bi_new(y, k);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((a << WORD_BITLEN) - 1); return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((a << WORD_BITLEN) - 1);
			}
			(*y)->a[k] = x->a[k] & ((a << rem) - 1);
			return;
		}
	}
}

int S_ADDABc(bigint* x, bigint* y, bigint** z,int carry, int r) {
	
	int d = 0;
	 
	if (r >= 1)
		if ((*z)->a[r - 1] < x->a[r - 1]) carry = 1;
		

	(*z)->a[r] = (x->a[r] + y->a[r]) & ((1 << WORD_BITLEN) - 1);
	if ((*z)->a[r] < x->a[r]) d = 1;
	
	(*z)->a[r] = ((*z)->a[r] + carry);

	if ((*z)->a[r] < carry) d = 1;
	
	return d;
}

void M_ADD(bigint* x, bigint* y, bigint** z) {
	int a, b, c, d = 0;
	a = x->wordlen;
	b = y->wordlen;

	bi_new(z, (a + 1));


	for (int i = b; i < a; i++)
		y->a[i] = 0;
	c = 0;

	for (int i = 0; i < a; i++)
		c = S_ADDABc(x, y, z, c, i);


	(*z)->a[a] = c;

	if ((*z)->a[a] == 0) bi_refine(*z);
}

int S_SUBABb(bigint* x, bigint* y, bigint** z, int b, int j) {

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;

	(*z)->a[j] -= y->a[j];
	return b;
}



void SUB_C(bigint* x, bigint* y, bigint** z) {
	bi_new(z, x->wordlen);

	for (int i = y->wordlen; i < (*z)->wordlen; i++)
		(*z)->a[i] = 0;
	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb(x, y, z, b, j);
	}
	bi_refine(*z);
}

void ADD(bigint* x, bigint* y, bigint** z) {
	int a, b;

	a = x->wordlen;
	b = y->wordlen;

	if (bi_is_zero(x) == 1) bi_assign(z, x);
	if (bi_is_zero(y) == 1) bi_assign(z, y);
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB_C(x, y, z);
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB_C(y, x, z);
	}
	if (a >= b) M_ADD(x, y, z);
	else M_ADD(y, x, z);
}

void SUB(bigint* x, bigint* y, bigint** z) {
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		SUB_C(x, y, z);
		return;
	}
	else {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(y, x, z);
		return;
	}
	else {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(x, y, z);
		flip_sign_bi(z);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		return;
	}
	else {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(z);
		return;
	}
}









