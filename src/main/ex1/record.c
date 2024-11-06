#include "record.h"

int compare_records_string(const void *a, const void *b) { 
    struct Record *first = (struct Record *)a;
    struct Record *second = (struct Record *)b;

    int comp = compare_string(&first->field1, &second->field1);
    if (comp != 0)
        return comp;
    
    comp = compare_int(&first->field2, &second->field2);
    if (comp != 0)
        return comp;

    comp = compare_float(&first->field3, &second->field3);
    
    return comp;
}

int compare_records_int(const void *a, const void *b) {
    struct Record *first = (struct Record *)a;
    struct Record *second = (struct Record *)b;

    int comp = compare_int(&first->field2, &second->field2);
    if (comp != 0)
        return comp;
    
    comp = compare_string(&first->field1, &second->field1);
    if (comp != 0)
        return comp;

    comp = compare_float(&first->field3, &second->field3);
    
    return comp;
}

int compare_records_float(const void *a, const void *b) {
    struct Record *first = (struct Record *)a;
    struct Record *second = (struct Record *)b;

    int comp = compare_float(&first->field3, &second->field3);
    if (comp != 0)
        return comp;
    
    comp = compare_string(&first->field1, &second->field1);
    if (comp != 0)
        return comp;

    
    comp = compare_int(&first->field2, &second->field2);
    return comp;
}