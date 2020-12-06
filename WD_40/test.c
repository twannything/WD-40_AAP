#pragma once
#include "Arithmetic.h"

/**
* @brief add_test : 덧셈 연산의 구현 정확성 테스트 하는 함수
* @brief 구성 : 빅넘버 x 와 y 그리고 x + y 값을 저장할 빅넘버 z 를 생성
* @brief x 와 y의 부호 : NONNEGATIVE or NEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void add_test(FILE* fp) {
	
	for (int i = 0; i < TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		ADD(x, y, &z);
		//ADD_print(x, y, &z);

		

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n\n");	
		printf("x + y ==");
		bi_show_hex(z);
		printf("\n\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief sub_test : 뺄셈 연산의 구현 정확성 테스트 하는 함수
* @brief 구성 : 빅넘버 x 와 y 그리고 x - y 값을 저장할 빅넘버 z 를 생성
* @brief x 와 y의 부호 : NONNEGATIVE or NEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void sub_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		SUB(x, y, &z);
		//SUB_print(x, y, &z);	

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n\n");
		printf("x - y ==");
		bi_show_hex(z);
		printf("\n\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief mul_test : 뺄셈 연산의 구현 정확성 테스트 하는 함수
* @brief 구성 : 빅넘버 x 와 y 그리고 x * y 값을 저장할 빅넘버 z 를 생성
* @brief x 와 y의 부호 : NONNEGATIVE or NEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void  mul_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		MUL(x, y, &z);
		//MUL_print(x, y, &z);		

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("x * y ==");
		bi_show_hex(z);
		printf("\n\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief bi_binary_long_division_test : 이진 롱 나눗셈 연산의 구현 정확성 테스트 하는 함수
* @brief 구성 : 빅넘버 x 와 y 그리고 x / y 값의 몫 과 나머지를 저장할 빅넘버 q, r 를 생성
* @brief x 와 y의 부호 : NONNEGATIVE or NEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND (?)
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void bi_binary_long_division_test(FILE* fp) {

	for (int i = 0; i < TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;

		bi_gen_rand(&x, rand() % 2, 5);
		bi_gen_rand(&y, rand() % 2, 3);
		bi_binary_long_division(x, y, &q, &r);
		if (bi_is_zero(q) && bi_is_zero(r)) {
			//printf(" Invalid Operation or X is Zero !\n");
			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&q);
			bi_delete(&r);
		}
		else {
			bi_show_hex(x); printf("=="); printf("("); bi_show_hex(y);
			printf(" * ");
			bi_show_hex(q); printf(")"); printf("+");
			bi_show_hex(r); printf("\n");

			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&q);
			bi_delete(&r);
		}
	}

}

/**
* @brief div_test :
* @brief 구성 : 빅넘버 x 와 y 그리고 x / y 값의 몫 과 나머지를 저장할 빅넘버 q, r 를 생성
* @brief x 와 y의 부호 : NONNEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND (?)
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void div_test(FILE* fp) {
	for (int i = 0; i < TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;
		bi_gen_rand(&x, rand() % 2, (rand() % 6) + 1);
		bi_gen_rand(&y, rand() % 2, (rand() % 6) + 1);
		bi_div(x, y, &q, &r);
		if (bi_is_zero(q) && bi_is_zero(r)) {
			//printf(" Invalid Operation or X is Zero !");
			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&q);
			bi_delete(&r);
		}
		else {
			bi_show_hex(x); printf("=="); printf("("); bi_show_hex(y);
			printf(" * ");
			bi_show_hex(q); printf(")"); printf("+");
			bi_show_hex(r); printf("\n");

			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&q);
			bi_delete(&r);
		}
	}
}

/**
* @brief Squaring_test : 빅넘버 제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x 와 x^2 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND 
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void Squaring_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* z = NULL;
		
		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		SQU(x, &z);
		//SQU_print(x, &z); /* 중간과정을 콘솔창에서 확인하고 싶을때 사용 */
		
		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("power(x,2) ==");
		bi_show_hex(z);
		printf("\n\n");
		
		bi_delete(&x);
		bi_delete(&z);
	}
}

