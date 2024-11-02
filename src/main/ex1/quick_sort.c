#include "quick_sort.h"

void swap(void *a, void *b) {
    
}

int partition(void *base, size_t size, size_t left, size_t right, int (*compar)(const void*, const void*)) {
    void *pivot = base + right * size;
    size_t i = left;

    for (size_t j = left; j < right; j++) {
        if (compar(base + j * size, pivot) < 0) {
            swap(base + i * size, base + j * size);
            i++;
        }
    }

    swap(base + i * size, base + right * size);

    return i;
}

void quick_sort_rec(void *base, size_t nitems, size_t size, size_t left, size_t right, int (*compar)(const void*, const void*)) {
    if (left < right) {
        int pivot = partition(base, size, left, right, compar);

        quick_sort_rec(base, nitems, size, left, pivot - 1, compar);
        quick_sort_rec(base, nitems, size, pivot + 1, right, compar);
    }
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems > 1) {
        quick_sort_rec(base, nitems, size, 0, nitems - 1, compar);
    }
}