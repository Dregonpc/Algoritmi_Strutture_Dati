#include "merge_sort.h"
#include "quick_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void load_data(const char* file_name, struct Record *arr);

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

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

    return (EXIT_SUCCESS);
}