/**
* @brief L2R_test : Left to Right 방식의 거듭제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 n , x^n 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief n의 부호 : NONNEGATIVE
* @brief n의 범위 : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void L2R_test(FILE* fp) {
	for (int i = 0; i <= TEST; i++) {
		
		bigint* x = NULL;
		bigint* z = NULL;
		
		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		int n = ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND);

		//left_to_right(x, &z, n);
		left_to_right_print(x, &z, n);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);
		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&z);
	}
}

/**
* @brief L2R_bi_test : Left to Right 방식의 빅넘버 거듭제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y , x^y 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : 1 (2 이상은 결과 값이 너무 커져 테스트하기 한계가 있음)
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void L2R_bi_test(FILE* fp) {


	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, 1);

		left_to_right_bi(x, y, &z);
		//left_to_right_bi_print(x, y, &z);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("power(x,y) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief L2R_Modular_bi_test : Left to Right 방식의 빅넘버 거듭제곱 모듈러 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y , 모듈러 기준을 결정하는 빅넘버 p ,  x^y mod p 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : LOWERBOUND ~ UPPERBOUND
* @brief p의 부호 : NONNEGATIVE
* @brief p의 범위 : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void L2R_Modular_bi_test(FILE* fp) {


	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL; // 거듭제곱 할 수
		bigint* y = NULL; // 거듭제곱 횟 수
		bigint* z = NULL; // 결과 저장 할 수
		bigint* p = NULL; // mod 연산 할 기준(=법)

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&p, NONNEGATIVE, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		left_to_right_mod_bi(x, y, p, &z);
		//left_to_right_mod_bi_print(x, y, p, &z);

		

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("p=");
		bi_show_hex(p);
		printf("\n");
		printf("power_mod(x,y,p) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&p);
		bi_delete(&z);
	}
}

/**
* @brief R2L_test : Right to Left 방식의 거듭제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 n , x^n 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief n의 부호 : NONNEGATIVE
* @brief n의 범위 : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void R2L_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {

		bigint* x = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		int n = ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND);

		right_to_left_print(x, &z, n);
		//right_to_left(x, &z, n);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);
		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n\n");

		bi_delete(&x);
		bi_delete(&z);
	}
}

/**
* @brief R2L_bi_test : Right to Left 방식의 빅넘버 거듭제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y ,  x ^ y 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : 1
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void R2L_bi_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, 1); // y->wordlen이 1이아니면 너무 큰 값이 나와버림 

		right_to_left_bi(x, y, &z);
		//right_to_left_bi_print(x, y, &z);
		
		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("power(x,y) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief R2L_Modular_bi_test : Right to Left 방식의 빅넘버 거듭제곱 모듈러 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y , 모듈러 기준을 결정하는 빅넘버 p ,  x^y mod p 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : LOWERBOUND ~ UPPERBOUND
* @brief p의 부호 : NONNEGATIVE
* @brief p의 범위 : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void R2L_Modular_bi_test(FILE* fp) {
	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL; // 거듭제곱 할 수
		bigint* y = NULL; // 거듭제곱 횟 수
		bigint* z = NULL; // 결과 저장 할 수
		bigint* p = NULL; // mod 연산 할 기준(=법)

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&p, NONNEGATIVE, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		right_to_left_mod_bi(x, y, p, &z);
		//right_to_left_mod_bi_print(x, y, p, &z);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("p=");
		bi_show_hex(p);
		printf("\n");
		printf("power_mod(x,y,p) ==");
		bi_show_hex(z);
		printf("\n");
		
		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&p);
		bi_delete(&z);
	}
}

/**
* @brief Mul_N_Squ_bi_test : Montgomery 방식의 빅넘버 거듭제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y , x ^ y 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief n의 부호 : NONNEGATIVE
* @brief n의 범위 : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void Mul_N_Squ_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {

		bigint* x = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		int n = ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND);

		Mul_N_Squ(x, &z, n);
		//Mul_N_Squ_print(x, &z, n);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);
		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&z);
	}

}

/**
* @brief Mul_N_Squ_bi_test : Montgomery 방식의 빅넘버 거듭제곱 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y , x ^ y 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : 1
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void Mul_N_Squ_bi_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, 1); // y->wordlen이 1이아니면 너무 큰 값이 나와버림 

		Mul_N_Squ_bi(x, y, &z);
		//Mul_N_Squ_bi_print(x, y, &z);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("power(x,y) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief Mul_N_Squ_mod_bi_test : Montgomery 방식의 빅넘버 거듭제곱 모듈러 연산의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 제곱횟수를 결정하는 빅넘버 y , 모듈러 기준을 결정하는 빅넘버 p ,  x^y mod p 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : LOWERBOUND ~ UPPERBOUND
* @brief p의 부호 : NONNEGATIVE
* @brief p의 범위 : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void Mul_N_Squ_mod_bi_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL; // 거듭제곱 할 수
		bigint* y = NULL; // 거듭제곱 횟 수
		bigint* z = NULL; // 결과 저장 할 수
		bigint* p = NULL; // mod 연산 할 기준(=법)

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&p, NONNEGATIVE, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		Mul_N_Squ_mod_bi(x, y, p, &z);
		//Mul_N_Squ_mod_bi_print(x, y, p, &z);

		printf("x=");
		bi_show_hex(x);
		printf("\n");	
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("p=");
		bi_show_hex(p);
		printf("\n");
		printf("power_mod(x,y,p) ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&p);
		bi_delete(&z);
	}

}