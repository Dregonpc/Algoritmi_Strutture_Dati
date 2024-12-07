#include "../headers/hash_table.h"
#include <string.h> // Per strcmp

// Funzione ausiliaria: ridimensiona la tabella hash
void hash_table_resize(HashTable* table) {
    int new_capacity = table->capacity * 2;
    HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));

    for (int i = 0; i < table->capacity; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            // Calcola il nuovo indice nella tabella ridimensionata
            unsigned long new_index = table->hash_function(current->key) % new_capacity;

            // Ricolloca il nodo
            HashNode* next = current->next;
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;

            current = next;
        }
    }

    // Sostituisce i vecchi bucket con i nuovi
    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
}

// Creazione della Tavola Hash
HashTable* hash_table_create(int (*compare_keys)(const void*, const void*), unsigned long (*hash_function)(const void*)) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->capacity = 16; // Capacità iniziale
    table->size = 0;
    table->load_factor = 0.75; // Fattore di carico predefinito
    table->buckets = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
    table->compare_keys = compare_keys;
    table->hash_function = hash_function;
    return table;
}

// Inserimento di una Coppia
void hash_table_put(HashTable* table, const void* key, const void* value) {
    // Controlla se è necessario ridimensionare
    if ((float)table->size / table->capacity >= table->load_factor) {
        hash_table_resize(table);
    }

    unsigned long hash = table->hash_function(key) % table->capacity;
    HashNode* current = table->buckets[hash];

    // Controlla se la chiave esiste già
    while (current != NULL) {
        if (table->compare_keys(current->key, key)) { // Modifica: confronta con 1 per uguaglianza
            current->value = (void*)value; // Aggiorna il valore
            return;
        }
        current = current->next;
    }

    // Inserisce un nuovo nodo
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = (void*)key;
    new_node->value = (void*)value;
    new_node->next = table->buckets[hash];
    table->buckets[hash] = new_node;
    table->size++;
}

// Ottenere un Valore
void* hash_table_get(const HashTable* table, const void* key) {
    unsigned long hash = table->hash_function(key) % table->capacity;
    HashNode* current = table->buckets[hash];

    while (current != NULL) {
        if (table->compare_keys(current->key, key)) { // Modifica: confronta con 1 per uguaglianza
            return current->value;
        }
        current = current->next;
    }

    return NULL; // Chiave non trovata
}

// Verificare l'Esistenza di una Chiave
int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

// Rimuovere una Coppia
void hash_table_remove(HashTable* table, const void* key) {
    unsigned long hash = table->hash_function(key) % table->capacity;
    HashNode* current = table->buckets[hash];
    HashNode* prev = NULL;

    while (current != NULL) {
        if (table->compare_keys(current->key, key)) { // Modifica: confronta con 1 per uguaglianza
            if (prev == NULL) {
                table->buckets[hash] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            table->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Ottenere la Dimensione della Tavola
int hash_table_size(const HashTable* table) {
    return table->size;
}

// Ottenere l'Insieme delle Chiavi
void** hash_table_keyset(const HashTable* table) {
    void** keys = (void**)malloc(table->size * sizeof(void*));
    int index = 0;

    for (int i = 0; i < table->capacity; i++) {
        HashNode* current = table->buckets[i];
        while (current != NULL) {
            keys[index++] = current->key;
            current = current->next;
        }
    }

    return keys;
}

// Deallocare la Tavola Hash
void hash_table_free(HashTable* table) {
    for (int i = 0; i < table->capacity; i++) {
        HashNode* current = table->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}
