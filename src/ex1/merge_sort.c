#include "merge_sort.h"

void merge(void *base, size_t left_count, size_t right_count, size_t size, int (*compar)(const void*, const void*)) {
    
}

void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems < 2) {
        return;
    }
    else {
        size_t mid = nitems / 2;

        merge_sort(base, mid, size, compar);
        merge_sort(base + (mid * size), nitems - mid, size, compar);

        merge(base, mid, nitems - mid, size, compar);
    }
}