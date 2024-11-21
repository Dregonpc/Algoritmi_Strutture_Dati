#include "../headers/merge_sort.h"
#include "../headers/quick_sort.h"
#include "../headers/record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Record* load_data(FILE *infile, size_t *num_records) {
    char line[256];
    size_t capacity = 8;
    *num_records = 0;
    int i = 0;

    Record *records = (Record*)malloc(capacity * sizeof(Record));
    if (records == NULL) {
        printf("Errore nell'allocazione della memoria.\n");
        fclose(infile);
        return NULL;
    }
    
    while (fgets(line, sizeof(line), infile) != NULL) {
        // Rimuovi il newline finale se presente
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n')) { // || line[len - 1] == '\r'
            line[len - 1] = '\0';
        }

        Record record;

        if (sscanf(line, "%d,%49[^,],%d,%f", &record.id, record.field1, &record.field2, &record.field3) == 4) {
            records[*num_records] = record;
            (*num_records)++;

            if (*num_records == capacity) {
                //printf("Riallocazione necessaria: %zu record letti.\n", *num_records);
                capacity *= 2;
                records = realloc(records, capacity * sizeof(Record));
                if (records == NULL) {
                    printf("Errore nella riallocazione della memoria.\n");
                    fclose(infile);
                    return NULL;
                }
            }

            printf("Sto leggendo: %d\n", i);
            i++;
        } 
        else {
            printf("Errore nel parsing della riga: '%s'\n", line);
        }
    }

    fclose(infile);
    return records;
}

void write_data(FILE *outfile, Record* records, size_t *num_records) {
    for (size_t i = 0; i < *num_records; i++) {
        fprintf(outfile, "%d,%s,%d,%f\n", records[i].id, records[i].field1, records[i].field2, records[i].field3);
    }

    fclose(outfile);
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

    clock_t start, end;
    if (algo == 1) { 
        start = clock();
        merge_sort(records, num_records, sizeof(Record), compar);
        end = clock();
        float exTime = (float)(end - start);
        printf("Time of esecution of merge sort in this case is %f seconds\n", exTime);
    }
    else {
        start = clock();
        quick_sort(records, num_records, sizeof(Record), compar);
        end = clock();
        float exTime = (float)(end - start);
        printf("Time of esecution of quick sort in this case is %f seconds\n", exTime);
    }

    write_data(outfile, records, &num_records);

    free(records);
}

int main(int argc, char const *argv[]) {
    if (argc < 5) {
        printf("Error, to start:\nmain_ex1.c (Path of the file to read) (Path of the file to write to) (1/2/3 = indicates which of the three fields should be used to sort the records.) (1/2 = Merge sort / Quick sort)");
        exit(EXIT_FAILURE);
    }

    int fieldKey = atoi(argv[3]);
    int algo = atoi(argv[4]);
    if ((fieldKey < 1 || fieldKey > 3) || (algo < 1 || algo > 2)) {
        printf("Error, to start:\nmain_ex1.c (Path of the file to read) (Path of the file to write to) (1/2/3 = indicates which of the three fields should be used to sort the records.) (1/2 = Merge sort / Quick sort)");
        exit(EXIT_FAILURE);
    }

    FILE *inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Error opening file.");
        exit(EXIT_FAILURE);
    }

    FILE *outFile = fopen(argv[2], "w");
    if (outFile == NULL) {
        printf("Error opening file.");
        exit(EXIT_FAILURE);
    }

    sort_records(inFile, outFile, fieldKey, algo);

    return (EXIT_SUCCESS);
}