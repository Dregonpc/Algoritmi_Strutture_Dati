#include "compare.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Partition the array using the last element as a pivot
 * @param base Is a pointer to the first element of the array to sort
 * @param left Index of the most left element of the array
 * @param right Index of the most right element of the array
 * @param size Is the size (in bytes) of each element of the array
 * @param compar It is the criterion according to which to sort the data (given two pointers to elements of the array, it returns a number greater than, equal to or less than zero if the first argument is respectively greater than, equal to or less than the second)
 * @return Index of the pivot
 */
size_t partition(void *base, size_t size, size_t left, size_t right, int (*compar)(const void*, const void*));

/**
 * @brief Quick sort of generic array
 * @param base Is a pointer to the first element of the array to sort
 * @param nitems Is the number of elements in the array to sort
 * @param size Is the size (in bytes) of each element of the array
 * @param compar It is the criterion according to which to sort the data (given two pointers to elements of the array, it returns a number greater than, equal to or less than zero if the first argument is respectively greater than, equal to or less than the second)
 */
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));