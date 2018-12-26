//
//  coer_sort.c
//  coer
//
//  Created by vs on 12/25/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "coer_sort.h"


#include <stdlib.h>

static int comp_i(const void* a, const void* b)
{
	double f = *((int*)a);
	double s = *((int*)b);
	if (f > s)
		return 1;
	if (f < s)
		return -1;
	return 0;
}

static int comp_f(const void* a, const void* b)
{
	double f = *((float*)a);
	double s = *((float*)b);
	if (f > s)
		return 1;
	if (f < s)
		return -1;
	return 0;
}
static int comp_d(const void* a, const void* b)
{
	double f = *((double*)a);
	double s = *((double*)b);
	if (f > s)
		return 1;
	if (f < s)
		return -1;
	return 0;
}

void coer_sort_i(int* data, int num)
{
	qsort(data, num, sizeof(data[0]), comp_i);
	
}

void coer_sort_f(float* data, int num)
{
	qsort(data, num, sizeof(data[0]), comp_f);
	
}

void coer_sort_d(double* data, int num)
{
	qsort(data, num, sizeof(data[0]), comp_d);
	
}

