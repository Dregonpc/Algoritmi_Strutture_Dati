#include "../headers/compare.h"

int is_null(const void *a, const void *b, int *check) {
    if (a != NULL && b != NULL)
        return 0;
    
    if (a == NULL && b == NULL)
        *check = 0;
    else if (a == NULL && b != NULL)
        *check = -1;
    else if (a != NULL && b == NULL)
        *check = 1;
    
    return 1;
}

int compare_char(const void *a, const void *b) {
    int ret;
    if (is_null(a, b, &ret))
        return ret;
    
    char first = *(char*)a;
    char second = *(char*)b;

    if (first > second)
        return 1;
    if (first < second)
        return -1;

    return 0;
}

int compare_string(const void *a, const void *b) {
    int ret;
    if (is_null(a, b, &ret))
        return ret;
    
    char *first = (char*)a;
    
    char *second = (char*)b;

    return strcmp(first, second);
}

int compare_int(const void *a, const void *b) {
    int ret;
    if(is_null(a, b, &ret))
        return ret;
    
    int first = *(int*)a;
    int second = *(int*)b;

    if(first > second)
        return 1;
    if(first < second)
        return -1;
    
    return 0;
}

int compare_long(const void *a, const void *b) {
    int ret;
    if(is_null(a, b, &ret))
        return ret;
    
    long first = *(long*)a;
    long second = *(long*)b;

    if(first > second)
        return 1;
    if(first < second)
        return -1;
    
    return 0;
}

int compare_float(const void *a, const void *b) {
    int ret;
    if(is_null(a, b, &ret))
        return ret;
    
    float first = *(float*)a;
    float second = *(float*)b;

    if(first > second)
        return 1;
    if(first < second)
        return -1;
    
    return 0;
}

int compare_double(const void *a, const void *b) {
    int ret;
    if(is_null(a, b, &ret))
        return ret;
    
    double first = *(double*)a;
    double second = *(double*)b;

    if(first > second)
        return 1;
    if(first < second)
        return -1;
    
    return 0;
}