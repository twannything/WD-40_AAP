﻿#pragma once
#include "Basic Operation.h"

#define ZERORIZE


/**
* @brief array_init : bi_delete 에 사용되는 함수 빅넘버 x의 메모리를 반납하기전 0으로 초기화
* @param word* a : 초기화 할 워드열
* @param wordlen : 초기화 할 워드열의 길이
*/

void array_init(word* a, int wordlen) {
	memset(a, 0x00, (wordlen * sizeof(word)));
}

/**
* @brief array_copy : 빅넘버 끼리 복사하는 bi_assign함수에 사용
* @param word* a : 복사할 워드열
* @param word* b : 복사당할 워드열
* @param int wordlen : 복사할 길이
*/
void array_copy(word* a, word* b, int wordlen) {
	for (unsigned int i = 0; i < wordlen * sizeof(word); i++)
		a[i] = b[i];
}
/**
* @brief array_rand : 배열에 랜덤값 입력 bi_gen_rand에 사용
* @param word* dst : 랜덤값을 넣을 문자열
* @param int wordlen : 입력받을 길이
*/
void array_rand(word* dst, int wordlen) {
	byte* p = (byte*)dst;
	int cnt = wordlen * sizeof(word);
	while (cnt > 0) {
		*p = rand() & 0xff;
		p++;
		cnt--;
	}
}
/**
* @brief bi_delete : 빅넘버 x에 할당했던 메모리를 반납하는 함수
* @param bigint** x : 반납할 빅넘버
*/
void bi_delete(bigint** x) {
	if (*x == NULL) return;

#ifdef ZERORIZE
	array_init((*x)->a, (*x)->wordlen);
#endif
	free((*x)->a);
	free(*x);
	*x = NULL;
}
/**
* @brief bi_new : 해당 wordlen 만큼 빅넘버 x의 메모리를 할당해주는 함수
* @param bigint** x : 메모리를 할당받을 빅넘버 x
* @param int wordlen : 할당받을 워드의 길이
*/
void bi_new(bigint** x, int wordlen) {
	if (*x != NULL)
		bi_delete(x);

	*x = (bigint*)malloc(sizeof(bigint));
	(*x)->sign = NONNEGATIVE;
	(*x)->wordlen = wordlen;
	(*x)->a = (word*)calloc(wordlen, sizeof(word));
}
/**
* @brief bi_set_by_array : 배열에 빅넘버 값이 있을 때, 배열을 x->a 배열에 대입시켜 주는 함수
* @param bigint** x : 값을 대입할 빅넘버 x
* @param int sign : x의 부호
* @param word* a : 대입할 빅넘버 배열
* @param int wordlen : x의 워드길이
*/
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen) {
	if (*x != NULL)
		bi_delete(x);
	bi_new(x, wordlen);
	(*x)->sign = sign;
	for (int i = 0, j = wordlen - 1; i < wordlen, j >= 0; i++, j--)
		(*x)->a[i] = a[j];
}
/**
* @brief bi_set_by_string : word 배열 즉, word 문자열에 빅넘버 값이 있을 때, 문자열을 x->a에 대입시켜주는 함수
* @param bigint** x :값을 대입할 빅넘버 x
* @param int sign :x의 부호
* @param char* str : 대입할 빅넘버 문자열
* @param word base :x의 워드길이
*/
void bi_set_by_string(bigint** x, int sign, char* str, word base) {
	if (*x != NULL)
		bi_delete(x);


}
/**
* @brief bi_show_hex : (*x)->a 값을 WOREBITLEN에 맞게 16진수 출력
* @param bigint* x : 출력한 빅넘버 x
*/
void bi_show_hex(bigint* x) {
	if (x->sign == NEGATIVE)
		printf("-0x");
	else
		printf("0x");
	for (int i = (x->wordlen - 1); i >= 0; i--) {
#if (WORD_BITLEN == 8)
		printf("%02x", x->a[i]);
#elif (WORD_BITLEN == 32)
		printf("%08x", x->a[i]);
#else
		printf("%16x", x->a[i]);
#endif
	}
	printf("\n");
}

//
//void bi_show_dec(bigint* x) {
//	for (int i = 0; i < x->wordlen; i++)
//}
/**
* @brief bi_show_bin : (*x)->a 값을 WOREBITLEN에 맞게 2진수 출력
* @param bigint* x : 출력한 빅넘버 x
*/
void bi_show_bin(bigint* x) {
	if (x->sign == NEGATIVE) printf("-0b");
	else printf("0b");
	for (int i = x->wordlen - 1; i >= 0; i--) {
		for (int j = WORD_BITLEN - 1; j >= 0; j--) {
			int mask = 1 << j;
			printf("%d", x->a[i] & mask ? 1 : 0);
		}
		//printf(" ");

	}
	//printf("\n");
}

