
#include "primitivesort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define MAX_STRLEN 256

/* Sorts integers, characters by ascii value (selection sort) */
extern void sortint(int a[], int n) {
	if (!a) return;	
	if (n < 100) {
		/* int *aux = malloc(sizeof(int) * n);
		if (1==0) {
			mergesortint(a, n);
			free(aux);
		}
		else */ stablesortint(a, n);		
	}
	else quicksortint(a, n);
}

/* Sorts real values */
extern void sortreal(double a[], int n) {
	if (!a) return;
	if (n < 100) stablesortreal(a, n);
	else quicksortreal(a, n);
}

/* Sorts real values */
extern void sortstring(char *a[], int n) {
	if (!a) return;
	quicksortstring(a, n);
}

void stablesort(void *a, int n, int dtype) {
	if (dtype == 0) stablesortint((int *)a, n);
	else stablesortreal((double *)a, n);
}

/* Shellsort integers */
extern void stablesortint(int a[], int n) {
	int iter = 1;
	while (iter < n / 3) iter = 3 * iter + 1;
	while (iter >= 1) {
		for (int i = iter; i < n; i++) {
			for (int j = i; j >= iter; j -= iter) {
				if (a[j] < a[j - iter]) {
					int temp = a[j];
					a[j] = a[j - iter];
					a[j - iter] = temp;
				}
			}
		}
		iter /= 3;
	}
}

/* Shellsort integers */
extern void stablesortreal(double a[], int n) {

	int iter = 1;
	while (iter < n / 3) iter = 3 * iter + 1;
	while (iter >= 1) {
		for (int i = iter; i < n; i++) {
			for (int j = i; j > iter; j -= iter) {
				if (a[j] < a[j - iter]) {
					double temp = a[j];
					a[j] = a[j - iter];
					a[j - iter] = temp;
				}
			}
		}
		iter /= 3;
	}
}

/*void mergesortint(int a[], int n) {

}


void mergesortreal(double a[], int n) {

}*/


/* Quicksort integers */
void quicksort(void *a, int n, int dtype) {
	shuffle(a, n);
	if (dtype == 0) partitionsortint((int *)a, 0, n - 1);
	else partitionsortreal((double *)a, 0, n - 1);
}

/* Quicksort int values */
void quicksortint(int a[], int n) {
	shuffle(a, n);
	partitionsortint(a, 0, n - 1);
}

/* Quicksort real values */
void quicksortreal(double a[], int n) {
	shufflereal(a, n);
	partitionsortreal(a, 0, n - 1);
}

/* Quicksort string values */
void quicksortstring(char *a[], int n) {
	shufflestring(a, n);
	partitionsortstring(a, 0, n - 1, 0);
}


void partitionsortint(int a[], int lo, int hi) {

	/* if (lo >= hi) return; */
	if (lo + 13 >= hi) {
		insertionsortint(a, lo, hi);
		return;
	}
	int pValue = a[lo];
	int pivot = lo;

	int index = lo + 1;						/*Start scan on element at index 1*/
	int end = hi;

	while (index <= end) {

		int current = a[index];

		if (current < pValue) {				/*Put the smaller element in front of the pivot element*/
			int temp = a[pivot];
			a[pivot] = a[index];
			a[index] = temp;
			index++;						/*Increment index to check next element*/
			pivot++;						/*Keep start as the index for the pivot element*/
		}
		else if (current > pValue) {		/*Put the bigger element at the end of the list*/
			int temp = a[index];
			a[index] = a[end];
			a[end] = temp;
			end--;							/*Set upper bound to the next highest index*/
		}
		else {
			index++;
		}
	}
	partitionsortint(a, lo, pivot - 1);
	partitionsortint(a, end + 1, hi);
}

