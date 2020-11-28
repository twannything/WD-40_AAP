#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Basic Operation.h"
 
// Ä«¶óÃ÷¹Ù °ö¼Á, Á¦°ö, ³ª´°¼À, Áö¼ö½Â, 8 32 64 È£È¯, ºÎÈ£ ±æÀÌ Â÷ÀÌ³¯¶§ , 

void bi_reduction(bigint** y, bigint* x, int r);
int S_ADDABc(word x, word y, bigint** z, unsigned int carry, int r);
void M_ADD(bigint* x, bigint* y, bigint** z);
int S_SUBABb(bigint* x, bigint* y, bigint** z, unsigned int b, int j);
void SUB_C(bigint* x, bigint* y, bigint** z);
void ADD(bigint* x, bigint* y, bigint** z);
void SUB(bigint* x, bigint* y, bigint** z);
void MULC(word x, word y, word* tmp);
void MUL(bigint* x, bigint* y, bigint** z);
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z);
void karatsuba_MUL(bigint* x, bigint* y, bigint** z);
void Squaring_word(word* dst, word a);
void Squaring_Schoolbook(bigint* x, bigint** z);
void binary_long_division(int a, int b, int* q, int* r);
void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r);
void left_to_right(bigint* x, bigint** z, int n);