/**
* @brief File_print : 파일에 빅넘버 값을 16진수로 출력할 때 사용되는 함수
* @param bigint* x : 출력한 빅넘버 x
* @param FILE* fp : 출력값을 적을 파일
*/
void File_print(bigint* x, FILE* fp) {


	if (x->sign == NEGATIVE)
		fprintf(fp, "-0x");
	else
		fprintf(fp, "0x");

	for (int i = (x->wordlen - 1); i >= 0; i--) {
#if (WORD_BITLEN == 8)
		fprintf(fp, "%02x", x->a[i]);
#elif (WORD_BITLEN == 32)
		fprintf(fp, "%08x", x->a[i]);
#else
		fprintf(fp, "%16x", x->a[i]);
#endif
	}
	fprintf(fp, "\n");
}
/**
* @brief bi_refine : x->a = 0x0000ffff 처럼 앞에 실질적으로 필요없는 메모리가 잡혀있을때 x->a = 0xffff로 줄여주는 함수
* @param bigint* x : refine 할 빅넘버 x
*/
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

	if ((x->wordlen == 1) && (x->a[0] == 0x0))
		x->sign = NONNEGATIVE;
}
/**
* @brief bi_assign : 빅넘버 y에 빅넘버x를 복사해주는 함수
* @param bigint** y : 복사한 값을 넣을 빅넘버 y
* @param bigint* x : 복사할 빅넘버 x
*/
void bi_assign(bigint** y, bigint* x) {
	if (*y != NULL)
		bi_delete(y);

	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	array_copy((*y)->a, x->a, x->wordlen);
}
/**
* @brief bi_gen_rand : 부호와 값이 랜덤한 빅넘버 x를 만들어 주는 함수
* @param bigint** x : 생성할 빅넘버 x
* @param int wordlen : 빅넘버 x의 워드 길이
*/
void bi_gen_rand(bigint** x, int sign, int wordlen) {
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}
/**
* @brief get_word_length : 빅넘버 x의 wordlen를 리턴
* @param bigint* x : 빅넘버 x
*/
int get_word_length(bigint* x) {
	return x->wordlen;
}
/**
 * @brief get_bit_length : 빅넘버 x의 비트길이를 리턴
 * @param bigint* x : 빅넘버 x
 * @return total
 */
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
/**
* @brief bit_of_bi : 빅넘버 x의 j번째 비트값을 리턴
* @param bigint* x :빅넘버 x
* @param int j : x의 j번째 비트를 표시
* @return (x->a[j_word] & mask) >> rem
*/
int bit_of_bi(bigint* x, int j) {
	int rem = j % WORD_BITLEN;
	int j_word = j / WORD_BITLEN;
	int mask = 1 << rem;

	return (x->a[j_word] & mask) >> rem;
}
/**
* @brief get_sign_bi : x의 부호 리턴
* @param bigint* x : 빅넘버 x
* @return NEGATIVE or NONNEGATIVE
*/
int get_sign_bi(bigint* x) {
	return x->sign;
}


/**
* @brief flip_sign_bi : x의 부호 반대처리하는 함수
* @param bigint** x : 빅넘버 x
*/

void flip_sign_bi(bigint** x) {
	if ((*x)->sign == NONNEGATIVE)
		(*x)->sign = NEGATIVE;
	else (*x)->sign = NONNEGATIVE;
}
/**
* @brief bi_set_one : x를 1로 바꿔주는 함수
* @param bigint** x : 빅넘버 x
*/
void bi_set_one(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NONNEGATIVE;
	(*x)->a[0] = 0x1;
}
/**
* @brief bi_set_zero : x를 0으로 바꿔주는 함수
* @param : bigint** x : 빅넘버 x
*/
void bi_set_zero(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NONNEGATIVE;
	(*x)->a[0] = 0x0;
}
/**
* @brief bi_is_zero : x가 0인지 확인하는 함수: x가 0이면 1을 리턴
* @param bigint* x :빅넘버 x
* @return 0 or 1
*/
int bi_is_zero(bigint* x) {
	if (x->sign == NEGATIVE || x->a[0] != 0) return 0;
	else {
		for (int j = x->wordlen - 1; j > 0; j--)
			if (x->a[j] != 0) return 0;
	}
	return 1;
}
/**
* @brief bi_is_one : x가 1지 확인하는 함수: x가 1이면 1을 리턴
* @param bigint* x : 빅넘버 x
* @return 0 or 1
*/
int bi_is_one(bigint* x) {
	if (x->sign == NEGATIVE || x->a[0] != 1) return 0;
	else {
		for (int j = x->wordlen - 1; j > 0; j--)
			if (x->a[j] != 0) return 0;
	}
	return 1;
}
/**
* @brief compareABS : x 와 y의 절대값크기 비교 : x가 크면 1, 작으면 -1, 같으면 0을 리턴
* @param bigint* x : 빅넘버 x
* @param bigint* y : 빅넘버 y
* @return -1 , 0, 1
*/
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
/**
* @brief compareAB : x와 y의 크기 비교 : x가 크면 1, 작으면 -1, 같으면 0을 리턴
* @param bigint* x : 빅넘버 x
* @param bigint* y : 빅넘버 y
* @return -1, 0, 1
*/
int compareAB(bigint* x, bigint* y)
{
	int ret;

	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) return -1;
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) return 1;

	ret = compareABS(x, y);
	if (get_sign_bi(x) == NONNEGATIVE) return ret;
	else return ret - 1;

}

/**
* @brief bi_leftshift : x를 r비트만큼 leftShift 해주는 함수
* @param bigint** x : 빅넘버 x
* @param int r : leftShift 횟수
*/
void bi_leftshift(bigint** x, int r)
{
	int k, rp, a;
	k = r / WORD_BITLEN;
	rp = r % WORD_BITLEN;
	word tmp = 0;
	word ttmp = 0;

	if (r % WORD_BITLEN == 0) 
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

/**
* @brief bi_rightshift : x를 r비트만큼  rightShift 해주는 함수
* @param bigint** x : 빅넘버 x
* @param int r : rightShift 횟수
*/
void bi_rightshift(bigint** x, int r)
{
	int i, j, k, rp, a;
	k = r / WORD_BITLEN;
	rp = r % WORD_BITLEN;

	a = (*x)->wordlen;

	if (k >= (*x)->wordlen)
		for (i = 0; i < a; i++)
			(*x)->a[i] = 0x00;

	if (r % WORD_BITLEN == 0)
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


