#pragma once
#include "Basic Operation.h"
 
// Ä«¶óÃ÷¹Ù °ö¼Á, Á¦°ö, ³ª´°¼À, Áö¼ö½Â, 8 32 64 È£È¯, ºÎÈ£ ±æÀÌ Â÷ÀÌ³¯¶§ , 

// Chapter 3.1 ¸ðµâ·¯ ¿¬»ê
void bi_reduction(bigint** y, bigint* x, int r);

// Chapter 3.2 µ¡¼À ¿¬»ê
int S_ADDABc(word x, word y, bigint** z, int carry, int r);
void M_ADD(bigint* x, bigint* y, bigint** z);
void ADD(bigint* x, bigint* y, bigint** z);

// Chapter 3.3 »¬¼À ¿¬»ê
int S_SUBABb(bigint* x, bigint* y, bigint** z, unsigned int b, int j);
void SUB_C(bigint* x, bigint* y, bigint** z);
void SUB(bigint* x, bigint* y, bigint** z);

// Chapter 3.4 °ö¼À ¿¬»ê
void MULC(word x, word y, word* tmp);
void MUL(bigint* x, bigint* y, bigint** z);
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z);
void karatsuba_MUL(bigint* x, bigint* y, bigint** z);

// Chapter 3.5 ³ª´°¼À ¿¬»ê
void binary_long_division(int a, int b, int* q, int* r);
void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r);
void long_division_2word(bigint* x, bigint* y, bigint** q, bigint** r);
void divcc(bigint* x, bigint* y, bigint** q, bigint** r);
void divc(bigint* x, bigint* y, bigint** q, bigint** r);
void bi_div(bigint* x, bigint* y, bigint** q, bigint** r);

// Chapter 3.6 Á¦°ö ¿¬»ê
void Squaring_word(word* dst, word a);
void Squaring_Schoolbook(bigint* x, bigint** z);

// Chapter 3.7 Áö¼ö½Â ¿¬»ê
void left_to_right(bigint* x, bigint** z, int n);
void left_to_right_bi(bigint* x, bigint* y, bigint** t);
void left_to_right_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t);
void right_to_left(bigint* x, bigint** z, int n);
void right_to_left_bi(bigint* x, bigint* y, bigint** t);
void right_to_left_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t);





void modular_bi(bigint* x, bigint* y, bigint** z);
