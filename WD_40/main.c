#define _CRT_SECURE_NO_WARNINGS
#include "Basic Operation.h"
#include "Arithmetic.h"

int main() {
	
	bigint* p[5] = { NULL, };
	bigint* n[5] = { NULL, };
	bigint* az[5] = { NULL, };
	bigint* sz[5] = { NULL, };
	bigint* mz[5] = { NULL, };
	for (int i = 0; i < 5; i++) {
		bi_gen_rand(&p[i],NONNEGATIVE,3);
		bi_gen_rand(&n[i],NEGATIVE, 3);
	}


	for (int i = 0; i < 5; i++) {
		printf("%d-th Nonegative Big Interger = ", i);
		bi_show_hex(p[i]);
	}
	printf("\n");
	for (int i = 0; i < 5; i++) {
		printf("%d-th Negative Big Interger = ", i);
		bi_show_hex(n[i]);
	}

	printf("\n*********Result*********\n");

	for (int i = 0; i < 5; i++) {
		ADD(p[i], n[i], &az[i]);
		SUB(p[i], n[i], &sz[i]);
		Schoolbook_MUL(p[i], n[i], &mz[i]);
		printf("\n%d-th Add result : ", i);
		bi_show_hex(az[i]);
		printf("%d-th Sub result : ", i);
		bi_show_hex(sz[i]);
		printf("%d-th Mul result : ", i);
		bi_show_hex(mz[i]);
	}






	bi_show_bin(p[1]);
	bi_leftshift(&p[1], WORD_BITLEN - 1);
	bi_show_bin(p[1]);
	bi_leftshift(&p[1], WORD_BITLEN);
	bi_show_bin(p[1]);
	bi_leftshift(&p[1], WORD_BITLEN + 1);
	bi_show_bin(p[1]);
	bi_show_bin(p[2]);
	bi_rightshift(&p[2], WORD_BITLEN);
	bi_show_bin(p[2]);
	bi_rightshift(&p[2], WORD_BITLEN - 1);
	bi_show_bin(p[2]);
	

}

