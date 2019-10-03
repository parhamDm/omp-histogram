// histogram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "omp.h"
#include<time.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>

long* categorize(int * arr, size_t n) {
	long histogram[5001];
	long histogramAns[5001];
	for (int i = 0; i < 5001; i++) {
		histogram[i] = 0;
		histogramAns[i] = 0;
	}
	int i = 0;
#pragma omp parallel firstprivate(histogram) 
	{
	#pragma omp for
			for (i = 0; i < n; i++) {
				histogram[arr[i]]++;
			}
	#pragma omp critical
			for (i = 0; i < 5001; i++) {

				//printf("%d/", histogram[i]);
				histogramAns[i] += histogram[i];
			}
#pragma omp critical
				printf("%d\n", histogram[10]);
	}
	return histogramAns;
}

void fill_array_random(int *a, size_t n) {
	srand(time(NULL));
	int i;
	for (i = 0; i < n; ++i) {
		a[i] = rand() % 5001;
	}
}

void print_array(long *a, size_t n) {
	for (int i = 0; i < n; ++i) {
		printf("%d\n",a[i]) ;
	}
	return;
}

int main()
{
	int size = 70000000;
	int * array = (int *) malloc(size * sizeof(int));
	fill_array_random(array,size);
	long * result = categorize(array, size);
//	print_array(result, 5001);
	 getch();
	return 0;
}



