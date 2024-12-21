#include "../headers/word_count.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso corretto: %s <file_di_testo> <lunghezza_minima>\n", argv[0]);
        return 1;
    }

    const char* file_path = argv[1];

    int min_length = atoi(argv[2]);
    if (min_length <= 0) {
        fprintf(stderr, "Errore: la lunghezza minima deve essere un intero positivo.\n");
        return 1;
    }

    find_most_frequent_word(file_path, min_length);

    return 0;
}
