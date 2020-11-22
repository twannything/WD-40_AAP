﻿#pragma once
#include "Arithmetic.h"
#include "Basic Operation.h"

/**
* @brief bi_reduction : y를 x의 r승 modular 연산 취해주는 함수
* @param bigint** y : 빅넘버 y
* @param bigint* x : 빅넘버 x
* @param int r : x의 지수
*/
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
				(*y)->a[i] = x->a[i] & (((long long)a << WORD_BITLEN) - 1); return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & (((long long)a << WORD_BITLEN) - 1);
			}
			(*y)->a[k] = x->a[k] & ((a << rem) - 1);
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
int S_ADDABc(bigint* x, bigint* y, bigint** z,int carry, int r) {
	
	int d = 0;
	 
	if (r >= 1)
		if ((*z)->a[r - 1] < x->a[r - 1]) carry = 1;
		

	(*z)->a[r] = (x->a[r] + y->a[r]) & (((long long)1 << WORD_BITLEN) - 1);
	if ((*z)->a[r] < x->a[r]) d = 1;
	
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
	if(j<y->wordlen)
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
* @brief ADD : 덧셈에서 사용되는 모든 경우를 처리하는 함수
* @param bigint* x : 더하고자하는 빅넘버 x
* @param bigint* y : 더하고자하는 빅넘버 y
* @param bigint** z : 더한 값을 저장할 빅넘버 z
*/
void ADD(bigint* x, bigint* y, bigint** z) {
	int a, b;

	a = x->wordlen;
	b = y->wordlen;

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
		flip_sign_bi(&y);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB(y, x, z);
		flip_sign_bi(&x);
		return;
	}
	if (a >= b) {
		M_ADD(x, y, z);
		return;
	}
	else {
		M_ADD(y, x, z);
		return;
	}
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
	else if(get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) ==-1) {
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
	else if(get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) ==-1) {
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
	t0 = (t0 + t1) & (((long long)a << WORD_BITLEN) - 1);
	t1 = t0 < t1;


	c0 = a0 * b0;
	c1 = a1 * b1;
	t = c0;
	c0 = ((c0 + (t0 << (WORD_BITLEN / 2))) & (((long long)a << WORD_BITLEN) - 1));
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

	if (bi_is_one(x) == 1 && get_sign_bi(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}

	if (bi_is_one(y) == 1) {
		bi_assign(z, x);
		return;
	}

	if (bi_is_one(y) == 1 && get_sign_bi(y) == 1) {
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	Schoolbook_MUL(x, y, z);
	(*z)->sign = ((-1) ^ (x->sign + y->sign));
}
/**
* @brief Schoolbook_MUL : 길이가 2이상인 두 빅넘버 x , y를 곱하는 함수
* @param bigint* x : 곱하고자하는 빅넘버 x
* @param bigint* y : 곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {

	int i, j, c = 0;
	bigint* tmp = NULL;
	word t = 0;
	bi_new(&tmp, 2);
	bi_new(z, (x->wordlen + y->wordlen));

	for (i = 0; i < x->wordlen; i++)
		for (j = 0; j < y->wordlen; j++) {
			MULC(x, y, &tmp, i, j);
			t = (*z)->a[i + j];
			(*z)->a[i + j] += tmp->a[0];
			if ((*z)->a[i + j] < t) c = 1;
			else c = 0;
			(*z)->a[i + j + 1] += tmp->a[1] + c;
		}
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

//void Squaring_word(word* dst, word a) {
//
//	word a0 = a & MASK;
//	word a1 = a >> (sizeof(word) * 4);
//	word s0 = (a1 * a0) << (sizeof(word) * 4);
//	word s1 = (a1 * a0) >> (sizeof(word) * 4);
//
//	dst[0] += s0;
//	dst[1] += s1;
//	if (dst[0] < s0)
//		dst[1] += 1;
//
//	dst[0] += s0;
//	dst[1] += s1;
//	if (dst[0] < s0)
//		dst[1] += 1;
//}
//
//void Squaring_Karatsuba(bigint* x, bigint** z) {
//
//	if (*z != NULL)
//		bi_delete(z);
//
//	*z = (bigint*)malloc(sizeof(bigint));
//
//	if (x->wordlen == 1) {
//		bi_new(z, 2);
//		word dst[2] = { 0, };
//		Squaring_word(dst, *(x->a));
//		(*z)->a[0] = dst[0];
//		(*z)->a[1] = dst[1];
//	}
//	else {
//		bigint* a1 = NULL;
//		bigint* a0 = NULL;
//
//	}
//
//
//}
/**
* @date 2020-11-23 01:49
*/

int bit_length(unsigned int a) {
	int cnt = 32;
	unsigned int x = 0x80000000;

	for (int i = 0; i < 32; i++) {
		if ((a & x) != 0) break;
		else {
			cnt--;
			x = x >> 1;
		}
		
	}
	return cnt;
}
void binary_long_division(int a, int b, int* q, int* r) {
	int aj = 0;
	for (int i = bit_length(a) - 1; i >= 0; i--) {
		aj = a & (1 << i) ? 1 : 0;
		(*r) = ((*r) << 1 ) + aj;
		if ((*r) >= b) {
			(*q) = (*q) +( 1 << i);
			(*r) = (*r) - b;
		}
	}
}

void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r) {
	int aj = 0;
	bigint* tmp = NULL;
	bi_new(&tmp, (b->wordlen)+1);
	bi_new(r, b->wordlen-1);
	bi_new(q, (a->wordlen) - (b->wordlen) + 1);

	for (int i = (a->wordlen) - 1; i >= 0; i--) {
		for (int j = WORD_BITLEN - 1; j >= 0; j--) {
			aj = a->a[i] & (long long)1 << j ? 1 : 0;
			bi_leftshift(&tmp, 1);
			bi_leftshift(q, 1);
			tmp->a[0] += aj;
			if (compareAB(tmp, b) >= 0) {
				SUB(tmp, b, r);
				(*q)->a[0]++;
				bi_assign(&tmp, (*r));
			}
		}
	}
	bi_delete(&tmp);
}

void bi_binary_long_division_test() {
	bigint* x[10] = { NULL, };
	bigint* y[10] = { NULL, };
	bigint* q[10] = { NULL, };
	bigint* r[10] = { NULL, };
	for (int i = 0; i < 10; i++) {
		bi_gen_rand(&x[i], NONNEGATIVE, 3);
		bi_gen_rand(&y[i], NONNEGATIVE, 2);
	}

	for (int i = 0; i < 10; i++) {
		bi_binary_long_division(x[i], y[i], &q[i], &r[i]);
		bi_show_bin(x[i]); printf("=="); bi_show_bin(y[i]); printf("*"); bi_show_bin(q[i]); printf("+"); bi_show_bin(r[i]); printf("\n");

	}

}










