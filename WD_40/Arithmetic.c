#pragma once
#include "Arithmetic.h"
#include "Basic Operation.h"

void bi_reduction(bigint** y , bigint* x, int r) {
	{
		word a = 1;
		int k = r / WORD_BITLEN;
		int rem = r % WORD_BITLEN;
		if (r > x->wordlen * WORD_BITLEN) {
			bi_assign(y, x); return;
		}
		else if (rem == 0) {
			bi_new(y, k);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & (((long long)a << WORD_BITLEN) - 1); return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & (((long long)a << WORD_BITLEN) - 1);
			}
			(*y)->a[k] = x->a[k] & ((a << rem) - 1);
			return;
		}
	}
}

int S_ADDABc(bigint* x, bigint* y, bigint** z,int carry, int r) {
	
	int d = 0;
	 
	if (r >= 1)
		if ((*z)->a[r - 1] < x->a[r - 1]) carry = 1;
		

	(*z)->a[r] = (x->a[r] + y->a[r]) & (((long long)1 << WORD_BITLEN) - 1);
	if ((*z)->a[r] < x->a[r]) d = 1;
	
	(*z)->a[r] = ((*z)->a[r] + carry);

	if ((*z)->a[r] < carry) d = 1;
	
	return d;
}

void M_ADD(bigint* x, bigint* y, bigint** z) {
	int a, b, c, d = 0;
	a = x->wordlen;
	b = y->wordlen;

	bi_new(z, (a + 1));


	for (int i = b; i < a; i++)
		y->a[i] = 0;
	c = 0;

	for (int i = 0; i < a; i++)
		c = S_ADDABc(x, y, z, c, i);


	(*z)->a[a] = c;

	if ((*z)->a[a] == 0) bi_refine(*z);
}

int S_SUBABb(bigint* x, bigint* y, bigint** z, int b, int j) {

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;

	(*z)->a[j] -= y->a[j];
	return b;
}



void SUB_C(bigint* x, bigint* y, bigint** z) {
	bi_new(z, x->wordlen);
	
	for (int i = y->wordlen; i < (*z)->wordlen; i++)
		(*z)->a[i] = 0;
	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb(x, y, z, b, j);
	}
	bi_refine(*z);
}

void ADD(bigint* x, bigint* y, bigint** z) {
	int a, b;

	a = x->wordlen;
	b = y->wordlen;

	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		return;
	}
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB(y, x, z);
		flip_sign_bi(&x);
		return;
	}
	if (a >= b) {
		M_ADD(x, y, z);
		return;
	}
	else {
		M_ADD(y, x, z);
		return;
	}
}

void SUB(bigint* x, bigint* y, bigint** z) {
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}

	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		SUB_C(x, y, z);
		return;
	}
	else if(get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) ==-1) {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	else if(get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) ==-1) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	else {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&y);
		return;
	}
}

void MULC(bigint* x, bigint* y, bigint** z, int i, int j) {

	word a0, a1, b0, b1, c0, c1, t0, t1, t, a = 1;

	a0 = x->a[i] & ((a << (WORD_BITLEN / 2)) - 1);
	a1 = x->a[i] >> (WORD_BITLEN / 2);
	b0 = y->a[j] & ((a << (WORD_BITLEN / 2)) - 1);
	b1 = y->a[j] >> (WORD_BITLEN / 2);
	t0 = a1 * b0;
	t1 = a0 * b1;
	t0 = (t0 + t1) & ((a << WORD_BITLEN) - 1);
	t1 = t0 < t1;


	c0 = a0 * b0;
	c1 = a1 * b1;
	t = c0;
	c0 = ((c0 + (t0 << (WORD_BITLEN / 2))) & ((a << WORD_BITLEN) - 1));
	c1 = c1 + (t1 << (WORD_BITLEN / 2)) + (t0 >> (WORD_BITLEN / 2)) + (c0 < t);
	(*z)->a[0] = c0;
	(*z)->a[1] = c1;
}

void MUL(bigint* x, bigint* y, bigint** z) {

	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) {
		bi_set_zero(z);
		return;
	}

	if (bi_is_one(x) == 1) {
		bi_assign(z, y);
		return;
	}

	if (bi_is_one(x) == 1 && get_sign_bi(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}

	if (bi_is_one(y) == 1) {
		bi_assign(z, x);
		return;
	}

	if (bi_is_one(y) == 1 && get_sign_bi(y) == 1) {
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	Schoolbook_MUL(x, y, z);
	(*z)->sign = ((-1) ^ (x->sign + y->sign));
}

void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {

	int i, j, c = 0;
	bigint* tmp = NULL;
	word t = 0;
	bi_new(&tmp, 2);
	bi_new(z, (x->wordlen + y->wordlen));

	for (i = 0; i < x->wordlen; i++)
		for (j = 0; j < y->wordlen; j++) {
			MULC(x, y, &tmp, i, j);
			t = (*z)->a[i + j];
			(*z)->a[i + j] += tmp->a[0];
			if ((*z)->a[i + j] < t) c = 1;
			else c = 0;
			(*z)->a[i + j + 1] += tmp->a[1] + c;
		}
}










