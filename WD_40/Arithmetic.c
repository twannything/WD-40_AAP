#pragma once
#include "Arithmetic.h"
#include "Basic Operation.h"
/**
* @brief bi_reduction : y를 x의 r승 modular 연산 취해주는 함수
* @param bigint** y : 빅넘버 y
* @param bigint* x : 빅넘버 x
* @param int r : x의 지수
*/
void bi_reduction(bigint** y, bigint* x, int r) {
	{
		long long k = r / WORD_BITLEN;
		long long rem = r % WORD_BITLEN;
		if (r > x->wordlen * WORD_BITLEN) {
			bi_assign(y, x); return;
		}
		else if (rem == 0) {
			bi_new(y, k);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((1 << sizeof(word)) - 1); 
				return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((1 << sizeof(word)) - 1);
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
int S_ADDABc(word x, word y, bigint** z, unsigned int carry, int r) {

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

	if (*z != NULL)
		bi_delete(z);

	bi_new(z, x->wordlen + 1);
	
	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	//if (x->wordlen >= y->wordlen)
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
	if (bi_is_zero(y) == 1) 
	 {
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
int S_SUBABb(bigint* x, bigint* y, bigint** z, unsigned int b, int j) {

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;
	if (j < y->wordlen)
		(*z)->a[j] -= y->a[j];
	return b;
}
/**
* @brief SUB_C : 길이가 2이상인 두 빅넘버 x,y를 빼는 함수 x의 wordlen이 항상 y의 wordlen 이상이라고 가정
* @param bigint* x : 빼고자하는 빅넘버 x  (항상 y 보다 크거나 같음)
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
*/
void SUB_C(bigint* x, bigint* y, bigint** z) {
	
	bi_new(z, x->wordlen);

	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	for (int i = y->wordlen; i < x->wordlen; i++)
		y->a[i] = 0;

	/*for (int i = y->wordlen; i < (*z)->wordlen; i++)
		(*z)->a[i] = 0;*/

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
	/* 둘다 양수 일때 */
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		SUB_C(x, y, z);
		return;
	}
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	/* 둘다 음수 일때*/
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
	/* */
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) >= 0) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y)== -1) {
		flip_sign_bi(&y);
		M_ADD(y, x, z);
		flip_sign_bi(&y);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) >= 0) {
		flip_sign_bi(&x);
		M_ADD(x, y, z);
		flip_sign_bi(&x);
		flip_sign_bi(z);
		return;
	}
	else if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) == -1) {
		flip_sign_bi(&x);
		M_ADD(y, x, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
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

void MULC(word x, word y, word* tmp) {

	word a0, a1, b0, b1, c0, c1, t0, t1, t;

	a0 = x & MASKMUL;
	a1 = x >> (sizeof(word) * 4); // 8 = 1 *4 ->  
	b0 = y & MASKMUL;
	b1 = y >> (sizeof(word) * 4);
	t0 = a1 * b0;
	t1 = a0 * b1;
	t0 = (t0 + t1) & MASK;
	t1 = t0 < t1;


	c0 = a0 * b0;
	c1 = a1 * b1;
	t = c0;
	c0 = ((c0 + (t0 << (sizeof(word) * 4))) & MASK);

	c1 = c1 + (t1 << (sizeof(word) * 4)) + (t0 >> (sizeof(word) * 4)) + (c0 < t);
	tmp[0] = c0;
	tmp[1] = c1;
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

	//karatsuba_MUL(x, y, z);
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

	int i, j, k;
	unsigned int c = 0;
	int len_short = 0; int len_long = 0;
	
	bi_new(z, (x->wordlen + y->wordlen));



	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	word tmp[2] = { 0, };
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len_long + 1));

	for (i = 0; i < len_long; i++) {
		for (j = 0; j < len_short; j++) {
			if (len_short == y->wordlen)
				MULC(x->a[i], y->a[j], tmp);
			else MULC(x->a[j], y->a[i], tmp);

			tmp_arr[j] += c;
			c = (tmp_arr[j] < c);

			tmp_arr[j] += tmp[0];
			c += (tmp_arr[j] < tmp[0]);

			tmp_arr[j + 1] += c;
			c = (tmp_arr[j + 1] < c);
			tmp_arr[j + 1] += tmp[1];
			c += (tmp_arr[j + 1] < tmp[1]);
		}
		c = 0;
		for (k = 0; k < len_long + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);

			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, ((len_long + 1)*sizeof(word)));
	}
	free(tmp_arr);
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

	l = (max(x->wordlen, y->wordlen) + 1) >> 1;

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
}

