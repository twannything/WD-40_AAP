#include "Arithmetic.h"
#include "Basic Operation.h"

void add_test() {

	int i = 40;

	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, (rand() % 7) + 1);
		bi_gen_rand(&y, (rand() % 7) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring 에서는 안씀.
		bi_show_hex(y); // squaring 에서는 
		ADD(x, y, &z);

		printf("x + y ==");
		bi_show_hex(z);

		i--;
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
		printf("y="); // squaring 에서는 안씀
		bi_show_hex(y); // squaring 에서는 안씀
		SUB(x, y, &z);

		printf("x - y ==");
		bi_show_hex(z);

		i--;
	}
}

void  mul_test() {


	int i = 20;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 3);
		//bi_gen_rand(&y, 3);
		bi_gen_rand(&x, (rand() % 2) + 1);
		bi_gen_rand(&y, (rand() % 2) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);

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

void Squaring_test() {
	

	int i = 3;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 2);
		bi_gen_rand(&x, (rand() % 10) + 1);
		printf("x=");
		bi_show_hex(x);
		Squaring_Schoolbook(x, &z);
		printf("x ^ 2 ==");
		bi_show_hex(z);

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