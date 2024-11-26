#include "quicksort_c.h"

#include <stdio.h>
#include <stdlib.h>

// This is the exact same format as qsort, but you
// must NOT use qsort to implement this.

// You probably want to create a quicksort_internal function that
// you call in order to properly implement quicksort.
void quicksort_c(void *base, size_t nmemb,
                 size_t size,
                 int (*compar)(const void *, const void *))
{
    (void) base;
    (void) nmemb;
    (void) size;
    (void) compar;

    printf("IMPLEMENT THIS!\n");
}