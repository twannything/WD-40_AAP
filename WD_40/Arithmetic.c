#pragma once
#include "Arithmetic.h"


/**
* @brief S_ADDABc : 한 워드 끼리의 덧셈 연산후 carry값 = d를 리턴하는 함수
* @param word x : 더하고자하는 워드
* @param word y : 더하고자하는 워드
* @param bigint** z : 더한값을 저장할 빅넘버
* @param int carry : 이전 연산에서 발생한 carry
* @param int r : 더한 값을 z의 r번째 배열에 저장
* return d (carry 값)
*/

int maxlen(int a, int b) {
	return a >= b ? a : b;
}

int minlen(int a, int b) {
	return a < b ? a : b;
}
int S_ADDABc(word x, word y, bigint** z, int carry, int r) {

	int d = 0;

	(*z)->a[r] = (x + y) & MASK;
	if ((*z)->a[r] < x) d = 1;

	(*z)->a[r] = ((*z)->a[r] + carry);
	if ((*z)->a[r] < carry) d = 1;


	return d;
}

/**
* @brief S_ADDABc_print : 한 워드 끼리의 덧셈 연산후 carry값 = d를 리턴하는 함수
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param word x : 더하고자하는 워드
* @param word y : 더하고자하는 워드
* @param bigint** z : 더한값을 저장할 빅넘버
* @param int carry : 이전 연산에서 발생한 carry
* @param int r : 더한 값을 z의 r번째 배열에 저장
* return d (carry 값)
*/
int S_ADDABc_print(word x, word y, bigint** z, int carry, int r) {

	int d = 0;

	printf("x의 %d번째 워드 = ", r);
	word_show_hex(x);
	printf("\n");
	printf("y의 %d번째 워드 = ", r);
	word_show_hex(y);
	printf("\n");
	printf("이전에 발생한 carry = %d\n", carry);

	(*z)->a[r] = (x + y) & MASK;
	if ((*z)->a[r] < x) d = 1;

	(*z)->a[r] = ((*z)->a[r] + carry);
	if ((*z)->a[r] < carry) d = 1;

	printf("%d번째 워드간의 연산 후의 값 = ", r);
	word_show_hex((*z)->a[r]);
	printf("\n");
	printf("발생한 carry = %d\n", d);
	printf("%d번째 연산 후의 값 \n", r);
	bi_show_hex(*z);
	printf("\n\n");

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
	if ((y) == NULL)
		return;
	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	// word 길이가 차이날 때 차이 만큼 짧은 빅넘버의 left word를 0으로 채워줌
	if (x->wordlen >= y->wordlen)
		for (int i = y->wordlen; i < x->wordlen; i++)
			y->a[i] = 0;

	c = 0;

	for (int i = 0; i < x->wordlen; i++) 
		c = S_ADDABc(x->a[i], y->a[i], z, c, i);
	

	(*z)->a[x->wordlen] = c;

	if ((*z)->a[x->wordlen] == 0) bi_refine(z);
}

/**
* @brief M_ADD_print : 길이가 2이상인 두 빅넘버 x,y를 더하는 함수 x의 wordlen이 항상 y의 wordlen 이상이라고 가정
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 더하고자하는 빅넘버 x
* @param bigint* y : 더하고자하는 빅넘버 y
* @param bigint** z: 더한값을 저장할 빅넘버 z (z->wordlen = max(x->wordlen, y->wordlen) + 1)
*/
void M_ADD_print(bigint* x, bigint* y, bigint** z) {
	int c = 0;

	if (*z != NULL)
		bi_delete(z);

	bi_new(z, x->wordlen + 1);
	if ((y) == NULL)
		return;
	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	// word 길이가 차이날 때 차이 만큼 짧은 빅넘버의 left word를 0으로 채워줌
	if (x->wordlen >= y->wordlen)
		for (int i = y->wordlen; i < x->wordlen; i++)
			y->a[i] = 0;

	c = 0;

	for (int i = 0; i < x->wordlen; i++)
		c = S_ADDABc_print(x->a[i], y->a[i], z, c, i);


	(*z)->a[x->wordlen] = c;

	if ((*z)->a[x->wordlen] == 0) bi_refine(z);
}

/**
* @brief ADD : 덧셈에서 사용되는 모든 경우를 처리하는 함수
* @param bigint* x : 더하고자하는 빅넘버 x
* @param bigint* y : 더하고자하는 빅넘버 y
* @param bigint** z : 더한 값을 저장할 빅넘버 z
* @image html add.jpg 
*/
void ADD(bigint* x, bigint* y, bigint** z) {

	// x = 0 이면 x + y = y
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		return;
	}
	// y = 0 이면 x + y = x
	if (bi_is_zero(y) == 1) 
	 {
		bi_assign(z, x);
		return;
	}
	// x > 0 , y < 0 이면 x + y = x - |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x < 0 , y > 0 이면 x + y = -|x| + y = y - |x|
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB(y, x, z);
		flip_sign_bi(&x);
		return;
	}
	// x < 0 , y < 0 일때
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		// |x| > |y| 이면 x + y = - (|x| + |y|)
		if (x->wordlen >= y->wordlen) {
			M_ADD(x, y, z);
			flip_sign_bi(z);
			return;
		}
		// |x| < |y| 이면 x + y = - (|y| + |x|)
		else {
			M_ADD(y, x, z);
			flip_sign_bi(z);
			return;
		}
	}
	// x >= y > 0 일 때
	if (x->wordlen >= y->wordlen) {
		M_ADD(x, y, z);
		return;
	}
	// y > x > 0 일 때
	else {
		M_ADD(y, x, z);
		return;
	}
}

