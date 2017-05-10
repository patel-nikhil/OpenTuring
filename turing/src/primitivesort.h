#ifndef _MIOPRIMSORT_H_
#define _MIOPRIMSORT_H_

extern void sortint(int a[], int n);
extern void sortreal(double a[], int n);
extern void sortstring(char *a[], int n);
extern void stablesortint(int a[], int n);
extern void stablesortreal(double a[], int n);


void shuffle(int a[], int n);
void shufflereal(double a[], int n);
void shufflestring(char *a[], int n);

void stablesort(void *a, int n, int dtype);
void quicksortint(int a[], int n);
void quicksortreal(double a[], int n);
void quicksortstring(char *a[], int n);
void insertionsortint(int a[], int lo, int hi);
void insertionsortreal(double a[], int lo, int hi);
void partitionsortint(int a[], int lo, int hi);
void partitionsortreal(double a[], int lo, int hi);
void partitionsortstring(char *a[], int lo, int hi, int pos);

void selectionsort(int a[], int n);


#endif
