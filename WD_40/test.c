#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include "Arithmetic.h"
#include "Basic Operation.h"
#define TEST 100


void add_test() {
	//FILE* fp = fopen("add_test.txt", "w");
	//bigint* x[TEST] = { NULL, };
	//bigint* y[TEST] = { NULL, };
	//bigint* z[TEST] = { NULL, };

	//for (int i = 0; i < TEST; i++) {
	//	bi_gen_rand(&x[i], 5);
	//	bi_gen_rand(&y[i], 5);
	//	printf("x=");
	//	bi_show_hex(x[i]);
	//	printf("y="); // squaring ¿¡¼­´Â ¾È¾¸
	//	bi_show_hex(y[i]); // squaring ¿¡¼­´Â ¾È¾¸
	//	ADD(x[i], y[i], &z[i]);

	//	printf("x + y ==");
	//	bi_show_hex(z[i]);
	//}



	for (int i = 0; i < TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5); // squaring ¿¡¼­´Â ¾È¾¸

		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring ¿¡¼­´Â ¾È¾¸
		bi_show_hex(y); // squaring ¿¡¼­´Â ¾È¾¸
		ADD(x, y, &z);

		printf("x + y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); // squaring ¿¡¼­´Â ¾È¾¸
		bi_delete(&z);

		free(x);
		free(y); // squaring ¿¡¼­´Â ¾È¾¸
		free(z);

	}
	//}
}
void sub_test() {

	for (int i = 0; i < TEST; i++) {


		bigint* x = NULL;
		bigint* y =  NULL;
		bigint* z =  NULL;

		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5);
		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring ¿¡¼­´Â ¾È¾¸
		bi_show_hex(y); // squaring ¿¡¼­´Â ¾È¾¸
		SUB(x, y, &z);

		printf("x - y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); // squaring ¿¡¼­´Â ¾È¾¸
		bi_delete(&z);

		free(x);
		free(y); // squaring ¿¡¼­´Â ¾È¾¸
		free(z);
	}
	//bigint* x = NULL;
	//bigint* y = NULL;
	//bigint* z = NULL;

	//int i = 20;
	//while (i >= 0) {

	//	bi_gen_rand(&x, 5);
	//	bi_gen_rand(&y, 5); // squaring ¿¡¼­´Â ¾È¾¸

	//	printf("x=");
	//	bi_show_hex(x);
	//	printf("y="); // squaring ¿¡¼­´Â ¾È¾¸
	//	bi_show_hex(y); // squaring ¿¡¼­´Â ¾È¾¸
	//	SUB(x, y, &z);

	//	printf("x - y ==");
	//	bi_show_hex(z);

	//	bi_delete(&x);
	//	bi_delete(&y); // squaring ¿¡¼­´Â ¾È¾¸
	//	bi_delete(&z);

	//	free(x);
	//	free(y); // squaring ¿¡¼­´Â ¾È¾¸
	//	free(z);
	//	i--;
	//}
}

void  mul_test() {

	int i = 100;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;


		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5); // squaring ¿¡¼­´Â ¾È¾¸

		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring ¿¡¼­´Â ¾È¾¸
		bi_show_hex(y); // squaring ¿¡¼­´Â ¾È¾¸
		MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); // squaring ¿¡¼­´Â ¾È¾¸
		bi_delete(&z);

		free(x);
		free(y); // squaring ¿¡¼­´Â ¾È¾¸
		free(z);
		i--;
	}
}


void bi_binary_long_division_test() {
	bigint* x[10] = { NULL, };
	bigint* y[10] = { NULL, };
	bigint* q[10] = { NULL, };
	bigint* r[10] = { NULL, };
	for (int i = 0; i < 10; i++) {
		bi_gen_rand(&x[i], 3);
		bi_gen_rand(&y[i], 2);
	}

	for (int i = 0; i < 10; i++) {
		bi_binary_long_division(x[i], y[i], &q[i], &r[i]);
		bi_show_bin(x[i]); printf("/"); bi_show_bin(y[i]);
		printf(" == ");
		bi_show_bin(q[i]); printf("\n");
		printf("remainder == "); bi_show_bin(r[i]); printf("\n");
	}

}