#include "miosort.h"
#include "primitivesort.h"

#include <stdlib.h>
#include <time.h>
#include <windows.h>
/* Sorts */
extern void MIOSort_sortint(int a[], int n) {	
	sortint(a, n);
}

/* Sorts */
extern void MIOSort_sortreal(double a[], int n) {
	sortreal(a, n);
}

/* Sorts */
extern void MIOSort_sortstring(char *a[], int n) {
	sortstring(a, n);
}

/* Shellsort integers */
extern void MIOSort_stablesortint(int a[], int n) {
	stablesortint(a, n);
}

/* Shellsort integers */
extern void MIOSort_stablesortreal(double a[], int n) {
	stablesortreal(a, n);
}