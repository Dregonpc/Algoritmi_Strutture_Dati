#include "../main/ex3/headers/hash_table.h"
#include "Unity/unity.h"
#include <string.h>
#include <stdlib.h>

// Funzione di hash semplice (per stringhe)
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

// Funzione di hash per interi
unsigned long int_hash(const void* key) {
    return *(int*)key;
}

// Funzione di confronto per interi
int int_compare(const void* a, const void* b) {
    return *(int*)a == *(int*)b;
}

// Variabili globali per setup e teardown
HashTable* table;

// Setup per ogni test
void setUp(void) {
    table = hash_table_create(string_compare, string_hash);
}

// Teardown per ogni test
void tearDown(void) {
    hash_table_free(table);
}

// 1. Test Creazione della Tavola Hash
void test_hash_table_create(void) {
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
}

// 2. Test Inserimento e Recupero di una Chiave-Valore
void test_hash_table_put_get(void) {
    hash_table_put(table, "key1", "value1");
    TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(table, "key1"));
}

// 3. Test Sostituzione di un Valore
void test_hash_table_replace_value(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key1", "value2");
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(table, "key1"));
}

// 4. Test Verifica Esistenza Chiave
void test_hash_table_contains_key(void) {
    hash_table_put(table, "key1", "value1");
    TEST_ASSERT_TRUE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key2"));
}

// 5. Test Rimozione di una Coppia
void test_hash_table_remove(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_remove(table, "key1");
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key1"));
}

// 6. Test Recupero di una Chiave Non Esistente
void test_hash_table_get_non_existent(void) {
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
}

// 7. Test Dimensione della Tavola
void test_hash_table_size(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    TEST_ASSERT_EQUAL(2, hash_table_size(table));
}

// 8. Test Keyset della Tavola
void test_hash_table_keyset(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    void** keys = hash_table_keyset(table);

    // Verifica che le chiavi esistano indipendentemente dall'ordine
    int found_key1 = 0, found_key2 = 0;
    for (int i = 0; i < hash_table_size(table); i++) {
        if (strcmp((char*)keys[i], "key1") == 0) {
            found_key1 = 1;
        } else if (strcmp((char*)keys[i], "key2") == 0) {
            found_key2 = 1;
        }
    }
    TEST_ASSERT_TRUE(found_key1);
    TEST_ASSERT_TRUE(found_key2);

    free(keys);
}

// 9. Test Ridimensionamento Automatico
void test_hash_table_resize(void) {
    int new_capacity = table->capacity * 2;
    HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));

    for (int i = 0; i < table->capacity; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            // Ricalcola l'indice nel nuovo array di bucket
            unsigned long new_index = table->hash_function(current->key) % new_capacity;

            // Sposta il nodo nel nuovo bucket
            HashNode* next = current->next;
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;

            current = next;
        }
    }

    // Sostituisci i vecchi bucket con quelli nuovi
    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
}

// 10. Test Inserimento di Valori NULL
void test_hash_table_put_null_value(void) {
    hash_table_put(table, "key1", NULL);
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
}

// 11. Test Collisioni (chiavi diverse, stesso hash)
void test_hash_table_collision(void) {
    HashTable* int_table = hash_table_create(int_compare, int_hash);
    int key1 = 1, key2 = 17; // Stesso hash in una tabella con 16 bucket iniziali
    hash_table_put(int_table, &key1, "value1");
    hash_table_put(int_table, &key2, "value2");
    TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(int_table, &key1));
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(int_table, &key2));
    hash_table_free(int_table);
}

// 12. Test Rimozione con Collisioni
void test_hash_table_remove_collision(void) {
    HashTable* int_table = hash_table_create(int_compare, int_hash);
    int key1 = 1, key2 = 17;
    hash_table_put(int_table, &key1, "value1");
    hash_table_put(int_table, &key2, "value2");
    hash_table_remove(int_table, &key1);
    TEST_ASSERT_NULL(hash_table_get(int_table, &key1));
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(int_table, &key2));
    hash_table_free(int_table);
}

// 13. Test Inserimento e Recupero di Interi
void test_hash_table_int_keys(void) {
    HashTable* int_table = hash_table_create(int_compare, int_hash);
    int key = 42;
    char* value = "value";
    hash_table_put(int_table, &key, value);
    TEST_ASSERT_EQUAL_STRING(value, (char*)hash_table_get(int_table, &key));
    hash_table_free(int_table);
}

// 14. Test con Chiavi Vuote (stringhe vuote)
void test_hash_table_empty_string_key(void) {
    hash_table_put(table, "", "value");
    TEST_ASSERT_EQUAL_STRING("value", (char*)hash_table_get(table, ""));
}

// 15. Test Rimozione di Tutti gli Elementi
void test_hash_table_clear(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    hash_table_remove(table, "key1");
    hash_table_remove(table, "key2");
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
}

// Main per eseguire i test
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_hash_table_create);
    RUN_TEST(test_hash_table_put_get);
    RUN_TEST(test_hash_table_replace_value);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_get_non_existent);
    RUN_TEST(test_hash_table_size);
    RUN_TEST(test_hash_table_keyset);
    RUN_TEST(test_hash_table_resize);
    RUN_TEST(test_hash_table_put_null_value);
    RUN_TEST(test_hash_table_collision);
    RUN_TEST(test_hash_table_remove_collision);
    RUN_TEST(test_hash_table_int_keys);
    RUN_TEST(test_hash_table_empty_string_key);
    RUN_TEST(test_hash_table_clear);

    return UNITY_END();
}
