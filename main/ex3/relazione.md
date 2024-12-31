# Relazione 

## Indice
1. [Introduzione / Obbiettivo](#obbiettivo)
2. [Svolgimento](#svolgimento)
4. [Conclusioni](#conclusioni)

## Obbiettivo
In questo esercizio il nostro scopo è quello di creare una libreria generica che realizza la struttura dati *tavola hash (con concatenamento)* in grado di ospitare un insieme di coppie
`{<chiave 1,valore 1>,...,<chiave n,valore n>}`, ovviamente deve essere una libreria il più possibile ottimizzata e deve seguire le regole di scrittura di un buon codice.
Per la creazione però andremo ad utilizzare dei supporti basati su `Large Language Model (LLM)` come ad esempio ChatGPT.


## Svolgimento
### Sviluppo della libreria
Come primo approccio per la creazione della libreria da zero abbiamo deciso di utilizzare ChatGPT con il modello GPT-4o mini e per rendere la chat un ambiente ben strutturato sulla creazione di codice come input iniziale abbiamo utilizzato una frase di contesto in cui è specificato l’utilizzo del linguaggio C, la consegna dell’esercizio e come indicazione ulteriore le firme delle funzioni che dovrà andare a sviluppare.

## Input 1
Ciao, ho bisogno di una mano per un progetto di laboratorio di algoritmi e strutture dati in linguaggio C.

Devo implementare una libreria generica che realizza la struttura dati tavola hash (con concatenamento) in grado di ospitare un insieme di coppie {<chiave_1,valore_1>,...,<chiave_n,valore_n>}.
La tavola hash deve accettare chiavi e valori di tipi generici (tutte le chiavi hanno uno stesso tipo, tutti i valori hanno uno stesso tipo, ma chiavi e valori possono avere tipi fra loro differenti).
La struttura dati deve offrire almeno le seguenti funzionalità (ricavare il significato delle varie funzioni e procedure e dei loro parametri a partire dai loro prototipi):

```c
HashTable* hash_table_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*));
void hash_table_put(HashTable*, const void*, const void*);
void* hash_table_get(const HashTable*, const void*);
int hash_table_contains_key(const HashTable*, const void*);
void hash_table_remove(HashTable*, const void*);
int hash_table_size(const HashTable*);
void** hash_table_keyset(const HashTable*);
void hash_table_free(HashTable*);
```

## Output 1
>Per implementare una libreria generica in linguaggio C che rappresenti una tavola hash con concatenamento, devi progettare una struttura che consenta l'utilizzo di tipi generici per chiavi e valori. Questo richiede l'uso di puntatori void* e funzioni di callback per gestire le operazioni di confronto e calcolo degli hash. Ecco una spiegazione dettagliata e una possibile implementazione per i vari componenti richiesti.
> ### Strutture dati
>### 1. Nodo della lista
>Rappresenta una singola coppia chiave-valore in una lista collegata per gestire le collisioni.
>```c
>typedef struct HashNode {
>    void* key;
>    void* value;
>    struct HashNode* next;
>} HashNode;
>```
>### 2. Tavola Hash
>La struttura principale che contiene un array di puntatori a liste (bucket), funzioni di utilità e dimensione.
>```c
>typedef struct HashTable {
>    HashNode** buckets;                     // Array di liste per gestire i bucket
>    int size;                               // Numero di elementi nella tavola
>    int capacity;                           // Numero di bucket
>    int (*compare_keys)(const void*, const void*); // Funzione di confronto per chiavi
>    unsigned long (*hash_function)(const >void*);   // Funzione di hash per chiavi
>} HashTable;
>```
> ### Funzioni
>### 1. Creazione della tabella hash
>```c
>HashTable* hash_table_create(int (*compare_keys)(const void*, const void*), unsigned long (*hash_function)(const void*)) {
>    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
>    table->capacity = 16; // Capacità iniziale
>    table->size = 0;
>    table->buckets = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
>    table->compare_keys = compare_keys;
>    table->hash_function = hash_function;
>    return table;
>}
>```
>### 2. Inserimento di una Coppia
>```c
>void hash_table_put(HashTable* table, const void* key, const void* value) {
>    unsigned long hash = table->hash_function(key) % table->capacity;
>    HashNode* current = table->buckets[hash];
>
>    // Controlla se la chiave esiste già
>    while (current != NULL) {
>        if (table->compare_keys(current->key, key) == 0) {
>            current->value = (void*)value; // Aggiorna il valore
>            return;
>        }
>        current = current->next;
>    }
>
>    // Inserisce un nuovo nodo
>    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
>    new_node->key = (void*)key;
>    new_node->value = (void*)value;
>    new_node->next = table->buckets[hash];
>    table->buckets[hash] = new_node;
>    table->size++;
>}
>```
>### 3. Ottenere un valore
>```c
>void* hash_table_get(const HashTable* table, const void* key) {
>    unsigned long hash = table->hash_function(key) % table->capacity;
>    HashNode* current = table->buckets[hash];
>
>    while (current != NULL) {
>        if (table->compare_keys(current->key, key) == 0) {
>            return current->value;
>        }
>        current = current->next;
>    }
>
>    return NULL; // Chiave non trovata
>}
>```
>### 4. Verificare l'Esistenza di una Chiave
>```c
>int hash_table_contains_key(const HashTable* table, const void* key) {
>    return hash_table_get(table, key) != NULL;
>}
>```
>### 5. Rimuovere una Coppia
>```c
> void hash_table_remove(HashTable* table, const void* key) {
>     unsigned long hash = table->hash_function(key) % table->capacity;
>     HashNode* current = table->buckets[hash];
>     HashNode* prev = NULL;
> 
>     while (current != NULL) {
>         if (table->compare_keys(current->key, key) == 0) {
>             if (prev == NULL) {
>                 table->buckets[hash] = current->next;
>             } else {
>                 prev->next = current->next;
>             }
>             free(current);
>             table->size--;
>             return;
>         }
>         prev = current;
>         current = current->next;
>     }
> }
> ```
>### 6. Ottenere la dimensione della tavola
>```c
>int hash_table_size(const HashTable* table) {
>    return table->size;
>}
>```
>### 7. Ottenere l'Insieme delle Chiavi
> ```c
> void** hash_table_keyset(const HashTable* table) {
>     void** keys = (void**)malloc(table->size * sizeof(void*));
>     int index = 0;
> 
>     for (int i = 0; i < table->capacity; i++) {
>         HashNode* current = table->buckets[i];
>         while (current != NULL) {
>             keys[index++] = current->key;
>             current = current->next;
>         }
>     }
> 
>     return keys;
> }
> ```
>### 8. Deallocare la Tavola Hash
> ```c
> void hash_table_free(HashTable* table) {
>     for (int i = 0; i < table->capacity; i++) {
>         HashNode* current = table->buckets[i];
>         while (current != NULL) {
>             HashNode* temp = current;
>             current = current->next;
>             free(temp);
>         }
>     }
>     free(table->buckets);
>     free(table);
> }
> ```
> ### Utilizzo delle Funzioni di Callback
>- La funzione `compare_keys` dovrebbe restituire `0` se le chiavi sono uguali, e un valore diverso da zero altrimenti.
>- La funzione `hash_function` dovrebbe restituire un valore `unsigned long` rappresentante l'hash della chiave.
>- Queste funzioni di callback permettono alla tavola hash di essere generica e di funzionare con qualsiasi tipo di chiave e valore.
>- Esempi di funzioni di callback possono includere confronti di stringhe, interi, o qualsiasi altro tipo di dato.
>Esempio di funzioni per un caso in cui le chiavi sono stringhe:
> ```c
> int compare_strings(const void* a, const void* b) {
>   return strcmp((const char*)a, (const char*)b);
> }
> 
> unsigned long hash_string(const void* key) {
>   const char* str = (const char*)key;
>   unsigned long hash = 5381;
>   int c;
>   while ((c = *str++)) {
>     hash = ((hash << 5) + hash) + c;
>   }
>   return hash;
> }
> ```
>---
>Questo codice rappresenta una base solida per la libreria di gestione di una tavola hash generica in C.
>Se hai bisogno di ulteriori chiarimenti o miglioramenti, fammi sapere!

Il primo risultato ottenuto era **una semplice lista di funzioni separate tra loro**,
senza considerare la necessità di un **file header** ne dell’effettiva consegna della creazione di una libreria,
richieste che abbiamo introdotto con il secondo input

## Input 2
Puoi suddividere il codice in un file header (.h) e in un file .c per favore?

## Output 2
>Certamente! Ecco come puoi organizzare il codice in due file separati: un file header (hash_table.h) e un file sorgente (hash_table.c).
>### File Header : `hash_table.h` 
>```c
>#ifndef HASH_TABLE_H
>#define HASH_TABLE_H
>
>#include <stdlib.h>
>
>// Definizione delle strutture
>typedef struct HashNode {
>  void* key;
>  void* value;
>  struct HashNode* next;
>} HashNode;
>
>typedef struct HashTable {
>  HashNode** buckets;                     // Array di liste per gestire i bucket
>  int size;                               // Numero di elementi nella tavola
>  int capacity;                           // Numero di bucket
>  int (*compare_keys)(const void*, const void*); // Funzione di confronto per chiavi
>  unsigned long (*hash_function)(const void*);   // Funzione di hash per chiavi
>} HashTable;
>
>// Dichiarazioni delle funzioni
>HashTable* hash_table_create(int (*compare_keys)(const void*, const void*), unsigned long (*hash_function)(const void*));
>void hash_table_put(HashTable* table, const void* key, const void* value);
>void* hash_table_get(const HashTable* table, const void* key);
>int hash_table_contains_key(const HashTable* table, const void* key);
>void hash_table_remove(HashTable* table, const void* key);
>int hash_table_size(const HashTable* table);
>void** hash_table_keyset(const HashTable* table);
>void hash_table_free(HashTable* table);
>
>#endif // HASH_TABLE_H
>```
>### File Sorgente: `hash_table.c`
>```c
>#include "hash_table.h"
>
>// Creazione della Tavola Hash
>HashTable* hash_table_create(int (*compare_keys)(const void*, const void*), unsigned long (*hash_function)(const void*)) {
>  HashTable* table = (HashTable*)malloc(sizeof(HashTable));
>  table->capacity = 16; // Capacità iniziale
>  table->size = 0;
>  table->buckets = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
>  table->compare_keys = compare_keys;
>  table->hash_function = hash_function;
>  return table;
>}
>
>// Inserimento di una Coppia
>void hash_table_put(HashTable* table, const void* key, const void* value) {
>  unsigned long hash = table->hash_function(key) % table->capacity;
>  HashNode* current = table->buckets[hash];
>
>  // Controlla se la chiave esiste già
>  while (current != NULL) {
>    if (table->compare_keys(current->key, key) == 0) {
>      current->value = (void*)value; // Aggiorna il valore
>      return;
>    }
>    current = current->next;
>  }
>
>  // Inserisce un nuovo nodo
>  HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
>  new_node->key = (void*)key;
>  new_node->value = (void*)value;
>  new_node->next = table->buckets[hash];
>  table->buckets[hash] = new_node;
>  table->size++;
>}
>
>// Ottenere un Valore
>void* hash_table_get(const HashTable* table, const void* key) {
>  unsigned long hash = table->hash_function(key) % table->capacity;
>  HashNode* current = table->buckets[hash];
>
>  while (current != NULL) {
>    if (table->compare_keys(current->key, key) == 0) {
>      return current->value;
>    }
>    current = current->next;
>  }
>
>  return NULL; // Chiave non trovata
>}
>
>// Verificare l'Esistenza di una Chiave
>int hash_table_contains_key(const HashTable* table, const void* key) {
>  return hash_table_get(table, key) != NULL;
>}
>
>// Rimuovere una Coppia
>void hash_table_remove(HashTable* table, const void* key) {
>  unsigned long hash = table->hash_function(key) % table->capacity;
>  HashNode* current = table->buckets[hash];
>  HashNode* prev = NULL;
>
>  while (current != NULL) {
>    if (table->compare_keys(current->key, key) == 0) {
>      if (prev == NULL) {
>        table->buckets[hash] = current->next;
>      } else {
>        prev->next = current->next;
>      }
>      free(current);
>      table->size--;
>      return;
>    }
>    prev = current;
>    current = current->next;
>  }
>}
>
>// Ottenere la Dimensione della Tavola
>int hash_table_size(const HashTable* table) {
>  return table->size;
>}
>
>// Ottenere l'Insieme delle Chiavi
>void** hash_table_keyset(const HashTable* table) {
>  void** keys = (void**)malloc(table->size * sizeof(void*));
>  int index = 0;
>
>  for (int i = 0; i < table->capacity; i++) {
>    HashNode* current = table->buckets[i];
>    while (current != NULL) {
>      keys[index++] = current->key;
>      current = current->next;
>    }
>  }
>
>  return keys;
>}
>
>// Deallocare la Tavola Hash
>void hash_table_free(HashTable* table) {
>  for (int i = 0; i < table->capacity; i++) {
>    HashNode* current = table->buckets[i];
>    while (current != NULL) {
>      HashNode* temp = current;
>      current = current->next;
>      free(temp);
>    }
>  }
>  free(table->buckets);
>  free(table);
>}
>```
>### Utilizzo
>Puoi includere hash_table.h nel tuo programma principale o nei test per utilizzare la libreria.<br>
>Esempio:
>```c
>#include <stdio.h>
>#include <string.h>
>#include "hash_table.h"
>
>int compare_strings(const void* a, const void* b) {
>    return strcmp((const char*)a, (const char*)b);
>}
>
>unsigned long hash_string(const void* key) {
>    const char* str = (const char*)key;
>    unsigned long hash = 5381;
>    int c;
>    while ((c = *str++)) {
>        hash = ((hash << 5) + hash) + c;
>    }
>    return hash;
>}
>
>int main() {
>    HashTable* table = hash_table_create(compare_strings, hash_string);
>
>    hash_table_put(table, "key1", "value1");
>    hash_table_put(table, "key2", "value2");
>
>    printf("Key1: %s\n", (char*)hash_table_get(table, "key1"));
>    printf("Key2: %s\n", (char*)hash_table_get(table, "key2"));
>
>    hash_table_free(table);
>    return 0;
>}
>```


Il secondo risultato è stato effettivamente un’evoluzione del primo,
il modello ha suddiviso il codice in un file sorgente e un file headers ed in più ci ha fornito un file main con cui è stato possibile verificare in modo rapido e iniziale l’effettiva funzionalità della libreria.<br>
Con la creazione di file separati ChatGPT ha dovuto nominare i file, e abbiamo deciso di mantenerli invariati anche nella versione finale del codice.<br>
Successivamente revisionando il codice che ci era stato proposto abbiamo notato che il metodo in cui vengono aggiunti elementi alla hash table non è dinamico e alloca uno slot fisso.<br>

## Input 3
Questa implementazione non è completamente generica perchè contiene un massimo di 16 elementi.
Quando la tabella si riempe deve essere ingrandita

## Output 3 
>Hai assolutamente ragione: per rendere la tabella hash completamente generica e scalabile,
>è necessario implementare un meccanismo di ridimensionamento quando il numero di elementi supera una certa soglia (ad esempio,un fattore di carico).
>Di seguito, aggiorniamo l'implementazione per includere questa funzionalità
>### Modifica della Struttura e Funzioni
>1. Introduzione del Fattore di Carico
>Il fattore di carico (load factor) è la soglia oltre la quale la tabella viene ridimensionata.<br>
>Un valore tipico è 0.75.
> ```c
> typedef struct HashTable {
>   HashNode** buckets;                     // Array di liste per gestire i bucket
>   int size;                               // Numero di elementi nella tavola
>   int capacity;                           // Numero di bucket
>   float load_factor;                      // Fattore di carico per il ridimensionamento
>   int (*compare_keys)(const void*, const void*); // Funzione di confronto per chiavi
>   unsigned long (*hash_function)(const void*);   // Funzione di hash per chiavi
> } HashTable;
> ```
>### 2. Funzione per Ridimensionare la Tavola <br>
> ```c
> // Funzione ausiliaria: ridimensiona la tabella hash
> void hash_table_resize(HashTable* table) {
>   int new_capacity = table->capacity * 2;
>   HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));
>
>   for (int i = 0; i < table->capacity; i++) {
>     HashNode* current = table->buckets[i];
>     while (current) {
>       // Calcola il nuovo indice nella tabella ridimensionata
>       unsigned long new_index = table->hash_function(current->key) % new_capacity;
>
>       // Ricolloca il nodo
>       HashNode* next = current->next;
>       current->next = new_buckets[new_index];
>       new_buckets[new_index] = current;
>
>       current = next;
>     }
>   }
>
>   // Sostituisce i vecchi bucket con i nuovi
>   free(table->buckets);
>   table->buckets = new_buckets;
>   table->capacity = new_capacity;
> }
>```




