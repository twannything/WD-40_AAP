#include "Arithmetic.h"
#include "Basic Operation.h"
#define TEST 100

void add_test() {
	int i = TEST;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 5);
		//bi_gen_rand(&y, 5);
		bi_gen_rand(&x, (rand() % 7) + 1);
		bi_gen_rand(&y, (rand() % 7) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y="); 
		bi_show_hex(y);
		printf("\n");
		ADD(x, y, &z);

		printf("x + y ==");
		bi_show_hex(z);
		printf("\n");

		i--;
		bi_delete(&x);
		bi_delete(&y); // squaring ������ �Ⱦ�
		bi_delete(&z);
	}

}
void sub_test() {
	

	int i = 40;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, (rand() % 7) + 1);
		bi_gen_rand(&y, (rand() % 7) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		SUB(x, y, &z);

		printf("x - y ==");
		bi_show_hex(z);
		printf("\n");

		i--;
	}
}

void  mul_test() {


	int i = 40;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 3);
		//bi_gen_rand(&y, 3);
		bi_gen_rand(&x, (rand() % 7) + 1);
		bi_gen_rand(&y, (rand() % 7) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("y=");
		bi_show_hex(y);
		printf("\n");
		MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);
		printf("\n");
		bi_delete(&x);
		bi_delete(&y); // squaring ������ �Ⱦ�
		bi_delete(&z);

		i--;
	}
}

void Ka_mul_test() {

	
	int i = 10;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, 3);
		bi_gen_rand(&y, 3);
		//bi_gen_rand(&x, (rand() % 7) + 1);
		//bi_gen_rand(&y, (rand() % 7) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		karatsuba_MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);

		i--;
	}
}

void bi_binary_long_division_test() {

	for (int i = 0; i < 100; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;
		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 3);
		bi_binary_long_division(x, y, &q, &r);
		bi_show_hex(x); printf("=="); printf("("); bi_show_hex(y);
		printf(" * ");
		bi_show_hex(q); printf(")"); printf("+");
		bi_show_hex(r); printf("\n");

	}

}

void Squaring_test() {
	

	int i = 100;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 2);
		bi_gen_rand(&x, (rand()%7)+1);
		printf("x=");
		bi_show_hex(x);
		printf("\n");
		Squaring_Schoolbook(x, &z);
		printf("x ^ 2 ==");
		bi_show_hex(z);
		printf("\n");

		i--;
	}
}

void Exponentiation_test() {
	

	int i = 3;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, 2);


		printf("x=");
		bi_show_hex(x);
		//printf("n=%d", n);

		left_to_right(x, &z, 2);
		//left_to_right(x, &z, n);

		printf("x ^ 2 ==");
		//printf("x ^ n ==");
		bi_show_hex(z);

		i--;
	}
}