void Squaring_word(word* dst, word a) {

	word a0 = a & MASKMUL;
	word a1 = a >> (sizeof(word) * 4);

	dst[0] = a0 * a0;
	dst[1] = a1 * a1;

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

void Squaring_Schoolbook(bigint* x, bigint** z) {

	int i, j;
	unsigned int c = 0;
	unsigned int cc = 0;
	
	bigint* c1 = NULL;
	bigint* c2 = NULL;
	bigint* t1 = NULL;
	bigint* t2 = NULL;
	bi_new(&c1, 2 * x->wordlen);
	bi_new(&c2, 2 * x->wordlen);
	bi_new(&t1, 2);
	bi_new(&t2, 2);
	bi_new(z, (2 * x->wordlen));

	 word* tmp_arr = NULL;
	 tmp_arr = (word*)calloc(sizeof(word), (1 +  x->wordlen));

	for (j = 0; j < x->wordlen; j++) {
		Squaring_word(t1->a, x->a[j]);
		
		c1->a[2 * j] += c;
		c = (c1->a[2 * j] < c);

		c1->a[2 * j] += t1->a[0];
		c += (c1->a[2 * j] < t1->a[0]);

		c1->a[(2 * j) + 1] += c;
		c = (c1->a[(2 * j) + 1] < c);

		c1->a[(2 * j) + 1] += t1->a[1];
		c += (c1->a[(2 * j) + 1] < t1->a[1]);
		
		for (i = j + 1; i < x->wordlen; i++) {
			MULC(x->a[j], x->a[i], t2->a);

			c2->a[i + j+1] += cc;
			cc = (c2->a[i + j] < cc);

			c2->a[i + j] += t2->a[0];
			cc += (c2->a[i + j] < t2->a[0]);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j + 1] < cc);

			c2->a[i + j + 1] += t2->a[1];
			cc += (c2->a[i + j + 1] < t2->a[1]);
		}
		/*cc = 1 인 경우. 
		 01 88 4a 09 0b 
		*/		 
		/*for (i = j + 1; i < x->wordlen; i++) {
			MULC(x->a[j], x->a[i], t2->a);

			tmp_arr[i] += cc;
			cc = (tmp_arr[i] < cc);
			
			tmp_arr[i] += t2->a[0];
			cc += (tmp_arr[i] < t2->a[0]);

			tmp_arr[i + 1] += cc;
			cc = (tmp_arr[i + 1] < cc);

			tmp_arr[i + 1] += t2->a[1];
			cc += (tmp_arr[i + 1] < t2->a[1]);

		}
		cc = 0;
		for (int k = 0; k < x->wordlen + 1; k++) {
			c2->a[i + k] += cc;
			cc = (c2->a[i + k] < cc);
			
			c2->a[i + k] += tmp_arr[k];
			cc += (c2->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, ((1+ x->wordlen) * sizeof(word)));*/
	}
	bi_leftshift(&c2, 1);
	ADD(c1, c2, z);
}

//void Squaring_Schoolbook(bigint* x, bigint** z) {
//
//	int i, j, c = 0;
//	if (*z != NULL)
//void Squaring_Schoolbook(bigint* x, bigint** z) {
//
//	int i, j, c = 0;
//	if (*z != NULL)
//		bi_delete(z);
//
//	bigint* c1 = NULL;
//	bigint* c2 = NULL;
//	bigint* t1 = NULL;
//	bigint* t2 = NULL;
//	bi_new(&c1, (2 * x->wordlen));
//	bi_new(&c2, (2 * x->wordlen));
//	bi_new(&t1, 2);
//	bi_new(&t2, 2);
//	bi_new(z, (2 * x->wordlen));
//	word dst[2] = { 0, };
//
//	for (j = 0; j < x->wordlen; j++) {
//		Squaring_word(t1->a, x->a[j]);
//		bi_leftshift(&t1, (16 * j));
//		ADD(c1, t1, &c1);
//		for (i = j + 1; i < x->wordlen; i++) {
//			MULC(x->a[j], x->a[i], t2->a);
//			bi_leftshift(&t2, (i * j * 8));
//			ADD(c2, t2, &c2);
//		}
//	}
//	bi_leftshift(&c2, 1);
//	ADD(c1, c2, z);
//
//	bi_delete(&c1);
//	bi_delete(&c2);
//	bi_delete(&t1);
//	bi_delete(&t2);
//
//	free(c1);
//	free(c2);
//	free(t1);
//	free(t2);
//}


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
		(*r) = ((*r) << 1) + aj;
		if ((*r) >= b) {
			(*q) = (*q) + (1 << i);
			(*r) = (*r) - b;
		}
	}
}

void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r) {
	int aj = 0;
	bigint* tmp = NULL;
	bi_new(&tmp, b->wordlen + 1);
	bi_new(r, b->wordlen - 1);
	bi_new(q, (a->wordlen) - (b->wordlen) + 1);

	if (compareAB(b, a) == 1) {
		bi_set_zero(q);
		bi_assign(r, a);
		return;
	}
	else {
		for (int i = (a->wordlen) - 1; i >= 0; i--) {
			for (int j = WORD_BITLEN - 1; j >= 0; j--) {
				aj = a->a[i] & ((unsigned long long)1 << j) ? 1 : 0;
				bi_leftshift(&tmp, (unsigned long long)1); tmp->a[0] += aj;
				bi_leftshift(q, (unsigned long long)1);
				if (compareAB(tmp, b) >= 0) {
					SUB(tmp, b, r);
					(*q)->a[0]++;
					bi_assign(&tmp, (*r));
				}
			}
		}
		bi_assign(r, tmp);
		bi_delete(&tmp);
	}
}

void left_to_right(bigint* x, bigint** z,int n) {

	word* t[2] = { 0x00,  };
	int l;
	l = get_bit_length(x);
	bi_new(z, x->wordlen * n);
	for (int i = l-1; i > 0; i--) {
		Squaring_Schoolbook(*z, z);
		if (bit_of_bi(x, i) == 1)
			MUL(*z, x, z);
	}
}



/**
* @date 2020-11-28 20:17
*/