/* Real values */
void partitionsortreal(double a[], int lo, int hi) {

	/*if (lo >= hi) return;*/
	if (lo + 13 >= hi) {
		insertionsortreal(a, lo, hi);
		return;
	}

	double pValue = a[lo];
	int pivot = lo;

	int index = lo + 1;						/*Start scan on element at index 1*/
	int end = hi;

	while (index <= end) {

		double current = a[index];

		if (current < pValue) {				/*Put the smaller element in front of the pivot element*/
			double temp = a[pivot];
			a[pivot] = a[index];
			a[index] = temp;
			index++;						/*Increment index to check next element*/
			pivot++;						/*Keep start as the index for the pivot element*/
		}
		else if (current > pValue) {		/*Put the bigger element at the end of the list*/
			double temp = a[index];
			a[index] = a[end];
			a[end] = temp;
			end--;							/*Set upper bound to the next highest index*/
		}
		else {
			index++;
		}
	}
	partitionsortreal(a, lo, pivot - 1);
	partitionsortreal(a, end + 1, hi);
}

void partitionsortstring(char *a[], int lo, int hi, int pos) {
	if (lo >= hi) return;		

	int pValue = (pos < (signed)strlen(*a + lo*MAX_STRLEN) ? (int)(*(*a+lo*MAX_STRLEN+pos)) : -1);
	int pivot = lo;	

	int index = lo + 1;						/*Start scan on element at index 1*/
	int end = hi;

	while (index <= end) {

		int current = (pos < (signed)strlen(*a + index*MAX_STRLEN) ? *((*a + index*MAX_STRLEN)+pos) : -1);		
	
		if (current < pValue) {				/*Put the smaller element in front of the pivot element*/					
			char *temp = calloc(MAX_STRLEN, sizeof(char));
			strcpy(temp, *a + pivot*MAX_STRLEN);
			strcpy(*a + pivot * MAX_STRLEN, *a + index * MAX_STRLEN);
			strcpy(*a + index * MAX_STRLEN, temp);
			free(temp);
			index++;						/*Increment index to check next element*/
			pivot++;						/*Keep start as the index for the pivot element*/
		}
		else if (current > pValue) {		/*Put the bigger element at the end of the list*/						
			char *temp = calloc(MAX_STRLEN, sizeof(char));
			strcpy(temp, *a + index * MAX_STRLEN);
			strcpy(*a + index * MAX_STRLEN, *a + end * MAX_STRLEN);
			strcpy(*a + end * MAX_STRLEN, temp);
			free(temp);
			end--;							/*Set upper bound to the next highest index*/
		}
		else {
			index++;
		}
	}
	partitionsortstring(a, lo, pivot - 1, pos);
	if (pValue >= 0) partitionsortstring(a, pivot, end, pos + 1);
	partitionsortstring(a, end + 1, hi, pos);
}




/* Insertion sort for subarrays */
void insertionsortint(int a[], int lo, int hi) {	
	if (lo >= hi) return;
	for (int i = lo; i < hi; i++) {
		for (int j = i; j > 0; j--) {
			if (a[j] < a[j - 1]) {
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
	}
}

/* Insertion sort for subarrays */
void insertionsortreal(double a[], int lo, int hi) {
	if (lo >= hi) return;
	for (int i = lo; i < hi; i++) {
		for (int j = i; j > 0; j -= 1) {
			if (a[j] < a[j - 1]) {
				double temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
	}
}


void selectionsort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		int index = i;
		int min = index;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[min]) min = j;
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

/* Modern Fisher-Yates shuffle */
void shuffle(int a[], int n) {
	srand((unsigned)time(NULL));
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

/* Modern Fisher-Yates shuffle */
void shufflereal(double a[], int n) {
	srand((unsigned)time(NULL));
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		double temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

/* Modern Fisher-Yates shuffle */
void shufflestring(char **a, int n) {
	srand((unsigned)time(NULL));	
	for (int i = n - 1; i > 0; i--) {		
		int j = rand() % (i + 1);				
		
		char *temp = calloc(MAX_STRLEN, sizeof(char));
		strcpy(temp, *a + i*MAX_STRLEN);
		strcpy(*a + i*MAX_STRLEN, *a + j*MAX_STRLEN);
		strcpy(*a + j*MAX_STRLEN, temp);
		free(temp);		
	}
}