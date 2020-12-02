#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Basic Operation.h"
 
// ī������ ����, ����, ������, ������, 8 32 64 ȣȯ, ��ȣ ���� ���̳��� , 

// Chapter 3.1 ��ⷯ ����
void bi_reduction(bigint** y, bigint* x, int r);

// Chapter 3.2 ���� ����
int S_ADDABc(word x, word y, bigint** z, int carry, int r);
void M_ADD(bigint* x, bigint* y, bigint** z);
void ADD(bigint* x, bigint* y, bigint** z);

// Chapter 3.3 ���� ����
int S_SUBABb(bigint* x, bigint* y, bigint** z, unsigned int b, int j);
void SUB_C(bigint* x, bigint* y, bigint** z);
void SUB(bigint* x, bigint* y, bigint** z);

// Chapter 3.4 ���� ����
void MULC(word x, word y, word* tmp);
void MUL(bigint* x, bigint* y, bigint** z);
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z);
void karatsuba_MUL(bigint* x, bigint* y, bigint** z);

// Chapter 3.5 ������ ����
void binary_long_division(int a, int b, int* q, int* r);
void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r);
void long_division_2word(bigint* x, bigint* y, bigint** q, bigint** r);

// Chapter 3.6 ���� ����
void Squaring_word(word* dst, word a);
void Squaring_Schoolbook(bigint* x, bigint** z);

// Chapter 3.7 ������ ����
void left_to_right(bigint* x, bigint** z, int n);

// Chapter 3.8 ��ⷯ ������ ����

