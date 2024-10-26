#include "merge_sort.h"

void merge(void *base, size_t left_count, size_t right_count, size_t size, int (*compar)(const void*, const void*)) {
    
    size_t leftIndex = 0, rightIndex = 0, supIndex = 0;
    void* supArray = malloc(size * (left_count + right_count));

    if (supArray == NULL) {
        return;
    }

    void* left = base;
    void* right = base + (left_count * size);

    while (leftIndex < left_count && rightIndex < right_count) {
        if(compar(left + (leftIndex * size), right + (rightIndex * size)) <= 0) {
            memcpy(supArray + (supIndex * size), left + (leftIndex * size), size);
            leftIndex++;
        } else {
            memcpy(supArray + (supIndex * size), right + (rightIndex * size), size);
            rightIndex++;
        }
        supIndex++;
    }

    while (leftIndex < left_count) {
        memcpy(supArray + (supIndex * size), left + (leftIndex * size), size);
        leftIndex++;
        supIndex++;
    }

    while (rightIndex < right_count) {
        memcpy(supArray + (supIndex * size), right + (rightIndex * size), size);
        rightIndex++;
        supIndex++;
    }

    memcpy(base, supArray, supIndex * size);
    free(supArray);
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