#define _CRT_SECURE_NO_WARNINGS
#include "Basic Operation.h"
#include "Arithmetic.h"
//#include <vld.h> // �޸� ������ Ȯ�� �ϰ� ������ ���

/** @mainpage BIGINT LIBRARY : WD-40
* @section devleoper ������
* - ���¿�, ������
* @image html 11.jpg
* @section advenced  ���߸���
* - C��� �Թ��ڵ��� ���� ���α׷��� �ǽ� ������
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
