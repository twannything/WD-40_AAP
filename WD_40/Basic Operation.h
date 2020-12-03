#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "conf.h"

#define _CRT_SECURE_NO_WARNINGS

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

// Chapter 2.1 빅넘버를 생성하는 함수 & 삭제하는 함수
void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);

// Chapter 2.2 배열과 문자열로 받은 입력을 빅넘버에 저장하는 함수 & 빅넘버를 출력하는 함수 
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
//void bi_set_by_stirng(bigint** x, int sign, char* str, word base);
void bi_show_hex(bigint* x);
//void bi_show_dec(bigint* x);
void bi_show_bin(bigint* x);
void File_print(bigint* x, FILE* fp);

// Chapter 2.3 빅넘버 0000017398213 -> 17398213 으로 만들어 주는 함수
void bi_refine(bigint** x);

// Chapter 2.4 빅넘버를 복사하는 함수
void bi_assign(bigint** y, bigint* x);

// Chapter 2.5 빅넘버를 랜덤하게 생성하는 함수
void bi_gen_rand(bigint** x, int sign, int wordlen);

// Chapter 2.6 빅넘버의 워드길이, 비트길이, j번째 비트를 출력하는 함수
int get_word_length(bigint* x);
int get_bit_length(bigint* x);
int bit_of_bi(bigint* x, int j);

// Chapter 2.7 빅넘버의 워드길이, 비트길이, j번째 비트를 출력하는 함수
int get_sign_bi(bigint* x);
void flip_sign_bi(bigint** x);

// Chapter 2.8 빅넘버를 0 이나 1로 set하는 함수 & 0 이나 1인지 확인하는 함수
void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int bi_is_zero(bigint* x);
int bi_is_one(bigint* x);

// Chapter 2.9 두 빅넘버를 비교하여 무엇이 더 큰지 출력하는 함수
int compareABS(bigint* x, bigint* y);
int compareAB(bigint* x, bigint* y);

// Chapter 2.10 빅넘버를 r비트 left 또는 right로 shift 해주는 함수 
void bi_leftshift(bigint** x, int r);
void bi_rightshift(bigint** x, int r);