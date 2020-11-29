#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<math.h>

#define _CRT_SECURE_NO_WARNINGS
#define WORD_BITLEN 8

#if WORD_BITLEN == 64
typedef unsigned long long word;
#define MASK 0xffffffffffffffff
#define MASKMUL 0xffffffff
#elif WORD_BITLEN == 32
typedef unsigned int word;
#define MASK 0xffffffff
#define MASKMUL 0xffff
#else 
typedef unsigned char word;
#define MASK 0xff
#define MASKMUL 0xf
#endif

#define NONNEGATIVE 0
#define NEGATIVE 1

typedef unsigned char byte;

typedef struct {
	int sign; // NEGATIVE or NON-NEGATIVE
	int wordlen; // wordlen >=0
	word* a; // address for big integer(starting address)
}bigint;

void array_init(word* a, int wordlen);
void array_copy(word* a, word* b, int wordlen);
void array_rand(word* dst, int wordlen);


void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);

void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
//void bi_set_by_stirng(bigint** x, int sign, char* str, word base);

void bi_show_hex(bigint* x);
//void bi_show_dec(bigint* x);
void bi_show_bin(bigint* x);
void bi_refine(bigint* x);
void bi_assign(bigint** y, bigint* x);

void bi_gen_rand(bigint** x, int wordlen);

int get_word_length(bigint* x);
int get_bit_length(bigint* x);
int bit_of_bi(bigint* x, int j);

int get_sign_bi(bigint* x);
void flip_sign_bi(bigint** x);

void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int bi_is_zero(bigint* x);
int bi_is_one(bigint* x);

int compareABS(bigint* x, bigint* y);
int compareAB(bigint* x, bigint* y);
void bi_leftshift(bigint** x, int r);
void bi_rightshift(bigint** x, int r);