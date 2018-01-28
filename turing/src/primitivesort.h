#ifndef _MIOPRIMSORT_H_
#define _MIOPRIMSORT_H_


/*void stablesort(void *a, int n, int dtype);*/

/* Integer sorting (and helper) methods */
extern void sortint(int a[], int n);
extern void stablesortint(int a[], int n);

void shellsortint(int a[], int n);
void selectionsort(int a[], int n);
void insertionsortint(int a[], int lo, int hi);
void quicksortint(int a[], int n);
void partitionsortint(int a[], int lo, int hi);
void mergesortint(int a[], int aux[], int n);
void msortint(int a[], int aux[], int lo, int hi);

/* Integer array sorting-helper methods */
void shuffleint(int a[], int n);
void mergeint(int a[], int aux[], int lo, int mid, int hi);


/* Real array sorting (and helper) methods */
extern void sortreal(double a[], int n);
extern void stablesortreal(double a[], int n);

void shellsortreal(double a[], int n);
void insertionsortreal(double a[], int lo, int hi);
void quicksortreal(double a[], int n);
void partitionsortreal(double a[], int lo, int hi);
void mergesortreal(double a[], double aux[], int n);
void msortreal(double a[], double aux[], int lo, int hi);


/* Real array sorting-helper methods */
void shufflereal(double a[], int n);
void mergereal(double a[], double aux[], int lo, int mid, int hi);

/* String array sorting (and helper) methods */
extern void sortstring(char *a[], int n);

void quicksortstring(char *a[], int n);
void partitionsortstring(char *a[], int lo, int hi, int pos);

/* String array sorting-helper methods */
void shufflestring(char **a, int n);


#endif
