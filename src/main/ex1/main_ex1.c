#include "merge_sort.h"
#include "quick_sort.h"
#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Record* load_data(FILE *infile, size_t *num_records) {
    FILE *file = fopen(infile, 'r');
    if (file == NULL) {
        printf("Error opening file.");
        return NULL;
    }
    
    char line[256];
    size_t capacity = 8;
    *num_records = 0;

    Record *records = (Record*)malloc(capacity * sizeof(Record));
    if (records == NULL) {
        printf("Memory allocation error.");
        fclose(file);
        return NULL;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        Record record;
        if (sscanf(line, "%d,%s,%d,%f", &record.id, &record.field1, &record.field2, &record.field3) == 4) {
            records[*num_records] = record;
            (*num_records)++;

            if (*num_records == capacity) {
                capacity *= 2;
                records = realloc(records, capacity * sizeof(Record));
                if (records == NULL) {
                    printf("Memory reallocation error.");
                    fclose(file);
                    return NULL;
                }
            }
        }
    }

    fclose(file);
    return records;
}

void write_data(FILE *outfile, Record* records, size_t *num_records) {
    FILE *file = fopen(outfile, 'w');
    if (file == NULL) {
        printf("Error opening file.");
        return NULL;
    }

    for (size_t i = 0; i < num_records; i++) {
        fprintf(outfile, "%d,%s,%d,%f\n", records[i].id, records[i].field1, records[i].field2, records[i].field3);
    }

    fclose(file);
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    size_t num_records;
    Record *records = load_data(infile, &num_records);

    if (records == NULL) {
        printf("Error reading records.");
        return;
    }

    int (*compar)(const void*, const void*);
    if (field == 1)
        compar = compare_records_string;
    else if (field == 2)
        compar = compare_records_int;
    else
        compar = compare_records_float;

    if (algo == 1)
        merge_sort(records, num_records, sizeof(Record), compar);
    else
        quick_sort(records, num_records, sizeof(Record), compar);

    write_data(outfile, &records, &num_records);

    free(records);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Error, to start:\nmain_ex1.c (Path of the file to read) (Path of the file to write to) (1/2/3 = indicates which of the three fields should be used to sort the records.)");
        exit(EXIT_FAILURE);
    }

    //TO DO:
    // 1: Controllo parametri
    // 2: void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);
    // 3: dentro la funzione:
    // 4: funzione leggi file
    // 5: funzione sorting
    // 6: funzione scrittura file

    if (argv[3] < 1 || argv[3] > 3) {
        printf("Error, to start:\nmain_ex1.c (Path of the file to read) (Path of the file to write to) (1/2/3 = indicates which of the three fields should be used to sort the records.)");
        exit(EXIT_FAILURE);
    }

    int algo;
    printf("Please, choose the algorithm to use (1 = Merge sort, 2 = Quick sort): ");
    scanf("%d", &algo);

    if (algo != 1 || algo != 2) {
        printf("Error, invalid input. You can choose between 1 or 2. (1 = Merge sort, 2 = Quick sort).");
        exit(EXIT_FAILURE);
    }

    sort_records(argv[1], argv[2], argv[3], algo);

    return (EXIT_SUCCESS);
}