/**
* @brief ADD_print : 덧셈에서 사용되는 모든 경우를 처리하는 함수
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 더하고자하는 빅넘버 x
* @param bigint* y : 더하고자하는 빅넘버 y
* @param bigint** z : 더한 값을 저장할 빅넘버 z
*/
void ADD_print(bigint* x, bigint* y, bigint** z) {
	// x = 0 이면 x + y = y
	if (bi_is_zero(x) == 1) {
		printf("Case : x = 0 then x + y = y\n\n");
		bi_assign(z, y);
		return;
	}
	// y = 0 이면 x + y = x
	if (bi_is_zero(y) == 1)
	{
		printf("Case : y = 0 then x + y = x\n\n");
		bi_assign(z, x);
		return;
	}
	// x > 0 , y < 0 이면 x + y = x - |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		printf("Case : x > 0, y < 0 then x + y = x - |y|\n\n");
		flip_sign_bi(&y);
		SUB_print(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x < 0 , y > 0 이면 x + y = -|x| + y = y - |x|
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		printf("Case : x < 0, y > 0 then x + y = y - |x|\n\n");
		flip_sign_bi(&x);
		SUB_print(y, x, z);
		flip_sign_bi(&x);
		return;
	}
	// x < 0 , y < 0 일때
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		// |x| > |y| 이면 x + y = - (|x| + |y|)
		if (x->wordlen >= y->wordlen) {
			printf("Case : x < 0, y < 0 , |x| > |y| then x + y = -(|x| - |y|)\n\n");
			M_ADD_print(x, y, z);
			flip_sign_bi(z);
			return;
		}
		// |x| < |y| 이면 x + y = - (|y| + |x|)
		else {
			printf("Case : x < 0, y < 0 , |x| < |y| then x + y = -(|y| - |x|)\n\n");
			M_ADD_print(y, x, z);
			flip_sign_bi(z);
			return;
		}
	}
	// x >= y > 0 일 때
	if (x->wordlen >= y->wordlen) {
		printf("Case : x >= y > 0 then x + y = x + y\n\n");
		M_ADD_print(x, y, z);
		return;
	}
	// y > x > 0 일 때
	else {
		printf("Case : y > x > 0 then x + y = y + x\n\n");
		M_ADD_print(y, x, z);
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
* @brief S_SUBABb_print : 한 워드간의 뺄셈연산하는 함수 borrow 값을 리턴
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 빼고자하는 빅넘버 x
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
* @param int b : 이전 borrow 값
* @param int j : 뺀 값을 z의 j번째 배열에 저장
* @return b (borrow 값)
*/
int S_SUBABb_print(bigint* x, bigint* y, bigint** z, unsigned int b, int j) {

	printf("x의 %d번째 워드 = ", j);
	word_show_hex(x->a[j]);
	printf("\n");
	printf("y의 %d번째 워드 = ", j);
	word_show_hex(y->a[j]);
	printf("\n");
	printf("이전에 발생한 borrow = %d\n", b);

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;
	if (j < y->wordlen)
		(*z)->a[j] -= y->a[j];

	printf("%d번째 워드간의 연산 후의 값 = ", j);
	word_show_hex((*z)->a[j]);
	printf("\n");
	printf("발생한 borrow = %d\n", b);
	printf("%d번째 연산 후의 값 \n", j);
	bi_show_hex(*z);
	printf("\n\n");

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

	// wordlen가 차이가 난다면 차이만큼 짧은 빅넘버의 left word를 0으로 추가해줌
	for (int i = y->wordlen; i < x->wordlen; i++)
		y->a[i] = 0;

	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb(x, y, z, b, j);
	}
	bi_refine(z);
}

/**
* @brief SUB_C_print : 길이가 2이상인 두 빅넘버 x,y를 빼는 함수 x의 wordlen이 항상 y의 wordlen 이상이라고 가정
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 빼고자하는 빅넘버 x  (항상 y 보다 크거나 같음)
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
*/
void SUB_C_print(bigint* x, bigint* y, bigint** z) {

	bi_new(z, x->wordlen);

	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	// wordlen가 차이가 난다면 차이만큼 짧은 빅넘버의 left word를 0으로 추가해줌
	for (int i = y->wordlen; i < x->wordlen; i++)
		y->a[i] = 0;

	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb_print(x, y, z, b, j);
	}
	bi_refine(z);
}


/**
* @brief SUB : 뺄셈에서 사용되는 모든 경우를 처리하는 함수
* @param bigint* x : 빼고자하는 빅넘버 x
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
* - Pseudo Code
* @image html sub.jpg
*/
void SUB(bigint* x, bigint* y, bigint** z) {
	// x = 0 이면 x - y = -y
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 0 이면 x - y = -x
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}
	// x = y 이면 x - y = 0
	if (compareAB(x, y) == 0) {
		bi_set_zero(z);
		return;
	}

	// x >= y > 0 일 때
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		SUB_C(x, y, z);
		return;
	}
	// y > x > 0 일 때
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	// 0 >= x > y 일 때
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// 0 > y > x 일 때
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) == -1) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| > |y| 이면 x - y = x + |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) >= 0) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| < |y| 이면 x - y = |y| + x
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) == -1) {
		flip_sign_bi(&y);
		M_ADD(y, x, z);
		flip_sign_bi(&y);
		return;
	}// x < 0 , y > 0 & |x| > |y| 이면 x - y = -(x + y)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) >= 0) {
		flip_sign_bi(&x);
		M_ADD(x, y, z);
		flip_sign_bi(&x);
		flip_sign_bi(z);
		return;
	}// x < 0 , y > 0 & |x| < |y| 이면 x - y = -(y + x)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) == -1) {
		flip_sign_bi(&x);
		M_ADD(y, x, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		return;
	}
}

/**
* @brief SUB_print : 뺄셈에서 사용되는 모든 경우를 처리하는 함수
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 빼고자하는 빅넘버 x
* @param bigint* y : 빼고자하는 빅넘버 y
* @param bigint** z : 뺀 값을 저장할 빅넘버 z
*/
void SUB_print(bigint* x, bigint* y, bigint** z) {
	// x = 0 이면 x - y = -y
	if (bi_is_zero(x) == 1) {
		printf("Case : x = 0 then x - y = -y\n\n");
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 0 이면 x - y = -x
	if (bi_is_zero(y) == 1) {
		printf("Case : y = 0 then x - y = -x\n\n");
		bi_assign(z, x);
		return;
	}
	// x = y 이면 x - y = 0
	if (compareAB(x, y) == 0) {
		printf("Case : x = y then x - y = 0\n\n");
		bi_set_zero(z);
		return;
	}

	// x >= y > 0 일 때
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		printf("Case : x >= y > 0 then x - y = x - y\n\n");
		SUB_C_print(x, y, z);
		return;
	}
	// y > x > 0 일 때
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		printf("Case : y > x > 0 then x - y = y - x\n\n");
		SUB_C_print(y, x, z);
		flip_sign_bi(z);
		return;
	}
	// 0 >= x > y 일 때
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		printf("Case : 0 >= x > y then x - y = |y| - |x|\n\n");
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C_print(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// 0 > y > x 일 때
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) == -1) {
		printf("Case : 0 > y > x then x - y = - (|x| - |y|)\n\n");
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C_print(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| > |y| 이면 x - y = x + |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) >= 0) {
		printf("Case : x > 0 ,y < 0 , |x| > |y| then x - y = x + |y|\n\n");
		flip_sign_bi(&y);
		M_ADD_print(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| < |y| 이면 x - y = |y| + x
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) == -1) {
		printf("Case : x > 0 ,y < 0 , |x| < |y| then x - y = |y| + x\n\n");
		flip_sign_bi(&y);
		M_ADD_print(y, x, z);
		flip_sign_bi(&y);
		return;
	}// x < 0 , y > 0 & |x| > |y| 이면 x - y = -(x + y)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) >= 0) {
		printf("Case : x < 0 ,y > 0 , |x| > |y| then x - y = - (|x| + y)\n\n");
		flip_sign_bi(&x);
		M_ADD_print(x, y, z);
		flip_sign_bi(&x);
		flip_sign_bi(z);
		return;
	}// x < 0 , y > 0 & |x| < |y| 이면 x - y = -(y + x)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) == -1) {
		printf("Case : x < 0 ,y > 0 , |x| < |y| then x - y = - (y + |x|)\n\n");
		flip_sign_bi(&x);
		M_ADD_print(y, x, z);
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
	a1 = x >> (sizeof(word) * 4);
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
* - Pseudo Code
* @image html mul.jpg
*/
void MUL(bigint* x, bigint* y, bigint** z) {

	// x 또는 y 가 0이면 x * y = 0
	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) {
		bi_set_zero(z);
		return;
	}
	// x = 1 이면 x * y = y
	if (bi_is_one(x) == 1) {
		bi_assign(z, y);
		return;
	}
	// x = -1 이면 x * y = -y
	if (bi_is_one(x) == 1 && get_sign_bi(x) == NEGATIVE) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 1 이면 x * y = x
	if (bi_is_one(y) == 1) {
		bi_assign(z, x);
		return;
	}
	// y = -1 이면 x * y = -x
	if (bi_is_one(y) == 1 && get_sign_bi(y) == NEGATIVE) {
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	//karatsuba_MUL(x, y, z);
	Schoolbook_MUL(x, y, z);

	(*z)->sign = (x->sign + y->sign) % 2;
}

