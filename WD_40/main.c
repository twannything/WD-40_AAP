#define _CRT_SECURE_NO_WARNINGS
#include "Basic Operation.h"
#include "Arithmetic.h"
//#include <vld.h> // 메모리 누수를 확인 하고 싶을때 사용

/** @mainpage BIGINT LIBRARY : WD-40
* @section devleoper 개발자
* - 김태완, 유현도
* @image html 1.jpg
* @section advenced  개발목적
* - C언어 입문자들을 위한 프로그래밍 실습 교보재
* @version ver 1.0
* @date 2020.12.05
*/

int main() {

	errno_t err;
	FILE* fp = NULL;
	err = fopen_s(&fp, "C:\\Users\\user\\Desktop\\data.sage", "w");//나온 출력값이 맞는지 확인하는 함수이다.
	if (fp == NULL) {
		puts("파일 오픈 실패\n");
		return -1;
	}
	//add_test(fp);
	//sub_test(fp);
	//mul_test(fp);
	//Ka_mul_test(fp);
	//bi_binary_long_division_test(fp);
	//long_division_2word_test(fp);
	//divcc_test();
	//div_test();
	//divc_test();
	//Squaring_test(fp);
	L2R_test(fp);
	//L2R_bi_test(fp);
	//L2R_Modular_bi_test(fp);
	//R2L_test(fp);
	//R2L_bi_test(fp);
	//R2L_Modular_bi_test(fp);
	//Mul_N_Squ_test(fp);
	//Mul_N_Squ_bi_test(fp);
	//Mul_N_Squ_mod_bi_test(fp);
}
