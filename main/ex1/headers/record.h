#ifndef RECORD_H
#define RECORD_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *field1;
    int field2;
    float field3;
} Record;

/**
 * @brief compare two records based on their fields, start from field1
 * @details 
 *  calls #compare_string() on the first field, if the two strings are equal, 
 *  calls #compare_int() on the second field, if the two integers are equal,
 *  calls #compare_float() on the third field
 * @param a first record of comparison  
 * @param b second record of comparison
 * @return -1 if a < b, 0 if a = b, 1 if a > b
 */
int compare_records_string(const void *a, const void *b);

/**
 * @brief compare two records based on their fields, start from field2
 * @details 
 *  calls #compare_int() on the second field, if the two integers are equal,
 *  calls #compare_string() on the first field, if the two strings are equal, 
 *  calls #compare_float() on the third field
 * @param a first element of comparison  
 * @param b second element of comparison
 * @return -1 if a < b, 0 if a = b, 1 if a > b
 */
int compare_records_int(const void *a, const void *b);

/**
 * @brief compare two records based on their fields, start from field3
 * @details 
 *  calls #compare_float() on the third field
 *  calls #compare_string() on the first field, if the two strings are equal, 
 *  calls #compare_int() on the second field, if the two integers are equal,
 * @param a first element of comparison  
 * @param b second element of comparison
 * @return -1 if a < b, 0 if a = b, 1 if a > b
 */
int compare_records_float(const void *a, const void *b);

#endif //RECORD_H