/**
* @brief MUL_print : 곱셈에서 사용되는 모든 경우를 처리하는 함수
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x :곱하고자하는 빅넘버 x
* @param bigint* y :곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void MUL_print(bigint* x, bigint* y, bigint** z) {

	// x 또는 y 가 0이면 x * y = 0
	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) {
		printf("Case : x = 0 or y = 0 then x * y = 0\n\n");
		bi_set_zero(z);
		return;
	}
	// x = 1 이면 x * y = y
	if (bi_is_one(x) == 1) {
		printf("Case : x = 1 then x * y = y\n\n");
		bi_assign(z, y);
		return;
	}
	// x = -1 이면 x * y = -y
	if (bi_is_one(x) == 1 && get_sign_bi(x) == NEGATIVE) {
		printf("Case : x = -1 then x * y = -y\n\n");
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 1 이면 x * y = x
	if (bi_is_one(y) == 1) {
		printf("Case : y = 1 then x * y = x\n\n");
		bi_assign(z, x);
		return;
	}
	// y = -1 이면 x * y = -x
	if (bi_is_one(y) == 1 && get_sign_bi(y) == NEGATIVE) {
		printf("Case : y = -1 then x * y = -x\n\n");
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	printf("Case : x * y = x * y\n\n");
	Schoolbook_MUL_print(x, y, z);

	(*z)->sign = (x->sign + y->sign) % 2;
}

/**
* @brief Schoolbook_MUL : 길이가 2이상인 두 빅넘버 x , y를 곱하는 함수
* @param bigint* x : 곱하고자하는 빅넘버 x
* @param bigint* y : 곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {
	if ((*z) != NULL)
		bi_delete(z);

	int i, j, k;
	unsigned int c = 0;
	int len_short = 0; int len_long = 0;
	int len;
	bi_new(z, (x->wordlen + y->wordlen));

	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	len = len_long + len_short;
	word tmp[2] = { 0, };
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len + 1));

	for (i = 0; i < len_long; i++) {
		for (j = 0; j < len_short; j++) {
			if (len_short == y->wordlen)
				MULC(x->a[i], y->a[j], tmp);
			else 
				MULC(x->a[j], y->a[i], tmp);
							
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
		// 결과값을 더하면서 발생하는 carry 처리하면서 z에 저장
		for (k = 0; k < len_short + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);
			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, ((len + 1) * sizeof(word)));
	}
	free(tmp_arr);
}

/**
* @brief Schoolbook_MUL_print : 길이가 2이상인 두 빅넘버 x , y를 곱하는 함수
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 곱하고자하는 빅넘버 x
* @param bigint* y : 곱하고자하는 빅넘버 y
* @param bigint** z : 곱한 값을 저장할 빅넘버 z
*/
void Schoolbook_MUL_print(bigint* x, bigint* y, bigint** z) {
	if ((*z) != NULL)
		bi_delete(z);

	int i, j, k;
	unsigned int c = 0;
	int len_short = 0; int len_long = 0;
	int len;
	bi_new(z, (x->wordlen + y->wordlen));

	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	len = len_long + len_short;
	word tmp[2] = { 0, };
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len + 1));

	for (i = 0; i < len_long; i++) {
		for (j = 0; j < len_short; j++) {
			if (len_short == y->wordlen) {
				MULC(x->a[i], y->a[j], tmp);
				printf("x의 %d번째 워드 = ", i);
				word_show_hex(x->a[i]);
				printf("\n");
				printf("y의 %d번째 워드 = ", j);
				word_show_hex(y->a[j]);
				printf("\n");
				printf("워드간의 곱셈 후의 값 = ");
				word_show_hex(tmp[1]);
				word_show_hex(tmp[0]);
				printf("\n");

			}
			else {
				MULC(x->a[j], y->a[i], tmp);
				printf("x의 %d번째 워드 = ", j);
				word_show_hex(x->a[j]);
				printf("\n");
				printf("y의 %d번째 워드 = ", i);
				word_show_hex(y->a[i]);
				printf("\n");
				printf("워드간의 곱셈 후의 값 = ");
				word_show_hex(tmp[1]);
				word_show_hex(tmp[0]);
				printf("\n");

			}

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
		// 결과값을 더하면서 발생하는 carry 처리하면서 z에 저장
		for (k = 0; k < len_short + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);
			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		printf("carry 처리를 포함한 워드간의 연산 중간 값 = ");
		bi_show_hex(*z);
		printf("\n\n");
		memset(tmp_arr, 0, ((len + 1) * sizeof(word)));
	}
	free(tmp_arr);
}

/**
* @brief Squaring_word : 빅넘버 제곱연산에 사용되는 한 word 끼리의 제곱
* @param word* dst : 제곱의 결과를 저장하는 역할
* @param word a : 제곱하고자하는 a (1word)
*/
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


/**
* @brief Squaring_Schoolbook : 스쿨북 방식의 빅넘버 제곱연산
* @param bigint* x  : 제곱하고자하는 빅넘버 x
* @param bigint** z  : 제곱의 결과를 저장하는 빅넘버 z
*/
void Squaring_Schoolbook(bigint* x, bigint** z) {

	if ((*z) != NULL)
		bi_delete(z);

	int i = 0;
	int j = 0;
	unsigned int c = 0;
	unsigned int cc = 0;
	bigint* c1 = NULL;
	bigint* c2 = NULL;
	word t1[2] = { 0, };
	word t2[2] = { 0, };

	bi_new(&c1, (2 * x->wordlen));
	bi_new(&c2, (2 * x->wordlen));
	bi_new(z, (2 * x->wordlen));

	//word* tmp_arr = NULL;
	//tmp_arr = (word*)calloc(sizeof(word), (1 + x->wordlen));
	// c1 : 각 워드의 제곱의 연접으로 구성
	for (j = 0; j < x->wordlen; j++) {
		Squaring_word(t1, x->a[j]);

		c1->a[2 * j] += c;
		c = (c1->a[2 * j] < c);

		c1->a[2 * j] += t1[0];
		c += (c1->a[2 * j] < t1[0]);

		c1->a[(2 * j) + 1] += c;
		c = (c1->a[(2 * j) + 1] < c);

		c1->a[(2 * j) + 1] += t1[1];
		c += (c1->a[(2 * j) + 1] < t1[1]);

		// c2 : 중복이 포함된 워드간의 곱셈 결과의 합으로 구성
		for (i = j + 1; i < x->wordlen; i++) {
			MULC(x->a[j], x->a[i], t2);
			
			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j] < cc);

			c2->a[i + j] += t2[0];
			cc += (c2->a[i + j] < t2[0]);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j + 1] < cc);

			c2->a[i + j + 1] += t2[1];
			cc += (c2->a[i + j + 1] < t2[1]);
			if (cc == 1) {
				c2->a[i + j + 2] += cc;
				if (c2->a[i + j + 2] < cc) {
					c2->a[i + j + 3] += cc;
					if (c2->a[i + j + 3] < cc) {
						c2->a[i + j + 4] += cc;
					}
				}
			}
			cc = 0;
		}
	}
	bi_leftshift(&c2, 1);
	ADD(c1, c2, z);

	bi_delete(&c1);
	bi_delete(&c2);
}

