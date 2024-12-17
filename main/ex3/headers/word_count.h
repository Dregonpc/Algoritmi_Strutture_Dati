#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include "hash_table.h"

// Legge il file e popola la hash table con la frequenza delle parole
void read_words_from_file(const char* file_path, int min_length, HashTable* table);

// Trova la parola con la frequenza massima nella hash table
void find_max_frequency_word(HashTable* table, int min_length);

// Libera la memoria della hash table, incluse le chiavi e i valori
void free_hash_table_with_values(HashTable* table);

// Funzione principale
void find_most_frequent_word(const char* file_path, int min_length);

#endif // WORD_COUNT_H
