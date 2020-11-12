#define _CRT_SECURE_NO_WARNINGS
#include "bi.h"

int main() {
	
	bigint* x = NULL;
	bigint* hd = NULL;

	///*Create BigInt, Delete BigInt, Zerorize BigInt*/
	//bi_new(&x, 4);

	//printf("sign = %d\n", x->sign);
	//printf("wordlen = %d\n", x->wordlen);
	//printf("address = %p\n", x->a);
	//printf("\n");

	///*Set BigInt by array*/
	//word arr1[3] = { 0x33,0xff,0xfe };
	//bi_set_by_array(&x, NONNEGATIVE, arr1, sizeof(arr1)/sizeof(arr1[0]));
	//printf("sign = %d\n", x->sign);
	//printf("wordlen = %d\n", x->wordlen);
	//printf("address = %p\n", x->a);
	//printf("\n");

	///*Set BigInt by string*/

	///*Show Bigint Binary*/
	//printf("Binary Big Integer = ");
	//bi_show_bin(x);
	//printf("\n");

	///*Show Bigint hex, dec*/

	///*Refine BigInt*/
	//word arr2[4] = { 0x00,0x33,0xff,0xfe };
	//bi_set_by_array(&x, NONNEGATIVE, arr2, sizeof(arr2) / sizeof(arr2[0]));
	//printf("sign = %d\n", x->sign);
	//printf("wordlen = %d\n", x->wordlen);
	//printf("address = %p\n", x->a);
	//printf("Before Refine = ");
	//bi_show_bin(x);
	//bi_refine(x);
	//printf("refine BigInt = ");
	//bi_show_bin(x);
	//printf("\n");

	///*Assign BigInt*/
	//bigint* y = NULL;
	//bi_assign(&y, x);
	//printf("sign = %d\n", y->sign);
	//printf("wordlen = %d\n", y->wordlen);
	//printf("address = %p\n", y->a);
	//printf("\n");

	///*Genearate Random BigInt*/
	//bi_gen_rand(&x, NONNEGATIVE, 5);
	//printf("Rand BigInt = "); bi_show_bin(x);
	//printf("\n");
	//printf("sign = %d\n", x->sign);
	//printf("wordlen = %d\n", x->wordlen);
	//printf("address = %p\n", x->a);
	//printf("\n");


	///*Get Word Length, Bit Length, j-th Bit of BigInt*/
	//printf("bit length = %d\n", get_bit_length(x));
	//printf("\n");
	//printf("0-th bit = %d\n", bit_of_bi(x, 0));
	//printf("8-th bit = %d\n", bit_of_bi(x, 8));
	//printf("11-th bit = %d\n", bit_of_bi(x, 11));

	///*Get Sign, Flip Sign, of Bit*/
	//printf("Sign of BigInt x = %d\n", get_sign_bi(x));
	//flip_sign_bi(&x);
	//printf("Flip Sign of x = %d\n", get_sign_bi(x));
	//printf("\n");
	///*Set One, Set Zero, Is Zero, Is One*/
	//printf("Set One BigInt x\n");
	//bi_set_one(&x);
	//printf("sign = %d\n", x->sign);
	//printf("wordlen = %d\n", x->wordlen);
	//printf("address = %p\n", x->a);
	//bi_show_bin(x); printf("\n");
	//printf("Set Zero BigInt x\n");
	//bi_set_zero(&x);
	//printf("sign = %d\n", x->sign);
	//printf("wordlen = %d\n", x->wordlen);
	//printf("address = %p\n", x->a);
	//bi_show_bin(x); printf("\n");
	//printf("Is BigInt x One? : True(1), False(0)\n%d", bi_is_one(x));
	//printf("\n");
	//printf("Is BigInt x Zero? : True(1), False(0)\n%d", bi_is_zero(x));
	//printf("\n");
	///*Compare*/

	///*Left/Right Shift*/
	//bi_new(&hd, 2);
	//hd->a[0] = 0xab; // 10111011
	//hd->a[1] = 0xcd; // 11101011

	//bi_set_by_array(&x, NONNEGATIVE, hd->a, hd->wordlen);
	//printf("biginteger : %x%x\n", hd->a[1], hd->a[0]);
	//bi_show_bin(hd);

	//bi_leftshift(&hd, 8, hd->a, hd->wordlen);
	//printf("biginteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
	//bi_show_bin(hd);
	//
	/************** right shift È®ÀÎ ***************/
	//hd = NULL;
	word hd_Arr[3] = { 0x12, 0x34, 0x56 };
	//printf("BigInteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
	bi_set_by_array(&hd, NONNEGATIVE, hd_Arr, sizeof(hd_Arr)/sizeof(hd_Arr[0]));
	printf("BigInteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
	bi_show_bin(hd);

	bi_rightshift(&hd, 8, hd->a, hd->wordlen);
	printf("BigInteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
	bi_show_bin(hd);

	/*Reduction*/
	bigint* z=NULL;
	bi_gen_rand(&x, NONNEGATIVE, 5);
	printf("Rand BigInt = "); bi_show_bin(x);
	printf("\n");
	bi_reduction(&z, x, 8);
	printf("Reduction BigInt = "); bi_show_bin(z); printf("\n");
	bi_reduction(&z, x, 9);
	printf("Reduction BigInt = "); bi_show_bin(z); printf("\n");
	bi_reduction(&z, x, 50);
	printf("Reduction BigInt = "); bi_show_bin(z); printf("\n");
	



	//This is second Test
}