/**
* @brief Squaring_Schoolbook_print : 스쿨북 방식의 빅넘버 제곱연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x  : 제곱하고자하는 빅넘버 x
* @param bigint** z  : 제곱의 결과를 저장하는 빅넘버 z
*/
void Squaring_Schoolbook_print(bigint* x, bigint** z) {

	if ((*z) != NULL)
		bi_delete(z);

	int i = 0;
	int j = 0;
	unsigned int c = 0;
	unsigned int cc = 0;
	bigint* c1 = NULL;
	bigint* c2 = NULL;
	word t1[2] = { 0, };
	word t2[2] = { 0, };

	bi_new(&c1, (2 * x->wordlen));
	bi_new(&c2, (2 * x->wordlen));
	bi_new(z, (2 * x->wordlen));

	//word* tmp_arr = NULL;
	//tmp_arr = (word*)calloc(sizeof(word), (1 + x->wordlen));
	// c1 : 각 워드의 제곱의 연접으로 구성
	for (j = 0; j < x->wordlen; j++) {
		Squaring_word(t1, x->a[j]);

		printf("x의 %d번째 워드 = ", j);
		word_show_hex(x->a[j]);
		printf("\n");
		printf("x의 %d번째 워드 제곱 결과 = ", j);
		word_show_hex(t1[1]);
		word_show_hex(t1[0]);
		printf("\n");

		c1->a[2 * j] += c;
		c = (c1->a[2 * j] < c);

		c1->a[2 * j] += t1[0];
		c += (c1->a[2 * j] < t1[0]);

		c1->a[(2 * j) + 1] += c;
		c = (c1->a[(2 * j) + 1] < c);

		c1->a[(2 * j) + 1] += t1[1];
		c += (c1->a[(2 * j) + 1] < t1[1]);

		printf("carry 처리를 포함한 c1 중간 값 = ");
		bi_show_hex(c1);
		printf("\n");
		// c2 : 중복이 포함된 워드간의 곱셈 결과의 합으로 구성
		for (i = j + 1; i < x->wordlen; i++) {
			MULC(x->a[j], x->a[i], t2);
			printf("x의 %d번째 워드 = ", j);
			word_show_hex(x->a[j]);
			printf("\n");
			printf("x의 %d번째 워드 = ", i);
			word_show_hex(x->a[i]);
			printf("\n");

			printf("워드간의 곱셈 후의 값 = ");
			word_show_hex(t2[1]);
			word_show_hex(t2[0]);
			printf("\n");

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j] < cc);

			c2->a[i + j] += t2[0];
			cc += (c2->a[i + j] < t2[0]);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j + 1] < cc);

			c2->a[i + j + 1] += t2[1];
			cc += (c2->a[i + j + 1] < t2[1]);
			// 괴물쥐급 캐리가 발생하였을 때 예외처리
			if (cc == 1) {
				c2->a[i + j + 2] += cc;
				if (c2->a[i + j + 2] < cc) {
					c2->a[i + j + 3] += cc;
					if (c2->a[i + j + 3] < cc) {
						c2->a[i + j + 4] += cc;
					}
				}
			}
			cc = 0;
		}
		printf("carry 처리를 포함한 c2 중간 값 = ");
		bi_show_hex(c2);
		printf("\n\n");
	}
	printf("최종 c1 = ");
	bi_show_hex(c1);
	printf("\n");
	printf("최종 c2 = ");
	bi_show_hex(c2);
	printf("\n");
	bi_leftshift(&c2, 1);
	printf("c2 << 1 = ");
	bi_show_hex(c2);
	printf("\n");
	ADD(c1, c2, z);
	printf("c1 + c2 = ");
	bi_delete(&c1);
	bi_delete(&c2);
}

/**
* @brief SQU : 빅넘버 제곱연산
* @param bigint* x  : 제곱하고자하는 빅넘버 x
* @param bigint** z  : 제곱의 결과를 저장하는 빅넘버 z
* - Pseudo Code
* @image html squ.jpg
*/
void SQU(bigint* x, bigint** z) {

	// x 가 0 이나 1 또는 -1 일 때
	if (bi_is_zero(x) == 1 || bi_is_one(x) == 1 || bi_is_one(x) == -1) {
		bi_assign(z, x);
		return;
	}
	Squaring_Schoolbook(x, z);
}

/**
* @brief SQU_print : 빅넘버 제곱연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x  : 제곱하고자하는 빅넘버 x
* @param bigint** z  : 제곱의 결과를 저장하는 빅넘버 z
*/
void SQU_print(bigint* x, bigint** z) {

	// x 가 0 이나 1 또는 -1 일 때
	if (bi_is_zero(x) == 1 || bi_is_one(x) == 1 || bi_is_one(x) == -1) {
		bi_assign(z, x);
		return;
	}
	Squaring_Schoolbook_print(x, z);
}

/**
* @brief bit_length : 스쿨북 방식의 빅넘버 제곱연산
* @param unsigned int a :
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

/**
* @brief binary_long_division : 일반적인 이진 롱 디비전
* @param int a : 나눠질 a = b*q + r
* @param int b : 나누는 b
* @param int* q : a를 b로 나눈 몫
* @param int* r : a를 b로 나눈 나머지
*/
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


/**
* @brief binary_long_division : 빅넘버에서의 이진 롱 디비전
* @param bigint* a : 나눠질 a = b*q + r
* @param bigint* b : 나누는 b
* @param bigint** q : a를 b로 나눈 몫
* @param bigint** r : a를 b로 나눈 나머지
*/


void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r) {
	int aj = 0;

	if (b->sign == NEGATIVE || bi_is_zero(b)) {
		bi_set_zero(q);
		bi_set_zero(r);
		return;
	}
	if (a->sign == NONNEGATIVE && compareAB(b, a) == 1) {
		bi_set_zero(q);
		bi_assign(r, a);
		return;
	}
	if (bi_is_one(b)) {
		bi_assign(q, a);
		bi_set_zero(r);
		return;

	}
	else {
		int max_len = maxlen(a->wordlen, b->wordlen);
		int min_len = minlen(a->wordlen, b->wordlen);
		bigint* tmp = NULL;
		bigint* q_tmp = NULL;
		bigint* one = NULL;
		bi_set_one(&one);
		bi_new(&tmp, b->wordlen + 1);
		bi_new(r, b->wordlen);
		bi_new(q, max_len-min_len + 1);
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
		if (a->sign == NEGATIVE) {
			bi_assign(&q_tmp, *q);
			flip_sign_bi(&q_tmp);
			SUB(q_tmp, one, q);
			SUB(b, tmp, r);
		}
		bi_delete(&tmp);
		bi_delete(&q_tmp);
		bi_delete(&one);
	}
}

