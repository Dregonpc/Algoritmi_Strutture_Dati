#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "compare.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief It sorts two generic sub-arrays, then merges them into a temporary array, and is finally copied to the original array.
 * @param base Is a pointer to the first element of the array to sort
 * @param left_count Number of elements contained in the left sub-array
 * @param right_count Number of elements contained in the right sub-array
 * @param size Is the size (in bytes) of each element of the array
 * @param compar It is the criterion according to which to sort the data (given two pointers to elements of the array, it returns a number greater than, equal to or less than zero if the first argument is respectively greater than, equal to or less than the second)
 */
void merge(void *base, size_t left_count, size_t right_count, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Recursive function that divides one generic array in half, until there is one single element for array. After that they are merged together with the merge function.
 * @param base Is a pointer to the first element of the array to sort
 * @param nitems Is the number of elements in the array to sort
 * @param size Is the size (in bytes) of each element of the array
 * @param compar It is the criterion according to which to sort the data (given two pointers to elements of the array, it returns a number greater than, equal to or less than zero if the first argument is respectively greater than, equal to or less than the second)
 */
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

#endif //MERGE_SORT_H