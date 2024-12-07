#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

// Definizione delle strutture
typedef struct HashNode {
    void* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode** buckets;                     // Array di liste per gestire i bucket
    int size;                               // Numero di elementi nella tavola
    int capacity;                           // Numero di bucket
    float load_factor;                      // Fattore di carico per il ridimensionamento
    int (*compare_keys)(const void*, const void*); // Funzione di confronto per chiavi
    unsigned long (*hash_function)(const void*);   // Funzione di hash per chiavi
} HashTable;

// Dichiarazioni delle funzioni
HashTable* hash_table_create(int (*compare_keys)(const void*, const void*), unsigned long (*hash_function)(const void*));
void hash_table_put(HashTable* table, const void* key, const void* value);
void* hash_table_get(const HashTable* table, const void* key);
int hash_table_contains_key(const HashTable* table, const void* key);
void hash_table_remove(HashTable* table, const void* key);
int hash_table_size(const HashTable* table);
void** hash_table_keyset(const HashTable* table);
void hash_table_free(HashTable* table);

#endif // HASH_TABLE_H
