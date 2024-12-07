#include <stdio.h>
#include <string.h>
#include "../headers/hash_table.h"

int compare_strings(const void* a, const void* b) {
    return !strcmp((const char*)a, (const char*)b);
}

unsigned long hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int main() {
    HashTable* table = hash_table_create(compare_strings, hash_string);

    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    printf("Key1: %s\n", (char*)hash_table_get(table, "key1"));
    printf("Key2: %s\n", (char*)hash_table_get(table, "key2"));

    hash_table_free(table);
    return 0;
}
