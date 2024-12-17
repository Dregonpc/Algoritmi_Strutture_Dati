#include "../headers/word_count.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Funzione di hash per stringhe
unsigned long string_hash(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Funzione di confronto per stringhe
int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b) == 0;
}

// Funzione per normalizzare le parole (rimuove punteggiatura e mette in minuscolo)
char* normalize_word(const char* word) {
    int len = strlen(word);
    char* clean_word = (char*)malloc(len + 1);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isalnum(word[i])) {
            clean_word[j++] = tolower(word[i]);
        }
    }
    clean_word[j] = '\0';
    return clean_word;
}

// Funzione per copiare manualmente una stringa
char* manual_strdup(const char* str) {
    int len = strlen(str) + 1; // +1 per il terminatore null '\0'
    char* copy = (char*)malloc(len);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

void process_and_split_word(const char* input_word, int min_length, HashTable* table) {
    int len = strlen(input_word);
    char buffer[1024]; // Buffer per ogni sottostringa
    int j = 0;

    for (int i = 0; i <= len; i++) { // Include il terminatore null '\0'
        if (!isalnum(input_word[i]) || input_word[i] == '\0') { // Delimitatore trovato
            if (j > 0) { // Se il buffer contiene una parola valida
                buffer[j] = '\0'; // Termina la sottostringa
                char* normalized_word = normalize_word(buffer);
                if (strlen(normalized_word) >= (size_t)min_length) {
                    // Inserisce la parola nella hash table
                    int* count = (int*)hash_table_get(table, normalized_word);
                    if (count) {
                        (*count)++;
                    } else {
                        char* key_copy = manual_strdup(normalized_word);
                        int* new_count = (int*)malloc(sizeof(int));
                        *new_count = 1;
                        hash_table_put(table, key_copy, new_count);
                    }
                }
                free(normalized_word);
                j = 0; // Resetta il buffer
            }
        } else {
            buffer[j++] = tolower(input_word[i]); // Copia carattere alfanumerico in minuscolo
        }
    }
}

// Legge il file e popola la hash table
void read_words_from_file(const char* file_path, int min_length, HashTable* table) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Errore: impossibile aprire il file.\n");
        exit(1);
    }

    char buffer[1024];
    while (fscanf(file, "%1023s", buffer) == 1) {
        process_and_split_word(buffer, min_length, table);
    }

    fclose(file);
}

// Trova la parola con la frequenza massima
void find_max_frequency_word(HashTable* table, int min_length) {
    void** keys = hash_table_keyset(table);
    int max_count = 0;
    char* most_frequent_word = NULL;

    for (int i = 0; i < hash_table_size(table); i++) {
        int* count = (int*)hash_table_get(table, keys[i]);
        if (*count > max_count) {
            max_count = *count;
            most_frequent_word = (char*)keys[i];
        }
    }

    if (most_frequent_word) {
        printf("La parola più frequente di lunghezza >= %d è: '%s' (ripetuta %d volte)\n",
               min_length, most_frequent_word, max_count);
    } else {
        printf("Nessuna parola trovata con lunghezza >= %d.\n", min_length);
    }

    free(keys);
}

// Libera la memoria della hash table, incluse chiavi e valori
void free_hash_table_with_values(HashTable* table) {
    void** keys = hash_table_keyset(table);
    for (int i = 0; i < hash_table_size(table); i++) {
        free(keys[i]); // Libera le chiavi allocate manualmente
        free(hash_table_get(table, keys[i])); // Libera i conteggi
    }
    free(keys);
    hash_table_free(table);
}

// Funzione principale
void find_most_frequent_word(const char* file_path, int min_length) {
    // Crea la hash table
    HashTable* table = hash_table_create(string_compare, string_hash);

    // Leggi il file e popola la hash table
    read_words_from_file(file_path, min_length, table);

    // Trova la parola più frequente
    find_max_frequency_word(table, min_length);

    // Libera la memoria
    free_hash_table_with_values(table);
}
