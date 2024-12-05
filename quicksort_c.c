#include "quicksort_c.h"
#include <string.h>
#include <stdlib.h>

static void swap(void *a, void *b, size_t size) {
    unsigned char *p1 = a;
    unsigned char *p2 = b;
    for (size_t i = 0; i < size; i++) {
        unsigned char tmp = p1[i];
        p1[i] = p2[i];
        p2[i] = tmp;
    }
}

static void median_of_three(void *base, size_t low, size_t mid, size_t high, size_t size, int (*compar)(const void *, const void *)) {
    void *a = (unsigned char *)base + low * size;
    void *b = (unsigned char *)base + mid * size;
    void *c = (unsigned char *)base + high * size;
    if (compar(a, b) > 0) swap(a, b, size);
    if (compar(a, c) > 0) swap(a, c, size);
    if (compar(b, c) > 0) swap(b, c, size);
    swap(b, (unsigned char *)base + high * size, size);
}


static void three_way_partition(void *base, size_t low, size_t high, size_t size, int (*compar)(const void *, const void *), size_t *lt, size_t *gt) {
    size_t mid = low + (high - low) / 2;
    median_of_three(base, low, mid, high, size, compar);
    void *pivot = (unsigned char *)base + high * size;
    size_t i = low;
    *lt = low;
    *gt = high;

    while (i <= *gt) {
        void *element = (unsigned char *)base + i * size;
        int cmp = compar(element, pivot);
        if (cmp < 0) {
            swap((unsigned char *)base + (*lt) * size, element, size);
            (*lt)++;
            i++;
        } else if (cmp > 0) {
            swap((unsigned char *)base + (*gt) * size, element, size);
            (*gt)--;
        } else {
            i++;
        }
    }
}

static void quicksort_internal(void *base, size_t low, size_t high, size_t size, int (*compar)(const void *, const void *)) {
    if (low < high) {
        size_t lt, gt;
        three_way_partition(base, low, high, size, compar, &lt, &gt);
        if (lt > 0) { 
            quicksort_internal(base, low, lt - 1, size, compar);
        }
        quicksort_internal(base, gt + 1, high, size, compar);
    }
}

void quicksort_c(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    if (nmemb < 2 || size == 0 || base == NULL || compar == NULL) {
        return; 
    }
    quicksort_internal(base, 0, nmemb - 1, size, compar);
}
