#include "Arithmetic.h"
#include "Basic Operation.h"
#include "conf.h"

void add_test() {
	
	for(int i=0;i<TEST;i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 5);
		//bi_gen_rand(&y, 5);
		bi_gen_rand(&x, rand() % 2, (rand() % 7) + 1);
		bi_gen_rand(&y, rand() % 2, (rand() % 7) + 1);

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

		
		bi_delete(&x);
		bi_delete(&y); // squaring 에서는 안씀
		bi_delete(&z);
	}

}
void sub_test() {
	

	int i = TEST;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, (rand() % 7) + 1);
		bi_gen_rand(&y, rand() % 2, (rand() % 7) + 1);

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


	int i = 80;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		//bi_gen_rand(&x, 3);
		//bi_gen_rand(&y, 3);
		bi_gen_rand(&x, rand()%2,(rand() % 14) + 1);
		bi_gen_rand(&y, rand() % 2, (rand() % 14) + 1);

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
		bi_delete(&y);
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

		bi_gen_rand(&x, rand() % 2, 3);
		bi_gen_rand(&y, rand() % 2, 3);
		/*bi_gen_rand(&x, 1);
		word arr[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		bi_set_by_array(&x, NONNEGATIVE, arr, 7);*/
		//bi_gen_rand(&x, (rand() % 7) + 1);
		//bi_gen_rand(&y, (rand() % 7) + 1);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		karatsuba_MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); 
		bi_delete(&z);
		i--;
	}
}

void bi_binary_long_division_test() {

	for (int i = 0; i < 100; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;
		bi_gen_rand(&x, rand() % 2, 5);
		bi_gen_rand(&y, rand() % 2, 3);
		bi_binary_long_division(x, y, &q, &r);
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

void long_division_2word_test() {
	for (int i = 0; i < 100; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;
		bi_gen_rand(&x, NONNEGATIVE, 2);
		bi_gen_rand(&y, NONNEGATIVE, 1);
		if (x->a[1] >= y->a[0]) {
		}
		else {
			long_division_2word(x, y, &q, &r);
			bi_show_hex(x); printf("=="); printf("("); bi_show_hex(y);
			printf(" * ");
			bi_show_hex(q); printf(")"); printf("+");
			bi_show_hex(r); printf("\n");
		}
		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&q);
		bi_delete(&r);
	}
}

void Squaring_test() {
	

	int i = 25;

	while (i >= 0) {
		bigint* x = NULL;
		bigint* z = NULL;
		/* 원하는 배열을 확인 하고 싶을 때 사용*/
		/*bi_gen_rand(&x, 1);
		word arr[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		bi_set_by_array(&x, NONNEGATIVE, arr, 7);*/
		bi_gen_rand(&x, rand() % 2, (rand() % 14) + 1);
		printf("x=");
		bi_show_hex(x);
		printf("\n");
		Squaring_Schoolbook(x, &z);
		printf("x ^ 2 ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&z);

		i--;
	}
}

void Exponentiation_test() {
	

	int i = 6;
	while (i >= 0) {
		bigint* x = NULL;
		bigint* z = NULL;

		/* 원하는 배열을 확인 하고 싶을 때 사용*/
		bi_gen_rand(&x, rand() % 2, 1);
		word arr[1] = { 0x81 };
		bi_set_by_array(&x, NONNEGATIVE, arr, 1);


		//bi_gen_rand(&x, 3);
		//bi_gen_rand(&x, (rand() % 10) + 1);
		int n = (rand() % 20 + 1);
		//int n = 10;

		printf("x=");
		bi_show_hex(x);
		printf("\n");
		printf("n=%d\n", n);

		//left_to_right(x, &z, 3);
		left_to_right(x, &z, n);

		//printf("x ^ 3 ==");
		printf("x ^ n ==");
		bi_show_hex(z);
		printf("\n");

		bi_delete(&x);
		bi_delete(&z);
		i--;
	}
}