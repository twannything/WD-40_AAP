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
	
	for (int i = 0; i <= TEST; i++) {
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

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("print(x + y ==",fp);
		File_print(z,fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/
		
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

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("print(x - y ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

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

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("print(x * y ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

/**
* @brief bi_binary_long_division_test : 이진 롱 나눗셈 연산의 구현 정확성 테스트 하는 함수
* @brief 구성 : 빅넘버 x 와 y 그리고 x / y 값의 몫 과 나머지를 저장할 빅넘버 q, r 를 생성
* @brief x 와 y의 부호 : NONNEGATIVE or NEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void bi_binary_long_division_test(FILE* fp) {

	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));

		printf("x = "); bi_show_hex(x); printf("\n");
		printf("y = "); bi_show_hex(y); printf("\n");
		bi_binary_long_division(x, y, &q, &r);
		if (bi_is_zero(q) && bi_is_zero(r)) {
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

			//fputs("x=", fp);
			//File_print(x, fp);
			//fprintf(fp, "\n");
			//fputs("y=", fp);
			//File_print(y, fp);
			//fprintf(fp, "\n");
			//fputs("q=", fp);
			//File_print(q, fp);
			//fprintf(fp, "\n");
			//fputs("r=", fp);
			//File_print(r, fp);
			//fprintf(fp, "\n");

			////print(x//y==q,x%y==r)
			//fputs("print(x", fp);
			//fputs("//y", fp);
			//fputs("==q", fp);
			//fputs(",x", fp);
			//fputs("%y", fp);
			//fputs("==r", fp);
			//fputs(")\n", fp);

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
* @brief x 와 y의 부호 : NONNEGATIVE or NEGATIVE
* @brief x 와 y의 wordlen : LOWERBOUND ~ UPPERBOUND
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void div_test(FILE* fp) {
	
	for (int i = 0; i <= TEST; i++) {

		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		printf("x = "); bi_show_hex(x); printf("\n");
		printf("y = "); bi_show_hex(y); printf("\n");
		bi_div(x, y, &q, &r);
		//bi_div_print(x, y, &q, &r);
		if (bi_is_zero(q) && bi_is_zero(r)) {
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

			/*fputs("x=", fp);
			File_print(x, fp);
			fprintf(fp, "\n");
			fputs("y=", fp);
			File_print(y, fp);
			fprintf(fp, "\n");
			fputs("q=", fp);
			File_print(q, fp);
			fprintf(fp, "\n");
			fputs("r=", fp);
			File_print(r, fp);
			fprintf(fp, "\n");

			fputs("print(x", fp);
			fputs("//y", fp); 
			fputs("==q", fp);
			fputs(",x", fp); 
			fputs("%y", fp); 
			fputs("==r", fp);
			fputs(")\n", fp);*/

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
		//SQU_print(x, &z); 
		
		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("power(x,2) ==");
		bi_show_hex(z);
		printf("\n\n");
		
		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("print(x * x ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

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
		left_to_right(x, &z, n);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);
		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n");

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("n=", fp);
		fprintf(fp, "%d", n);
		fprintf(fp, "\n");
		fputs("print(power(x,n) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

		bi_delete(&x);
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

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("p=", fp);
		File_print(p, fp);
		fprintf(fp, "\n");
		fputs("print(power_mod(x,y,p) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

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

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);
		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n\n");

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("n=", fp);
		fprintf(fp, "%d", n);
		fprintf(fp, "\n");
		fputs("print(power(x,n) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

		bi_delete(&x);
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
		
		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("p=", fp);
		File_print(p, fp);
		fprintf(fp, "\n");
		fputs("print(power_mod(x,y,p) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

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

		//bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		//int n = 5;
		//Mul_N_Squ_print(x, &z, n);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);
		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n");

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("n=", fp);
		fprintf(fp, "%d", n);
		fprintf(fp, "\n");
		fputs("print(power(x,n) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

		bi_delete(&x);
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

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("p=", fp);
		File_print(p, fp);
		fprintf(fp, "\n");
		fputs("print(power_mod(x,y,p) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&p);
		bi_delete(&z);
	}

}

/**
* @brief Mod_test : 모듈러 지수승 연산에 사용되는 모듈러 함수의 구현 정확성을 테스트 하는 함수
* @brief 구성 : 빅넘버 x , 모듈러 기준을 결정하는 빅넘버 y ,  x mod y 값을 저장할 빅넘버 z
* @brief x의 부호 : NONNEGATIVE or NEGATIVE
* @brief x의 wordlen : LOWERBOUND ~ UPPERBOUND
* @brief y의 부호 : NONNEGATIVE
* @brief y의 범위 : x의 wordlen / 2 
* @param FILE* fp : sage로 정확성을 검증하기 위해 파일 fp에 결과 프린트
*/
void Mod_test(FILE* fp) {
	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL; // 거듭제곱 할 수
		bigint* y = NULL; // 거듭제곱 횟 수
		bigint* z = NULL; // 결과 저장 할 수
		bigint* p = NULL; // mod 연산 할 기준(=법)

		bi_gen_rand(&x, rand() % 2, ((rand() % (UPPERBOUND + 1 - LOWERBOUND)) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, (x->wordlen / 2));
		bi_modular(x, y, &z);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		printf("mod(x,y) ==");
		bi_show_hex(z);
		printf("\n");

		/*fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");
		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");
		fputs("print(mod(x,y) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");*/

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}