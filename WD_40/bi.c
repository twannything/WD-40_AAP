#pragma once
#include "bi.h"

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

/**
* @brief bi_show_bin : (*x)->a 값을 WOREBITLEN에 맞게 2진수 출력
* @param bigint* x : 출력한 빅넘버 x
*/
void bi_show_bin(bigint* x) {
	for (int i = x->wordlen - 1; i >= 0; i--) {
		for (int j = WORD_BITLEN - 1; j >= 0; j--) {
			int mask = 1 << j;
			printf("%d", x->a[i] & mask ? 1 : 0);
		}
		printf(" ");

	}
	printf("\n");
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

	if ((x->wordlen == 1) && (x->a[0] == 0x00))
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
void bi_gen_rand(bigint** x, int wordlen) {
	bi_new(x, wordlen);
	(*x)->sign = rand() % 2;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}
/**
* @brief get_word_length : 빅넘버 x의 wordlen를 리턴
* @param bigint* x : 빅넘버 x
*/
int get_word_length(bigint* x) {
	return x->wordlen;
}/**
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

	ret = compareABS(x, y); // 둘다 양수이거나 둘다 음수 1 0 -1
	if (get_sign_bi(x) == NONNEGATIVE) return ret;
	else return ret * (-1);

}

/**
* @brief bi_leftshift : x를 r비트만큼 leftShift 해주는 함수
* @param bigint** x : 빅넘버 x
* @param int r : leftShift 횟수
*/
void bi_leftshift(bigint** x, int r)
{
	int k, rp, a = 0;
	k = r / WORD_BITLEN;
	rp = r % WORD_BITLEN;
	word tmp = 0;
	word ttmp = 0;

	if (r % WORD_BITLEN == 0) // 
	{
		a = (*x)->wordlen;
		(*x)->wordlen += k;
		(*x)->a = (word*)realloc((*x)->a, (*x)->wordlen * sizeof(word));
		for (int i = a - 1; i >= 0; i--)
			(*x)->a[i + k] = (*x)->a[i];

		for (int i = 0; i < k; i++)
			(*x)->a[i] = 0x00;

	}
	else {
		a = (*x)->wordlen;
		(*x)->wordlen += 1 + k;
		(*x)->a = (word*)realloc((*x)->a, (*x)->wordlen * sizeof(word));
		tmp = (*x)->a[0];
		(*x)->a[0] = ((*x)->a[0]) << rp;
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

	if (r % WORD_BITLEN == 0) // 
	{
		for (i = 0; i < a - k; i++)
			(*x)->a[i] = ((*x)->a[k + i]);
		for (j = i; j < a; j++)
			(*x)->a[j] = 0x00;
	}
	else {
		for (int i = 0; i < a - k - 1; i++)
			(*x)->a[i] = ((*x)->a[i + 1] >> rp) ^ ((*x)->a[i + 2] << (WORD_BITLEN - rp));
		(*x)->a[a - k - 1] = ((*x)->a[a - k] >> rp);
		for (int i = a - k; i < a; i++)
			(*x)->a[i] = 0x00;
	}
}

/**
* @brief bi_reduction : y를 x의 r승 modular 연산 취해주는 함수
* @param bigint** y : 빅넘버 y
* @param bigint* x : 빅넘버 x
* @param int r : x의 지수
*/
void bi_reduction(bigint** y, bigint* x, int r) {
	{
		int k = r / WORD_BITLEN;
		int rem = r % WORD_BITLEN;
		if (r > x->wordlen * WORD_BITLEN) {
			bi_assign(y, x); return;
		}
		else if (rem == 0) {
			bi_new(y, k);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((1 << WORD_BITLEN) - 1); return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((1 << WORD_BITLEN) - 1);
			}
			(*y)->a[k] = x->a[k] & ((1 << rem) - 1);
			return;
		}
	}
}
/**
* @brief S_ADDABc : 한 워드 끼리의 덧셈 연산후 carry값 = d를 리턴하는 함수
* @param word x : 더하고자하는 워드
* @param word y : 더하고자하는 워드
* @param bigint** z : 더한값을 저장할 빅넘버
* @param int carry : 이전 연산에서 발생한 carry
* @param int r : 더한 값을 z의 r번째 배열에 저장
* return d (carry 값)
*/
int S_ADDABc(word x, word y, bigint** z, int carry, int r) {

	int d = 0;

	(*z)->a[r] = (x + y) & MASK;
	if ((*z)->a[r] < x) d = 1;

	(*z)->a[r] = ((*z)->a[r] + carry);
	if ((*z)->a[r] < carry) d = 1;

	return d;
}

/**
* @brief M_ADD : 길이가 2이상인 두 빅넘버 x,y를 더하는 함수 x의 wordlen이 항상 y의 wordlen 이상이라고 가정
* @param bigint* x : 더하고자하는 빅넘버 x
* @param bigint* y : 더하고자하는 빅넘버 y
* @param bigint** z: 더한값을 저장할 빅넘버 z (z->wordlen = max(x->wordlen, y->wordlen) + 1)
*/
void M_ADD(bigint* x, bigint* y, bigint** z) {
	int c = 0;

	if (*z == NULL) bi_new(z, (x->wordlen + 1));


	if (x->wordlen > y->wordlen)
		for (int i = y->wordlen; i < x->wordlen; i++)
			y->a[i] = 0;

	c = 0;

	for (int i = 0; i < x->wordlen; i++)
		c = S_ADDABc(x->a[i], y->a[i], z, c, i);

	(*z)->a[x->wordlen] = c;

	if ((*z)->a[x->wordlen] == 0) bi_refine(*z);
}

/**
* @brief ADD : 덧셈에서 사용되는 모든 경우를 처리하는 함수
* @param bigint* x : 더하고자하는 빅넘버 x
* @param bigint* y : 더하고자하는 빅넘버 y
* @param bigint** z : 더한 값을 저장할 빅넘버 z
*/
void ADD(bigint* x, bigint* y, bigint** z) {


	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		return;
	}
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB(x, y, z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB(y, x, z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		if (x->wordlen >= y->wordlen) {
			M_ADD(x, y, z);
			flip_sign_bi(z);
			return;
		}
		else {
			M_ADD(y, x, z);
			flip_sign_bi(z);
			return;
		}
	}
	if (x->wordlen >= y->wordlen) {
		M_ADD(x, y, z);
		return;
	}
	else {
		M_ADD(y, x, z);
		return;
	}
}

/**
* @brief S_SUBABb : 한 워드간의 뺄셈연산하는 함수 borrow 값을 리턴
* @param bigint* x : 빼고자하는 빅넘버 x
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
* @param int b : 이전 borrow 값
* @param int j : 뺀 값을 z의 j번째 배열에 저장
* @return b (borrow 값)
*/
int S_SUBABb(bigint* x, bigint* y, bigint** z, int b, int j) {

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;

	(*z)->a[j] -= y->a[j];
	return b;
}
/**
* @brief SUB_C : 길이가 2이상인 두 빅넘버 x,y를 빼는 함수 x의 wordlen이 항상 y의 wordlen 이상이라고 가정
* @param bigint* x : 빼고자하는 빅넘버 x
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
*/
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

/**
* @brief SUB : 뺄셈에서 사용되는 모든 경우를 처리하는 함수
* @param bigint* x : 빼고자하는 빅넘버 x
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
*/
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
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	else if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) == -1) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	else {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&y);
		return;
	}
}
/**
* @brief MULC : 한 워드간의 곱셈(x의 i번째 워드 * y의 j번째 워드)을 처리하는 함수
* @param bigint* x : 곱하고자하는 빅넘버 x
* @param bigint* y : 곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저정할 빅넘버 z
* @param int i : x의 i번째 word를 나타낼 정수 i
* @param int j : y의 j번째 word를 나타낼 정수 j
*/
void MULC(bigint* x, bigint* y, bigint** z, int i, int j) {

	word a0, a1, b0, b1, c0, c1, t0, t1, t, a = 1;

	a0 = x->a[i] & ((a << (WORD_BITLEN / 2)) - 1);
	a1 = x->a[i] >> (WORD_BITLEN / 2);
	b0 = y->a[j] & ((a << (WORD_BITLEN / 2)) - 1);
	b1 = y->a[j] >> (WORD_BITLEN / 2);
	t0 = a1 * b0;
	t1 = a0 * b1;
	t0 = (t0 + t1) & ((a << WORD_BITLEN) - 1);
	t1 = t0 < t1;


	c0 = a0 * b0;
	c1 = a1 * b1;
	t = c0;
	c0 = ((c0 + (t0 << (WORD_BITLEN / 2))) & ((a << WORD_BITLEN) - 1));

	c1 = c1 + (t1 << (WORD_BITLEN / 2)) + (t0 >> (WORD_BITLEN / 2)) + (c0 < t);
	(*z)->a[0] = c0;
	(*z)->a[1] = c1;
}
/**
* @brief MUL : 곱셈에서 사용되는 모든 경우를 처리하는 함수
* @param bigint* x :곱하고자하는 빅넘버 x
* @param bigint* y :곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void MUL(bigint* x, bigint* y, bigint** z) {

	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) {
		bi_set_zero(z);
		return;
	}

	if (bi_is_one(x) == 1) {
		bi_assign(z, y);
		return;
	}

	if (bi_is_one(x) == 1 && get_sign_bi(x) == NEGATIVE) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}

	if (bi_is_one(y) == 1) {
		bi_assign(z, x);
		return;
	}

	if (bi_is_one(y) == 1 && get_sign_bi(y) == NEGATIVE) {
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	Schoolbook_MUL(x, y, z);
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		(*z)->sign = NONNEGATIVE;
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		(*z)->sign = NONNEGATIVE;
		return;
	}
	else {
		(*z)->sign = NEGATIVE;
		return;
	}
}
/**
* @brief Schoolbook_MUL : 길이가 2이상인 두 빅넘버 x , y를 곱하는 함수
* @param bigint* x : 곱하고자하는 빅넘버 x
* @param bigint* y : 곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {

	int i, j, k, c = 0;
	int len_short = 0; int len_long = 0;
	bigint* tmp = NULL;


	bi_new(&tmp, 2);
	bi_new(z, (x->wordlen + y->wordlen));

	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len_long + 1));

	for (i = 0; i < x->wordlen; i++) {
		for (j = 0; j < y->wordlen; j++) {
			MULC(x, y, &tmp, j, i);

			tmp_arr[j] += c;
			c = (tmp_arr[j] < c);

			tmp_arr[j] += tmp->a[0];
			c += (tmp_arr[j] < tmp->a[0]);

			tmp_arr[j + 1] += c;
			c = (tmp_arr[j + 1] < c);

			tmp_arr[j + 1] += tmp->a[1];
			c += (tmp_arr[j + 1] < tmp->a[1]);
		}
		c = 0;
		for (k = 0; k < len_long + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);

			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, len_long + 1);
	}
	free(tmp);
}
/**
* @brief karatsuba_MUL : 길이가 2이상인 두 빅넘버 x , y를 곱하는 함수
* @param bigint* x : 곱하고자하는 빅넘버 x
* @param bigint* y : 곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void karatsuba_MUL(bigint* x, bigint* y, bigint** z) {

	int flag = 0, m;
	m = min(x->wordlen, y->wordlen);

	if (flag >= m) {
		Schoolbook_MUL(x, y, z);
		return;
	}
	int l = 0;

	l = (
		max(x->wordlen, y->wordlen) + 1) >> 1;

	bigint* a0 = NULL;
	bigint* a1 = NULL;
	bigint* b0 = NULL;
	bigint* b1 = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;
	bigint* s0 = NULL;
	bigint* s1 = NULL;
	bigint* R = NULL;
	bigint* S = NULL;
	bigint* tmp = NULL;

	bi_new(&a0, (l / 2));
	bi_new(&a1, (l / 2));
	bi_new(&b0, (l / 2));
	bi_new(&b1, (l / 2));
	bi_new(&t0, l);
	bi_new(&t1, l);
	bi_new(&s0, l);
	bi_new(&s1, l);
	bi_new(&R, (2 * l));
	bi_new(&S, (2 * l));
	bi_new(z, (x->wordlen + y->wordlen));


	for (int i = 0; i < (l / 2); i++) {
		a0->a[i] = x->a[i];
		b0->a[i] = y->a[i];
	}

	for (int i = 0; i < (l / 2); i++) {
		a1->a[i] = x->a[(l / 2) + i];
		b1->a[i] = y->a[(l / 2) + i];
	}

	karatsuba_MUL(a0, b0, &t0);
	karatsuba_MUL(a1, b1, &t1);
	for (int i = 0; i < R->wordlen; i++) {
		if (i < R->wordlen)
			R->a[i] = t0->a[i];
		else
			R->a[i] = t1->a[i - (R->wordlen / 2)];
	}

	SUB(b1, b0, &s0);
	SUB(a0, a1, &s1);

	if (s0->sign == NEGATIVE)
		flip_sign_bi(&s0);
	if (s1->sign == NEGATIVE)
		flip_sign_bi(&s1);
	karatsuba_MUL(s0, s1, &S);
	if (bi_is_zero(s0) == 1 || bi_is_zero(s1) == 1)
		S->sign = NONNEGATIVE;
	else
		S->sign = s0->sign ^ s1->sign;

	ADD(S, t1, &S);
	ADD(S, t0, &S);
	bi_leftshift(&S, l);
	ADD(*z, S, z);


	bi_delete(&a0);
	bi_delete(&a1);
	bi_delete(&b0);
	bi_delete(&b1);
	bi_delete(&t0);
	bi_delete(&t1);
	bi_delete(&s0);
	bi_delete(&s1);
	bi_delete(&R);
	bi_delete(&S);

	free(a0);
	free(a1);
	free(b0);
	free(b1);
	free(t0);
	free(t1);
	free(s0);
	free(s1);
	free(R);
	free(S);
}

void Squaring_word(word* dst, word a) {

	word a0 = a & MASK;
	word a1 = a >> (sizeof(word) * 4);
	word s0 = (a1 * a0) << (sizeof(word) * 4);
	word s1 = (a1 * a0) >> (sizeof(word) * 4);

	dst[0] += s0;
	dst[1] += s1;
	if (dst[0] < s0)
		dst[1] += 1;

	dst[0] += s0;
	dst[1] += s1;
	if (dst[0] < s0)
		dst[1] += 1;
}

void Squaring_Karatsuba(bigint* x, bigint** z) {

	if (*z != NULL)
		bi_delete(z);

	*z = (bigint*)malloc(sizeof(bigint));

	if (x->wordlen == 1) {
		bi_new(z, 2);
		word dst[2] = { 0, };
		Squaring_word(dst, *(x->a));
		(*z)->a[0] = dst[0];
		(*z)->a[1] = dst[1];
	}
	else {
		bigint* a1 = NULL;
		bigint* a0 = NULL;

	}


}
/**
* @date 2020-11-23 01:49
*/