void bi_binary_long_division_print(bigint* a, bigint* b, bigint** q, bigint** r) {

	if (b->sign == NEGATIVE || bi_is_zero(b)) {
		printf(" Y IS NEGATIVE OR ZERO!!\n");
		bi_set_zero(q);
		bi_set_zero(r);
		return;
	}
	if (a->sign == NONNEGATIVE && compareAB(b, a) == 1) {
		bi_set_zero(q);
		bi_assign(r, a);
		return;
	}
	if (bi_is_one(b)) {
		bi_assign(q, a);
		bi_set_zero(r);
		return;

	}

	int max_len = maxlen(a->wordlen, b->wordlen);
	int min_len = minlen(a->wordlen, b->wordlen);
	int aj = 0;
	bigint* tmp = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bi_set_one(&one);
	bi_new(&tmp, b->wordlen + 1);
	bi_new(r, b->wordlen);
	bi_new(q, max_len - min_len + 1);
		for (int i = (a->wordlen) - 1; i >= 0; i--) {
			for (int j = WORD_BITLEN - 1; j >= 0; j--) {
				aj = a->a[i] & ((unsigned long long)1 << j) ? 1 : 0;
				bi_leftshift(&tmp, (unsigned long long)1); tmp->a[0] += aj;
				bi_leftshift(q, (unsigned long long)1);
				if (compareAB(tmp, b) >= 0) {
					SUB(tmp, b, r);
					(*q)->a[0]++;
					bi_assign(&tmp, (*r));
					printf("remainder : ");
					bi_show_hex(tmp);
					printf("\n");
					printf("quotient : ");
					bi_show_hex(*q);
					printf("\n");
				}
			}
		}
		bi_assign(r, tmp);
		if (a->sign == NEGATIVE) {
			printf("If X is NEGATIVE , X = (-Q-1)Y + (B-R)\n");
			bi_assign(&q_tmp, *q);
			flip_sign_bi(&q_tmp);
			SUB(q_tmp, one, q);
			SUB(b, tmp, r);
		}
		bi_delete(&tmp);
		bi_delete(&q_tmp);
		bi_delete(&one);
}

/**
* @brief binary_long_division : 빅넘버에서의 롱 디비전에서 사용될 워드단위간의 롱 디비전
* @param bigint* x : 나눠질 x = b*q + r
* @param bigint* y : 나누는 y
* @param bigint** q : a를 b로 나눈 몫
* @param bigint** r : a를 b로 나눈 나머지
*/
void long_division_2word(bigint* x, bigint* y, bigint** q, bigint** r) {
	bi_set_zero(q);
	bi_new(r, 1);
	bigint* tmp1 = NULL;
	bigint* tmp2 = NULL;
	(*r)->a[0] = x->a[1];
	for (int i = WORD_BITLEN - 1; i >= 0; i--) {
		int ai = (x->a[0] & (unsigned long long)1 << i) ? 1 : 0;
		if ((*r)->a[0] >= (unsigned long long)1 << (WORD_BITLEN - 1)) {
			(*q)->a[0] += (unsigned long long)1 << i;
			bi_assign(&tmp1, *r);
			tmp1->a[0] += ai;
			SUB(y, *r, &tmp2);
			SUB(tmp1, tmp2, r);
		}
		else {
			bi_leftshift(r, 1);
			(*r)->a[0] += ai;
			if (compareAB(*r, y) >= 0) {
				(*q)->a[0] += (unsigned long long)1 << i;
				bi_assign(&tmp1, *r);
				SUB(tmp1, y, r);
			}
		}
	}
	bi_delete(&tmp1);
	bi_delete(&tmp2);
}

/**
* @brief divcc : 
* @param bigint* x : 나눠질 x = b*q + r
* @param bigint* y : 나누는 y
* @param bigint** q : a를 b로 나눈 몫
* @param bigint** r : a를 b로 나눈 나머지
*/
void divcc(bigint* x, bigint* y, bigint** q, bigint** r) {
	int x_len = x->wordlen;
	int y_len = y->wordlen;
	bigint* tmp = NULL;
	bigint* r_tmp = NULL;
	bigint* q_tmp = NULL;
	bigint* bq = NULL;
	bigint* one = NULL;
	bigint* a = NULL;
	bigint* b = NULL;
	bi_new(&b, 1);
	bi_new(&a, 2);

	bi_set_one(&one);
	bi_new(&q_tmp, x_len - y_len + 1);
	bi_new(&tmp, 1);
	if (x_len == y_len) {
		(*q)->a[0] = (x->a[x_len - 1] / y->a[y_len - 1]);
	}
	if (x_len == y_len + 1) {
		if (x->a[x_len - 1] == y->a[y_len - 1])
			(*q)->a[0] = MASK;
		else {
			a->a[a->wordlen - 1] = x->a[x->wordlen - 1];
			a->a[a->wordlen - 2] = x->a[x->wordlen - 2];
			b->a[b->wordlen - 1] = y->a[y->wordlen - 1];
			long_division_2word(a, b, q, &tmp);
		}
	}
	MUL(y, (*q), &bq);
	SUB(x, bq, r);
	while ((*r)->sign == NEGATIVE) {
		SUB(*q, one, &q_tmp);
		bi_assign(q, q_tmp);
		ADD(*r, y, &r_tmp);
		bi_assign(r, r_tmp);
	}
	bi_delete(&tmp);
	bi_delete(&r_tmp);
	bi_delete(&q_tmp);
	bi_delete(&bq);
	bi_delete(&one);
	bi_delete(&a);
	bi_delete(&b);

}

/**
* @brief divc :
* @param bigint* x : 나눠질 x = b*q + r
* @param bigint* y : 나누는 y
* @param bigint** q : a를 b로 나눈 몫
* @param bigint** r : a를 b로 나눈 나머지
*/
void divc(bigint* x, bigint* y, bigint** q, bigint** r) {
	int x_len = x->wordlen;
	int y_len = y->wordlen;
	bigint* y_tmp = NULL;
	bi_new(r, y_len);
	bi_assign(&y_tmp, y);
	int k = 0;
	if (compareAB(y, x) == 1) {
		bi_set_zero(q);
		bi_assign(r, x);
		bi_delete(&y_tmp);
		return;
	}
	while (!((y_tmp->a[y_len - 1] & ((unsigned long long)1 << (WORD_BITLEN - 1))) ? 1 : 0)) {
		y_tmp->a[y_len - 1] = y_tmp->a[y_len - 1] << 1;
		k++;
	}
	bi_delete(&y_tmp);
	bi_leftshift(&x, k);
	bi_leftshift(&y, k);
	divcc(x, y, q, r);
	bi_rightshift(r, k);
	bi_rightshift(&x, k);
	bi_rightshift(&y, k);
	bi_delete(&y_tmp);
}

