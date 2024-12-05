#include "quicksort_c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This is the exact same format as qsort, but you
// must NOT use qsort to implement this.

// You probably want to create a quicksort_internal function that
// you call in order to properly implement quicksort.

static void swap(void *a, void *b, size_t size) {
    unsigned char *po1 = a;
    unsigned char *po2 = b;
    for (size_t i = 0; i < size; i++) {
        unsigned char tmp = po1[i];
        po1[i] = po2[i];
        po2[i] = tmp;
    }
}

static void quicksort_internal(void *base, size_t low, size_t high, size_t size, int (*compar)(const void *, const void *)) {
    if (low >= high) {
        return;
    }

    void *piv = (unsigned char *)base + high * size;
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        void *tem = (unsigned char *)base + j * size;
        if (compar(tem, piv) < 0) {
            swap((unsigned char *)base + i * size, tem, size);
            i++;
        }
    }

    swap((unsigned char *)base + i * size, piv, size);

    if (i > 0) {
        quicksort_internal(base, low, i - 1, size, compar);
    }
    quicksort_internal(base, i + 1, high, size, compar);
}

void quicksort_c(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    (void) base;
    (void) nmemb;
    (void) size;
    (void) compar;
    if (nmemb < 2 || size == 0 || base == NULL || compar == NULL) {
        return;
    }

    quicksort_internal(base, 0, nmemb - 1, size, compar);
}
