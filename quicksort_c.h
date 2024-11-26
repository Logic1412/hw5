#ifndef _QUICKSORT_C_H
#define _QUICKSORT_C_H
#include <stdlib.h>

// This is the exact same format as qsort, but you
// must NOT use qsort to implement this.

void quicksort_c(void *base, size_t nmemb,
                 size_t size,
                 int (*compar)(const void *, const void *));

#endif
