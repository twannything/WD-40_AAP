#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Basic Operation.h"

int S_ADDABc(word x, word y, bigint** z, int carry, int r);
void M_ADD(bigint* x, bigint* y, bigint** z);
int S_SUBABb(bigint* x, bigint* y, bigint** z, int b, int j);
void SUB_C(bigint* x, bigint* y, bigint** z);
void ADD(bigint* x, bigint* y, bigint** z);
void SUB(bigint* x, bigint* y, bigint** z);
void MULC(bigint* x, bigint* y, bigint** z, int i, int j);
void MUL(bigint* x, bigint* y, bigint** z);
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z);
void binary_long_division(int a, int b, int* q, int* r);
void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r);

void add_test();
void sub_test();
void mul_test();
void bi_binary_long_division_test();