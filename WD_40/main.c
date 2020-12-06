#define _CRT_SECURE_NO_WARNINGS
#include "Basic Operation.h"
#include "Arithmetic.h"
//#include <vld.h> // 메모리 누수를 확인 하고 싶을때 사용

/** @mainpage BIGINT LIBRARY : WD-40
* @section devleoper 개발자
* - 김태완, 유현도
* @image html 11.jpg
* @section advenced  개발목적
* - C언어 입문자들을 위한 프로그래밍 실습 교보재
* @version ver 1.0
* @date 2020.12.06
*/

int main() {

	add_test();
	sub_test();
	mul_test();
	bi_binary_long_division_test();
	div_test();
	Squaring_test();
	L2R_test();
	L2R_bi_test();
	L2R_Modular_bi_test();
	R2L_test();
	R2L_bi_test();
	R2L_Modular_bi_test();
	Mul_N_Squ_test();
	Mul_N_Squ_bi_test();
	Mul_N_Squ_mod_bi_test();
}
