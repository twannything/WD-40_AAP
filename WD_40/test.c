#pragma once
#include "Arithmetic.h"
#include "Basic Operation.h"
#include <stdio.h>

void ADD_test() {
	bigint* x[100] = { NULL, };
	bigint* y[100] = { NULL, };
	bigint* z[100] = { NULL, };

	for (int i = 0; i < 100; i++) {
		bi_gen_rand(&x[i], (rand() & 0xff) % 2, 3);
		bi_gen_rand(&y[i], (rand() & 0xff) % 2, 3);
		ADD(x[i], y[i], &z[i]);
		bi_show_bin(x[i]); printf("+"); bi_show_bin(y[i]); printf("=="); bi_show_bin(z[i]);printf("\n");
	}
}

void bi_binary_long_division_test() {
	bigint* x[10] = { NULL, };
	bigint* y[10] = { NULL, };
	bigint* q[10] = { NULL, };
	bigint* r[10] = { NULL, };
	for (int i = 0; i < 10; i++) {
		bi_gen_rand(&x[i], NONNEGATIVE, 3);
		bi_gen_rand(&y[i], NONNEGATIVE, 2);
	}

	for (int i = 0; i < 10; i++) {
		bi_binary_long_division(x[i], y[i], &q[i], &r[i]);
		bi_show_bin(x[i]); printf("=="); bi_show_bin(y[i]); printf("*"); bi_show_bin(q[i]); printf("+"); bi_show_bin(r[i]); printf("\n");

	}

}