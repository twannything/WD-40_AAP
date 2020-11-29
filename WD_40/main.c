#define _CRT_SECURE_NO_WARNINGS
#include "Basic Operation.h"
#include "Arithmetic.h"
#include "test.h"

/**
* @mainpage BIGINT LIBRARY : WD-40
* - ÀÛ¼ºÀÚ : ±èÅÂ¿Ï, À¯Çöµµ
* @date 2020-11-23 05:42
*/

int main() {

	//add_test();
	//sub_test();
	//mul_test();
	//Ka_mul_test();
	//bi_binary_long_division_test();
	Squaring_test();
	//Exponentiation_test();


	//bigint* x = NULL;
	//bigint* z = NULL;
	//word a[4] = { 0xdb,0xa6,0xb3, 0xeb };

	//bi_set_by_array(&x, NONNEGATIVE, a, 4);
	//printf("x=");
	//bi_show_hex(x);
	//Squaring_Schoolbook(x, &z);
	//printf("x*x==");
	//bi_show_hex(z);


}










	/* Squaring word Å×½ºÆ®*/
	
	/*bigint* x = NULL;
	bigint* z = NULL;
	word dst[2] = { 0, };

	int i = 10;
	while (i > 0) {
		bi_gen_rand(&x, 1);
		bi_new(&z, 2);
		printf("x=");
		bi_show_hex(x);
		Squaring_word(z->a, x->a[0]);

		printf("x*x==");
		bi_show_hex(z);



		i--;
	}*/
	
	

	//bigint* x = NULL;
	//bigint* y = NULL;
	//bigint* z = NULL;
	///*errno_t err;
	//FILE* fp = NULL;
	//err = fopen_s(&fp,"C:\\Users\\user\\source\\repos\\WD_40(1)\\WD_40\\x64\\Release\\data.sage", "w");
	//if (fp == NULL) {
	//	puts("File Error\n");
	//	return -1;
	//}
	//*/
	//int i = 19;
	//while (i >= 0) {

	//	bi_gen_rand(&x,5);
	//	bi_gen_rand(&y,5); // squaring ¿¡¼­´Â ¾È¾¸

	//	printf("x=");
	//	bi_show_hex(x);
	//	printf("y="); // squaring ¿¡¼­´Â ¾È¾¸
	//	bi_show_hex(y); // squaring ¿¡¼­´Â ¾È¾¸
	//	MUL(x, y,&z);

	//	printf("x * y ==");
	//	bi_show_hex(z);

	//	bi_delete(&x);
	//	bi_delete(&y); // squaring ¿¡¼­´Â ¾È¾¸
	//	bi_delete(&z);

	//	free(x);
	//	free(y); // squaring ¿¡¼­´Â ¾È¾¸
	//	free(z);
	//	i--;
	//}

	/*
	bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		ADD(x, y, &z);
		printf("x + y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);

		free(x);
		free(y);
		free(z);

		bi_gen_rand(&x, 3);
		bi_gen_rand(&y, 5);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		ADD(x, y, &z);
		printf("x + y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);

		free(x);
		free(y);
		free(z);

		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 3);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		ADD(x, y, &z);
		printf("x + y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);

		free(x);
		free(y);
		free(z);
	*/
	/* –E¼À È®ÀÎ
	bi_gen_rand(&x, NONNEGATIVE, 5);
	bi_gen_rand(&y, NONNEGATIVE, 5);

	printf("x=");
	bi_show_hex(x);
	printf("y=");
	bi_show_hex(y);
	SUB(x, y, &z);
	printf("x - y ==");
	bi_show_hex(z);

	bi_delete(&x);
	bi_delete(&y);
	bi_delete(&z);

	free(x);
	free(y);
	free(z);

	bi_gen_rand(&x, NONNEGATIVE, 5);
	bi_gen_rand(&y, NEGATIVE, 5);

	printf("x=");
	bi_show_hex(x);
	printf("y=");
	bi_show_hex(y);

	SUB(x, y, &z);
	printf("x - y ==");
	bi_show_hex(z);

	bi_delete(&x);
	bi_delete(&y);
	bi_delete(&z);

	free(x);
	free(y);
	free(z);

	bi_gen_rand(&x, NEGATIVE, 5);
	bi_gen_rand(&y, NONNEGATIVE, 5);

	printf("x=");
	bi_show_hex(x);
	printf("y=");
	bi_show_hex(y);

	SUB(x, y, &z);
	printf("x - y ==");
	bi_show_hex(z);

	bi_delete(&x);
	bi_delete(&y);
	bi_delete(&z);

	free(x);
	free(y);
	free(z);

	bi_gen_rand(&x, NEGATIVE, 5);
	bi_gen_rand(&y, NEGATIVE, 5);

	printf("x=");
	bi_show_hex(x);
	printf("y=");
	bi_show_hex(y);

	SUB(x, y, &z);
	printf("x - y ==");
	bi_show_hex(z);

	bi_delete(&x);
	bi_delete(&y);
	bi_delete(&z);

	free(x);
	free(y);
	free(z);
	*/

	/* °ö¼À È®ÀÎ
	bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5);

		printf("x=");
		bi_show_hex(x);
		printf("y=");
		bi_show_hex(y);
		MUL(x, y, &z);
		printf("x * y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);

		free(x);
		free(y);
		free(z);
	*/

	/*
			bi_gen_rand(&x, 2);
			bi_gen_rand(&y, 2);

			printf("x=");
			bi_show_hex(x);
			printf("y=");
			bi_show_hex(y);
			MUL(x, y, &z);
			printf("x * y ==");
			bi_show_hex(z);


			//printf("\nif ((x * y) != z):\n");
			//printf("\tprint(False)\n");
			//printf("\n");


			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&z);

			free(x);
			free(y);
			free(z);

			*/




			/*  compare È®ÀÎ
			*
			*
				bi_gen_rand(&x, NONNEGATIVE, 5);
				bi_gen_rand(&y, NONNEGATIVE, 5);

				if (compareAB(x, y) == 1) {// x > y
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x > y\n");

				}
				else if (compareAB(x, y) == -1)
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x < y\n");
				}
				else if (compareAB(x, y) == 0) // x < y
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x == y\n");
				}

				bi_delete(&x);
				bi_delete(&y);

				free(x);
				free(y);

				bi_gen_rand(&x, NONNEGATIVE, 5);
				bi_gen_rand(&y, NEGATIVE, 5);

				if (compareAB(x, y) == 1) {// x > y
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x > y\n");

				}
				else if (compareAB(x, y) == -1)
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x < y\n");
				}
				else if (compareAB(x, y) == 0) // x < y
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x == y\n");
				}

				bi_delete(&x);
				bi_delete(&y);

				free(x);
				free(y);

				bi_gen_rand(&x, NEGATIVE, 5);
				bi_gen_rand(&y, NONNEGATIVE, 5);


				if (compareAB(x, y) == 1) {// x > y
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x > y\n");

				}
				else if (compareAB(x, y) == -1)
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x < y\n");
				}
				else if (compareAB(x, y) == 0) // x < y
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x == y\n");
				}

				bi_delete(&x);
				bi_delete(&y);

				free(x);
				free(y);

				bi_gen_rand(&x, NEGATIVE, 5);
				bi_gen_rand(&y, NEGATIVE, 5);


				if (compareAB(x, y) == 1) {// x > y
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x > y\n");

				}
				else if (compareAB(x, y) == -1)
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x < y\n");
				}
				else if (compareAB(x, y) == 0) // x < y
				{
					printf("x=");
					bi_show_hex(x);
					printf("y=");
					bi_show_hex(y);
					printf("x == y\n");
				}

				bi_delete(&x);
				bi_delete(&y);

				free(x);
				free(y);
			*/

			//fclose(fp);

			/*
				fputs("x=", fp);
				File_print(x, fp);
				fputs("y=", fp);
				File_print(y, fp);

				ADD(x, y, &z);

				fputs("x+y==", fp);
				File_print(z, fp);
			*/


			/*°ö¼Á È®ÀÎ
			//Schoolbook_MUL(x, y, &z);
			//printf("x * y = ");
			//bi_show_hex(z);
			*/

			/* compare È®ÀÎ
			*compareAB()
			*
			*/
			///************** left shift È®ÀÎ ***************/
			//bi_new(&x, 1);
			//word x_arr[2] = { 0xab, 0xcd }; // 10111011 11101011
			//bi_set_by_array(&x, NONNEGATIVE, x_arr, sizeof(x_arr) / sizeof(x_arr[0]));
			//printf("biginteger : ");
			//for(int i = (x->wordlen - 1); i >= 0; i--)
			//	printf("%02x", x->a[i]);
			//printf("\n");
			//bi_show_bin(x);
			//bi_leftshift(&x, 8, x->a, x->wordlen);
			//printf("biginteger : ");
			//for (int i = x->wordlen - 1; i >= 0; i--)
			//	printf("%02x", x->a[i]);
			//printf("\n");
			//bi_show_bin(x);

			///************** right shift È®ÀÎ ***************/
			//x = NULL;
			//bi_new(&x, 1);
			//word x1_arr[3] = { 0x12, 0x34, 0x56 };
			//bi_set_by_array(&x, NONNEGATIVE, x1_arr, sizeof(x1_arr)/sizeof(x1_arr[0]));
			//for (int i = (x->wordlen - 1); i >= 0; i--)
			//	printf("%02x", x->a[i]);
			//printf("\n");
			//bi_show_bin(x);
			//bi_rightshift(&x, 12, x->a, x->wordlen);
			//for (int i = (x->wordlen - 1); i >= 0; i--)
			//	printf("%02x", x->a[i]);
			//printf("\n");
			//bi_show_bin(x);

			////// µ¡¼À È®ÀÎ
			//word arr1[3] = { 0x03, 0xff, 0x43 };
			////word arr1[3] = { 0x00, };
			//word arr2[3] = { 0x02, 0xff, 0xae };

			//	
			//bi_set_by_array(&x, NONNEGATIVE, arr1, sizeof(arr1) / sizeof(arr1[0]));
			//bi_set_by_array(&y, NONNEGATIVE, arr2, sizeof(arr2) / sizeof(arr2[0]));
			//flip_sign_bi(&y);
			//for (int i = x->wordlen - 1; i >= 0; i--)
			//	printf("%02x", x->a[i]);
			//printf("\n");
			//for (int i = y->wordlen - 1; i >= 0; i--)
			//	printf("%02x", y->a[i]);
			//printf("\n");
			//
			//ADD(x, y, &z);

			//printf("wordlen of z = %d \n", z->wordlen);
			//	
			//printf("sign of z = %d \n", z->sign);
			//for (int i = z->wordlen - 1 ; i >= 0; i--)
			//	printf("%02x", z->a[i]);
			//printf("\n");


			///*create bigint, delete bigint, zerorize bigint*/
			//bi_new(&x, 4);

			//printf("sign = %d\n", x->sign);
			//printf("wordlen = %d\n", x->wordlen);
			//printf("address = %p\n", x->a);
			//printf("\n");

			///*set bigint by array*/
			//word arr1[3] = { 0x33,0xff,0xfe };
			//bi_set_by_array(&x, nonnegative, arr1, sizeof(arr1)/sizeof(arr1[0]));
			//printf("sign = %d\n", x->sign);
			//printf("wordlen = %d\n", x->wordlen);
			//printf("address = %p\n", x->a);
			//printf("\n");

			///*set bigint by string*/

			///*show bigint binary*/
			//printf("binary big integer = ");
			//bi_show_bin(x);
			//printf("\n");

			///*show bigint hex, dec*/

			///*refine bigint*/
			//word arr2[4] = { 0x00,0x33,0xff,0xfe };
			//bi_set_by_array(&x, nonnegative, arr2, sizeof(arr2) / sizeof(arr2[0]));
			//printf("sign = %d\n", x->sign);
			//printf("wordlen = %d\n", x->wordlen);
			//printf("address = %p\n", x->a);
			//printf("before refine = ");
			//bi_show_bin(x);
			//bi_refine(x);
			//printf("refine bigint = ");
			//bi_show_bin(x);
			//printf("\n");

			///*assign bigint*/
			//bigint* y = null;
			//bi_assign(&y, x);
			//printf("sign = %d\n", y->sign);
			//printf("wordlen = %d\n", y->wordlen);
			//printf("address = %p\n", y->a);
			//printf("\n");

			///*genearate random bigint*/
			//bi_gen_rand(&x, nonnegative, 5);
			//printf("rand bigint = "); bi_show_bin(x);
			//printf("\n");
			//printf("sign = %d\n", x->sign);
			//printf("wordlen = %d\n", x->wordlen);
			//printf("address = %p\n", x->a);
			//printf("\n");


			///*get word length, bit length, j-th bit of bigint*/
			//printf("bit length = %d\n", get_bit_length(x));
			//printf("\n");
			//printf("0-th bit = %d\n", bit_of_bi(x, 0));
			//printf("8-th bit = %d\n", bit_of_bi(x, 8));
			//printf("11-th bit = %d\n", bit_of_bi(x, 11));

			///*get sign, flip sign, of bit*/
			//printf("sign of bigint x = %d\n", get_sign_bi(x));
			//flip_sign_bi(&x);
			//printf("flip sign of x = %d\n", get_sign_bi(x));
			//printf("\n");
			///*set one, set zero, is zero, is one*/
			//printf("set one bigint x\n");
			//bi_set_one(&x);
			//printf("sign = %d\n", x->sign);
			//printf("wordlen = %d\n", x->wordlen);
			//printf("address = %p\n", x->a);
			//bi_show_bin(x); printf("\n");
			//printf("set zero bigint x\n");
			//bi_set_zero(&x);
			//printf("sign = %d\n", x->sign);
			//printf("wordlen = %d\n", x->wordlen);
			//printf("address = %p\n", x->a);
			//bi_show_bin(x); printf("\n");
			//printf("is bigint x one? : true(1), false(0)\n%d", bi_is_one(x));
			//printf("\n");
			//printf("is bigint x zero? : true(1), false(0)\n%d", bi_is_zero(x));
			//printf("\n");
			///*compare*/

			///*left/right shift*/
			//bi_new(&hd, 2);
			//hd->a[0] = 0xab; // 10111011
			//hd->a[1] = 0xcd; // 11101011

			//bi_set_by_array(&x, nonnegative, hd->a, hd->wordlen);
			//printf("biginteger : %x%x\n", hd->a[1], hd->a[0]);
			//bi_show_bin(hd);

			//bi_leftshift(&hd, 8, hd->a, hd->wordlen);
			//printf("biginteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
			//bi_show_bin(hd);
			//
			///************** right shift È®ÀÎ ***************/
			//hd = null;
			//word hd_arr[3] = { 0x12, 0x34, 0x56 };
			//printf("biginteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
			//bi_set_by_array(&hd, nonnegative, hd_arr, sizeof(hd_arr)/sizeof(hd_arr[0]));
			//printf("biginteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
			//bi_show_bin(hd);

			//bi_rightshift(&hd, 8, hd->a, hd->wordlen);
			//printf("biginteger : %x%x%x\n", hd->a[2], hd->a[1], hd->a[0]);
			//bi_show_bin(hd);

			///*reduction*/
			//bigint* z=null;
			//bi_gen_rand(&x, nonnegative, 5);
			//printf("rand bigint = "); bi_show_bin(x);
			//printf("\n");
			//bi_reduction(&z, x, 8);
			//printf("reduction bigint = "); bi_show_bin(z); printf("\n");
			//bi_reduction(&z, x, 9);
			//printf("reduction bigint = "); bi_show_bin(z); printf("\n");
			//bi_reduction(&z, x, 50);
			//printf("reduction bigint = "); bi_show_bin(z); printf("\n");