/**
* @brief bi_div : 빅넘버 나눗셈연산 
* @param bigint* x  : 나누고자하는 빅넘버 x
* @param bigint* y  : 나누는 빅넘버 y
* @param bigint** q  : 몫을 저장하는 빅넘버 q
* @param bigint** r  : 나머지를 저장하는 빅넘버 r
* - Pseudo Code
* @image html div.jpg
*/
void bi_div(bigint* x, bigint* y, bigint** q, bigint** r) {
	int x_len1 = x->wordlen;
	int y_len1 = y->wordlen;
	bigint* r_tmp1 = NULL;
	bigint* q_tmp1 = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bigint* tmp = NULL;
	bi_set_one(&one);

	if (y->sign == NEGATIVE) {
		bi_set_zero(q);
		bi_set_zero(r);//printf("Invalid operation!!!!");
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}
	if (x->sign == NONNEGATIVE && compareAB(y, x) == 1) {
		bi_set_zero(q);
		bi_assign(r, x);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	if (bi_is_one(y)) {
		bi_assign(q, x);
		bi_set_zero(r);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	//bi_new(r, y_len1);
	bi_new(&r_tmp1, y_len1);
	//bi_new(q, x_len1 - y_len1 + 1);
	bi_new(&q_tmp1, 1);
	bi_set_zero(q);
	bi_set_zero(r);

	for (int i = x_len1 - 1; i >= 0; i--) {
		bi_leftshift(r, WORD_BITLEN);
		(*r)->a[0] += x->a[i];
		bi_assign(&r_tmp1, *r);
		divc(r_tmp1, y, &q_tmp1, r);
		bi_leftshift(q, WORD_BITLEN);
		(*q)->a[0] += q_tmp1->a[0];
	}

	if (x->sign == NEGATIVE) {
		bi_assign(&q_tmp, *q);
		bi_assign(&tmp, *r);
		flip_sign_bi(&q_tmp);
		SUB(q_tmp, one, q);
		SUB(y, tmp, r);

	}
	bi_delete(&q_tmp);
	bi_delete(&tmp);
	bi_delete(&one);
	bi_delete(&r_tmp1);
	bi_delete(&q_tmp1);
}

void bi_div_print(bigint* x, bigint* y, bigint** q, bigint** r) {

	int x_len1 = x->wordlen;
	int y_len1 = y->wordlen;
	bigint* r_tmp1 = NULL;
	bigint* q_tmp1 = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bigint* tmp = NULL;
	bi_set_one(&one);

	if (y->sign == NEGATIVE || bi_is_zero(y)) {
		bi_set_zero(q);
		bi_set_zero(r);
		printf("Y IS NEGATIVE OR ZERO!!!\n");
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}
	if (y->sign == NONNEGATIVE && compareAB(y, x) == 1) {
		bi_set_zero(q);
		bi_assign(r, x);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	if (bi_is_one(y)) {
		bi_assign(q, x);
		bi_set_zero(r);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	//bi_new(r, y_len1);
	bi_new(&r_tmp1, y_len1);
	//bi_new(q, x_len1 - y_len1 + 1);
	bi_new(&q_tmp1, 1);
	bi_set_zero(q);
	bi_set_zero(r);

	for (int i = x_len1 - 1; i >= 0; i--) {
		bi_leftshift(r, WORD_BITLEN);
		(*r)->a[0] += x->a[i];
		bi_assign(&r_tmp1, *r);
		divc(r_tmp1, y, &q_tmp1, r);
		bi_leftshift(q, WORD_BITLEN);
		(*q)->a[0] += q_tmp1->a[0];
		printf("remainder : ");
		bi_show_hex(r_tmp1);
		printf("\n");
		printf("quotient : ");
		bi_show_hex(*q);
		printf("\n");
	}

	if (x->sign == NEGATIVE) {
		bi_assign(&q_tmp, *q);
		bi_assign(&tmp, *r);
		flip_sign_bi(&q_tmp);
		SUB(q_tmp, one, q);
		SUB(y, tmp, r);

	}
	bi_delete(&q_tmp);
	bi_delete(&tmp);
	bi_delete(&one);
	bi_delete(&r_tmp1);
	bi_delete(&q_tmp1);
}


/**
* @brief int_to_binary : 정수형태의 수를 이진 배열로 표현해주는 함수
* @param int decimal : 이진수로 표현할 정수 
* @param int* binary : 이진수로 구성된 배열
*/
int int_to_binary(int decimal, int* binary ){
	
	int position = 0;
	while (1)
	{
		binary[position] = decimal % 2;// 2로 나누었을 때 나머지를 배열에 저장    
		decimal = decimal / 2;  // 2로 나눈 몫을 저장

		position++;    // 자릿수 변경

		if (decimal == 0)    // 몫이 0이 되면 반복을 끝냄
			break;
	}
	// 배열의 성분은 역순으로 저장 EX : 6-> 110 이지만 배열에는 011로 저장됨.
	return position;
}

/**
* @brief left_to_right : Left to Right 방식의 빅넘버 지수승 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint** t : 결과를 저장할 빅넘버 t
* @param int n : x를 몇번 제곱할지 정해주는 정수 n
* - Pseudo Code
* @image html l2r.jpg
*/
void left_to_right(bigint* x, bigint** t, int n) {

	int l;
	int ll[100] = { 0, };
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = int_to_binary(n, ll);
	bi_set_one(&tmp);

	for (int i = l - 1; i >= 0; i--) {
		SQU(tmp, &ttmp);
		if (ll[i] == 1) {
			MUL(ttmp, x, &tmp);
			bi_show_hex(tmp);
			printf("\n");
		}
		else bi_assign(&tmp, ttmp);
	}
	bi_assign(t, tmp);
	bi_refine(t);

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_print : Left to Right 방식의 빅넘버 지수승 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint** t : 결과를 저장할 빅넘버 t
* @param int n : x를 몇번 제곱할지 정해주는 정수 n
*/
void left_to_right_print(bigint* x, bigint** t, int n) {

	int l;
	int ll[100] = { 0, };
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	l = int_to_binary(n, ll);

	printf("n의 비트길이 %d \n", l);
	for (int i = 0; i < l; i++)
		printf("%d", ll[i]);
	printf("\n\n");

	bi_set_one(&tmp);

	for (int i = l - 1; i >= 0; i--) {
		printf("%d번째 t ^ 2 단계 시작\n\n", i);
		printf("t = ");
		bi_show_hex(tmp);
		printf("\n");
		SQU(tmp, &ttmp);
		printf("t^2 = ");
		bi_show_hex(ttmp);
		printf("\n");
		if (ll[i] == 1) {
			printf("y의 %d번째 비트 == 1 이므로 t * x 단계 시작\n\n", i);
			MUL(ttmp, x, &tmp);
			printf("t * x 후의 t = ");
			bi_show_hex(tmp);
			printf("\n");
		}
		else bi_assign(&tmp, ttmp);
	}
	bi_assign(t, tmp);
	bi_refine(t);

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_bi : Left to Right 방식의 빅넘버 거듭제곱 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint** t : 결과를 저장할 빅넘버 t
*/
void left_to_right_bi(bigint* x, bigint* y, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);

	bi_new(t, 1);
	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		Squaring_Schoolbook(tmp, &ttmp);
		bi_assign(t, ttmp);
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			bi_assign(&tmp, *t);
			MUL(tmp, x, &ttmp);
			bi_assign(t, ttmp);
		}
		// y의 i번째 비트가 0일 때
		else;
	}
	// x가 음수이고, 홀수번 제곱할때 z는 음수가 된다.
	if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_bi_print : Left to Right 방식의 빅넘버 거듭제곱 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint** t : 결과를 저장할 빅넘버 t
*/
void left_to_right_bi_print(bigint* x, bigint* y, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);
	printf("y의 bitlen = %d\n\n", l);

	bi_new(t, 1);
	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		int a = bit_of_bi(y, i);
		printf("%d", a);
	}
	printf("\n\n");

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		printf("제곱전의 t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		SQU(tmp, &ttmp);
		printf("제곱후의 t = ");
		bi_show_hex(ttmp);
		printf("\n\n");
		bi_assign(t, ttmp);
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			printf("y의 %d번째 비트 == 1 이므로 x * t 단계 시작\n\n", i);
			bi_assign(&tmp, *t);
			printf("x * t 전의 t = ");
			bi_show_hex(tmp);
			printf("\n\n");
			MUL(tmp, x, &ttmp);
			printf("x * t 후의 t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(t, ttmp);
		}
		// y의 i번째 비트가 0일 때
		else
			printf("y의 %d번째 비트 == 0 이므로 아무 조치 하지않음\n\n", i);
	}
	// x가 음수이고, 홀수번 제곱할때
	if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_bi : Left to Right 방식의 빅넘버 거듭제곱 나머지 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint* b : 모듈러 연산에 기준이 되는 빅넘버
* @param bigint** t : 결과를 저장할 빅넘버 t
* - Pseudo Code
* @image html l2rmod.jpg
*/
void left_to_right_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);

	bi_set_one(t);

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		SQU(tmp, &ttmp);
		bi_modular(ttmp, b, &tmp);
		bi_assign(t, tmp);
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			bi_assign(&ttmp, *t);
			MUL(ttmp, x, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(t, ttmp);
		}
		// y의 i번째 비트가 0일 때
		else;
	}

	// x가 음수이고, 홀수번 제곱할때 z는 음수가 된다. 
	/*if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;*/

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_mod_bi_print : Left to Right 방식의 빅넘버 거듭제곱 나머지 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint* b : 모듈러 연산에 기준이 되는 빅넘버
* @param bigint** t : 결과를 저장할 빅넘버 t
*/
void left_to_right_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);

	bi_new(t, 1);
	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		printf("제곱전의 t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		Squaring_Schoolbook(tmp, &ttmp);
		printf("제곱후의 t = ");
		bi_show_hex(ttmp);
		printf("\n\n");
		bi_modular(ttmp, b, &tmp);
		printf("모듈러후의 t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		bi_assign(t, tmp);
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			printf("y의 %d번째 비트 == 1 이므로 x * t 단계 시작\n\n", i);
			bi_assign(&ttmp, *t);
			printf("t * x 전의 t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			MUL(ttmp, x, &tmp);
			printf("t * x 후의 t = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular(tmp, b, &ttmp);
			printf("모듈러후의 t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(t, ttmp);
		}
		// y의 i번째 비트가 0일 때
		else
			printf("y의 %d번째 비트 == 0 이므로 아무 조치 하지않음\n\n", i);
	}

	// x가 음수이고, 홀수번 제곱할때
	/*if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;*/

	bi_delete(&tmp);
	bi_delete(&ttmp);
}


/**
* @brief right_to_left : Right to Left 방식의 빅넘버 지수승 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint** z : 결과를 저장할 빅넘버 z
* @param int n : x를 몇번 제곱할지 정해주는 정수 n
* - Pseudo Code
* @image html r2l.jpg
*/
void right_to_left(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	bi_new(&t0, 1);
	t0->a[0] = 0x01;
	bi_assign(&t1, x);

	for (int i = 0; i < l; i++) {
		// n의 i번째 비트가 1일 때
		if (ll[i] == 1) {
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
		}
		else;
		SQU(t1, &tmp);
		bi_assign(&t1, tmp);
	}
	bi_assign(z, t0);
	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief right_to_left_print : Right to Left 방식의 빅넘버 지수승 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint** z : 결과를 저장할 빅넘버 z
* @param int n : x를 몇번 제곱할지 정해주는 정수 n
*/
void right_to_left_print(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	printf("n의 비트길이 %d \n", l);
	for (int i = 0; i < l; i++)
		printf("%d", ll[i]);
	printf("\n\n");

	bi_set_one(&t0);
	bi_assign(&t1, x);

	for (int i = 0; i < l; i++) {
		if (ll[i] == 1) {
			printf("y의 %d번째 비트 == 1 -> t1 * t0 단계 시작\n\n", i);
			printf("t0 = ");
			bi_show_hex(t0);
			printf("\n");
			printf("t1 = ");
			bi_show_hex(t1);
			printf("\n");
			MUL(t1, t0, &tmp);
			printf("t1 * t0  = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_assign(&t0, tmp);
		}
		else {
			printf("y의 %d번째 비트 == 0 PASS\n\n", i);

		}
		printf("%d번째 t1^2 단계 시작\n\n", i);
		printf("t1 = ");
		bi_show_hex(t1);
		printf("\n");
		SQU(t1, &tmp);
		printf("t1^2 = ");
		bi_show_hex(tmp);
		printf("\n\n");
		bi_assign(&t1, tmp);
	}
	bi_assign(z, t0);
	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief right_to_left_bi : Right to Left 방식의 빅넘버승 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint** z : 결과를 저장할 빅넘버 z
*/
void right_to_left_bi(bigint* x, bigint* y, bigint** z) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);


	for (int i = 0; i < l; i++) {
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
		}
		else;
		SQU(t1, &tmp);
		bi_assign(&t1, tmp);
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);

}

/**
* @brief right_to_left_mod_bi : Right to Left 방식의 빅넘버 거듭제곱 나머지 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint* b : 모듈러 연산에 기준이 되는 빅넘버
* @param bigint** z : 결과를 저장할 빅넘버 z
* - Pseudo Code
* @image html r2lmod.jpg
*/
void right_to_left_mod_bi(bigint* x, bigint* y, bigint* b, bigint** z) {
	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_new(&t0, 1);
	t0->a[0] = 0x01;
	bi_assign(&t1, x);


	for (int i = 0; i < l; i++) {
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			MUL(t1, t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t0, ttmp);
		}
		else;
		SQU(t1, &tmp);
		bi_modular(tmp, b, &ttmp);
		bi_assign(&t1, ttmp);
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&ttmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief right_to_left_mod_bi_print : Right to Left 방식의 빅넘버 거듭제곱 나머지 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint* b : 모듈러 연산에 기준이 되는 빅넘버
* @param bigint** z : 결과를 저장할 빅넘버 z
*/
void right_to_left_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** z) {
	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);


	for (int i = 0; i < l; i++) {
		// y의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			printf("y의 %d번째 비트 == 1 이므로 t0 * t1 단계 시작\n\n", i);
			printf("t0 * t1 전의 t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			MUL(t1, t0, &tmp);
			printf("t * x 후의 t = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("모듈러후의 t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t0, ttmp);
		}
		else {
			printf("y의 %d번째 비트 == 0 이므로 PASS\n\n", i);
		}
		printf("제곱전의 t = ");
		bi_show_hex(t0);
		printf("\n\n");
		SQU(t1, &tmp);
		printf("제곱후의 t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		bi_modular_print(tmp, b, &ttmp);
		printf("모듈러후의 t = ");
		bi_show_hex(ttmp);
		printf("\n\n");
		bi_assign(&t1, ttmp);
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&ttmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ : Montgomery Ladder 방식의 빅넘버 지수승 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint** z : 결과를 저장할 빅넘버 z
* @param int n : x를 몇번 제곱할지 정해주는 정수 n
* - Pseudo Code
* @image html mns.jpg
*/
void Mul_N_Squ(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	bi_set_one(&t0);
	bi_assign(&t1, x);
	for (int i = l - 1; i >= 0; i--) {
		// n의 i번째 비트가 1일 때
		if (ll[i] == 1) {
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
			SQU(t1, &tmp);
			bi_assign(&t1, tmp);
		}
		// n의 i번째 비트가 0일 때
		else {
			MUL(t1, t0, &tmp);
			bi_assign(&t1, tmp);
			SQU(t0, &tmp);
			bi_assign(&t0, tmp);
			
		}
	}
	bi_assign(z, t0);
	bi_refine(z);


	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ_print : Montgomery Ladder 방식의 빅넘버 지수승 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint** z : 결과를 저장할 빅넘버 z
* @param int n : x를 몇번 제곱할지 정해주는 정수 n
*/
void Mul_N_Squ_print(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	printf("n의 비트길이 %d \n", l);
	for (int i = 0; i < l; i++)
		printf("%d", ll[i]);
	printf("\n\n");

	bi_set_one(&t0);
	printf("최초 t0 = ");
	bi_show_hex(t0);
	printf("\n\n");
	bi_assign(&t1, x);
	printf("최초 t1 = ");
	bi_show_hex(t1);
	printf("\n\n");
	for (int i = l - 1; i >= 0; i--) {
		// n의 i번째 비트가 1일 때
		if (ll[i] == 1) {
			printf("n의 %d번째 비트 = 1\n\n", ll[i]);
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
			printf("t0 = t1 * t0 = ");
			bi_show_hex(t0);
			printf("\n\n");
			Squaring_Schoolbook(t1, &tmp);
			bi_assign(&t1, tmp);
			printf("t1 = t1 ^ 2 = ");
			bi_show_hex(t1);
			printf("\n\n");
		}
		// n의 i번째 비트가 0일 때
		else {
			printf("n의 %d번째 비트 = 0\n\n", ll[i]);
			MUL(t1, t0, &tmp);
			bi_assign(&t1, tmp);
			printf("t1 = t1 * t0 = ");
			bi_show_hex(t1);
			printf("\n\n");
			SQU(t0, &tmp);
			bi_assign(&t0, tmp);
			printf("t0 = t0 ^ 2 = ");
			bi_show_hex(t0);
			printf("\n\n");
		}
	}
	bi_assign(z, t0);
	bi_refine(z);


	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ_mod_bi : Montgomery Ladder 방식의 빅넘버 거듭제곱 나머지 연산
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint* b : 모듈러 연산에 기준이 되는 빅넘버
* @param bigint** z : 결과를 저장할 빅넘버 z
* - Pseudo Code
* @image html mnsmod.jpg
*/
void Mul_N_Squ_mod_bi(bigint* x, bigint* y, bigint* b, bigint** z){

	int l;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);
	for (int i = l - 1; i >= 0; i--) {
		// n의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			MUL(t1, t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t0, ttmp);
			SQU(t1, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t1, ttmp);
		}
		// n의 i번째 비트가 0일 때
		else {
			MUL(t1, t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t1, ttmp);
			SQU(t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t0, ttmp);
		}
	}
	bi_assign(z, t0);
	bi_refine(z);
	bi_delete(&ttmp);
	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ_mod_bi_print : Montgomery Ladder 방식의 빅넘버 거듭제곱 나머지 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : 거듭제곱할 빅넘버 x
* @param bigint* y : x를 몇번 제곱할지 정해주는 빅넘버 y
* @param bigint* b : 모듈러 연산에 기준이 되는 빅넘버
* @param bigint** z : 결과를 저장할 빅넘버 z
*/
void Mul_N_Squ_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** z) {

	int l;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);

	for (int i = l - 1; i >= 0; i--) {
		// n의 i번째 비트가 1일 때
		if (bit_of_bi(y, i) == 1) {
			printf("y의 %d번째 비트 == 1 이므로 t0 = t0*t1 & t1 = t1^2\n\n", i);
			printf("t0 * t1 전의 t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			MUL(t1, t0, &tmp);
			printf("t0 * t1 후의 t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("모듈러후의 t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t0, ttmp);
			printf("t1^2 전의 t1 = ");
			bi_show_hex(t1);
			printf("\n\n");
			SQU(t1, &tmp);
			printf("t1^2 후의 t1 = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("모듈러후의 t1 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t1, ttmp);
		}
		// n의 i번째 비트가 0일 때
		else {
			printf("y의 %d번째 비트 == 0 이므로 t1 = t0*t1 & t0 = t0^2\n\n", i);
			printf("t0 * t1 전의 t1 = ");
			bi_show_hex(t1);
			printf("\n\n");
			MUL(t1, t0, &tmp);
			printf("t0 * t1 후의 t1 = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("모듈러후의 t1 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t1, ttmp);
			printf("t0^2 전의 t0 = ");
			bi_show_hex(t1);
			printf("\n\n");
			SQU(t0, &tmp);
			printf("t0^2 후의 t0 = ");
			bi_show_hex(t1);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("모듈러후의 t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t0, ttmp);
		}
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&ttmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief modular : 빅넘버 Modular 연산
* @param bigint* x : mod 연산을 취할 빅넘버 x
* @param bigint* y : mod의 기준이 되는 빅넘버 y
* @param bigint** z : 결과를 저장할 빅넘버 z = x (mod y)
*/
void bi_modular(bigint* x, bigint* y, bigint** z) {
	
	// x를 y로 나눈다음에 r만 z 에 저장
	
	bigint* q = NULL;
	bigint* r = NULL;

	if (compareABS(x, y) == -1) {
		bi_assign(z,x);
		return;
	}

	/*if (*z != NULL)
		bi_delete(z);*/
	
	bi_div(x, y, &q, &r);
	bi_assign(z, r);

	bi_delete(&q);
	bi_delete(&r);
}

/**
* @brief bi_modular_print : 빅넘버 Modular 연산
* @brief 중간과정을 콘솔창에 출력하여 연산 이해 및 오류 발생 시점 확인가능
* @param bigint* x : mod 연산을 취할 빅넘버 x
* @param bigint* y : mod의 기준이 되는 빅넘버 y
* @param bigint** z : 결과를 저장할 빅넘버 z = x (mod y)
*/
void bi_modular_print(bigint* x, bigint* y, bigint** z) {

	// x를 y로 나눈다음에 r만 z 에 저장

	bigint* q = NULL;
	bigint* r = NULL;

	if (compareABS(x, y) == -1) {
		bi_assign(z, x);
		return;
	}

	printf("모듈러 시작\n\n");
	if (*z != NULL)
		bi_delete(z);
	printf("z 초기화 \n\n");

	printf("나눗셈 시작\n\n");
	bi_div(x, y, &q, &r);
	printf("모듈러 연산한 나머지 값 = ");
	bi_show_hex(r);
	printf("\n\n");
	bi_assign(z, r);
	printf("r을 x에 복사한 값 = ");
	bi_show_hex(*z);
	printf("\n\n");

	bi_delete(&q);
	bi_delete(&r);
}

/**
* @date 2020-12-07 09:00
*/


