#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

/**
 * @brief Node structure for the hash table
 * @param key key of the node
 * @param value value of the node
 */
typedef struct HashNode {
    void* key;
    void* value;
    struct HashNode* next;
} HashNode;

/**
 * @brief Hash table structure
 * @param buckets array of lists to manage the buckets
 * @param size number of elements in the table
 * @param capacity number of buckets
 * @param load_factor load factor for resizing
 * @param compare_keys function to compare keys
 * @param hash_function function to hash keys
 */
typedef struct HashTable {
    HashNode** buckets;
    int size;
    int capacity;
    float load_factor;
    int (*compare_keys)(const void*, const void*);
    unsigned long (*hash_function)(const void*);
} HashTable;

/**
 * @brief create a new hash table
 * @param compare_keys function to compare keys
 * @param hash_function function to hash keys
 */
HashTable* hash_table_create(int (*compare_keys)(const void*, const void*), unsigned long (*hash_function)(const void*));

/**
 * @brief put a key-value pair in the hash table
 * @param table hash table to insert the key-value pair
 * @param key key to insert
 * @param value value to insert
 */
void hash_table_put(HashTable* table, const void* key, const void* value);

/**
 * @brief get the value associated with a key in the hash table
 * @param table hash table to search the key in
 * @param key key to search
 * @return value associated with the key
 */
void* hash_table_get(const HashTable* table, const void* key);

/**
 * @brief check if a key is in the hash table
 * @param table hash table to search the key in
 * @param key key to search
 * @return 1 if the key is in the hash table, 0 otherwise
 */
int hash_table_contains_key(const HashTable* table, const void* key);

/**
 * @brief remove a key-value pair from the hash table
 * @param table hash table to remove the key-value pair from
 * @param key key to remove
 */
void hash_table_remove(HashTable* table, const void* key);

/**
 * @brief get the size of the hash table
 * @param table hash table to get the size of
 * @return size of the hash table
 */
int hash_table_size(const HashTable* table);

/**
 * @brief get the keys of the hash table
 * @param table hash table to get the keys of
 * @return keys of the hash table
 */
void** hash_table_keyset(const HashTable* table);

/**
 * @brief free the memory of the hash table
 * @param table hash table to free
 */
void hash_table_free(HashTable* table);

#endif // HASH_TABLE_H
