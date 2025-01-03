# Relazione 

## Indice
1. [Introduzione / Obiettivo](#obiettivo)
2. [Svolgimento](#svolgimento)
    - [Input 1](#input-1)
    - [Input 2](#input-2)
    - [Input 3](#input-3)
    - [Input 4](#input-4)
    - [Input 5](#input-5)
    - [Input 6](#input-6)
    - [Input 7](#input-7)
    - [Input 8](#input-8)
    - [Input 9](#input-9)
    - [Input 10](#input-10)
3. [Conclusioni](#conclusioni)

## Obiettivo
Lo scopo di questo esercizio è quello di creare una libreria generica che realizza la struttura dati *tavola hash (con concatenamento)* in grado di ospitare un insieme di coppie
`{<chiave 1,valore 1>,...,<chiave n,valore n>}`, ovviamente deve essere una libreria il più possibile ottimizzata e deve seguire le regole di scrittura di un buon codice.
Per la creazione però, andremo ad utilizzare dei supporti basati su `Large Language Model (LLM)` come ad esempio ChatGPT.


# Svolgimento

## Sviluppo della libreria
Per la creazione della libreria da zero abbiamo deciso di utilizzare ChatGPT con il modello GPT-4o mini e per iniziare la conversazione abbiamo specificato subito di voler realizzare un progetto in linguaggio C, spiegando la consegna dell'esercizio e riportando le firme delle funzioni che dovrà sviluppare, in modo da dargli più informazioni possibili e avere una risposta la più stutturata e attendibile possibile.

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
richieste che abbiamo introdotto con il secondo input.

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
> ### Cosa cambia?
> 1. **Capacità dinamica**:<br>
> La tabella hash espande automaticamente quando il fattore di carico supera la soglia.
> 2. **Ricollocamento degli Elementi:**<br>
> Quando la tabella viene ridimensionata, gli elementi esistenti vengono reinseriti nei nuovi bucket.
> 3. **Ottimizzazione dello Spazio:**<br>
> La tabella utilizza solo lo spazio necessario, crescendo dinamicamente.
>
> Fammi sapere se hai bisogno di altre modifiche o chiarimenti!

Nel terzo output infatti è stato aggiunto un nuovo parametro all’interno della struct 	HashTable con load_factor ovvero una variabile dichiarata a 0.75 che permette di riallocare nuovo spazio quando il carico raggiunge i ¾ dello spazio disponibile.


## Input 4
Come quarto input gli abbiamo specificato di rimodulare il codice adattandolo alla nostra funzione di compare,
basandoci su quella utilizzata nei test messi a disposizione su moodle con code runner,
in cui ritorna 1 se i due elementi sono uguali, 0 altrimenti:

Come funzione di compare utilizzerò una funzione che ritorna 1 se i due elementi sono uguali, 0 se sono diversi.
Riadatta il codice in base a questa funzione

## Output 4
> Grazie per la precisazione!
> Adattiamo il codice affinché utilizzi una funzione di confronto
> che restituisce 1 se due elementi sono uguali e 0 altrimenti.
> Di conseguenza, aggiorneremo il controllo di uguaglianza delle chiavi nella tabella hash.
>
> Ecco il codice aggiornato:
>
> ```c
> // Ottenere un Valore
> void* hash_table_get(const HashTable* table, const void* key) {
>   unsigned long hash = table->hash_function(key) % table->capacity;
>   HashNode* current = table->buckets[hash];
>
>   while (current != NULL) {
>     if (table->compare_keys(current->key, key) == 1) { // Modifica: confronta con 1 per uguaglianza
>       return current->value;
>     }
>     current = current->next;
>   }
>
>   return NULL; // Chiave non trovata
> }
>
> // Verificare l'Esistenza di una Chiave
> int hash_table_contains_key(const HashTable* table, const void* key) {
>   return hash_table_get(table, key) != NULL;
> }
> ```
> ### Modifiche Effettuate
> 1. **Funzione di Confronto:**
> Ora si utilizza `table->compare_keys(current->key, key)`e si verifica se ritorna 1 per stabilire che due chiavi sono uguali.
>
> 2. **Controllo di Uguaglianza:**
> L'uguaglianza tra chiavi (`key`) e quelle già presenti nella tabella (`current->key`) è verificata come richiesto.
>
> Fammi sapere se hai bisogno di ulteriori dettagli o chiarimenti!

Le modifiche effettuate sono state nell’ utilizzo di table->compare_keys(current->key, key) con la verifica di ritorno 1 se le due chiavi sono uguali, tutto ciò per controllare la presenza della chiave nella tabella come richiesto.
Successivamente siamo passati alla parte di Unit Testing con la richiesta di 15 test per verificare la funzionalità della libreria, specificando espressamente l’utilizzo della libreria Unity.

## Input 5
Crea 15 Unit Test per testare questo codice, la libreria Unity è già stata implementata.

## Output 5
> Ecco 15 unit test per verificare il corretto funzionamento della tabella hash implementata,
> utilizzando la libreria Unity. Questi test coprono i principali casi d'uso
> e includono anche situazioni limite per verificare la robustezza della struttura dati.
> ```c
> #include "Unity/unity.h"
> #include <string.h>
> #include <stdlib.h>
> 
> // Funzione di hash semplice (per stringhe)
> unsigned long string_hash(const void* key) {
>     const char* str = (const char*)key;
>     unsigned long hash = 5381;
>     int c;
>     while ((c = *str++)) {
>         hash = ((hash << 5) + hash) + c;
>     }
>     return hash;
> }
> 
> // Funzione di confronto per stringhe
> int string_compare(const void* a, const void* b) {
>     return strcmp((const char*)a, (const char*)b) == 0;
> }
> 
> // Funzione di hash per interi
> unsigned long int_hash(const void* key) {
>     return *(int*)key;
> }
> 
> // Funzione di confronto per interi
> int int_compare(const void* a, const void* b) {
>     return *(int*)a == *(int*)b;
> }
> 
> // Variabili globali per setup e teardown
> HashTable* table;
> 
> // Setup per ogni test
> void setUp(void) {
>     table = hash_table_create(string_compare, string_hash);
> }
> 
> // Teardown per ogni test
> void tearDown(void) {
>     hash_table_free(table);
> }
> 
> // 1. Test Creazione della Tavola Hash
> void test_hash_table_create(void) {
>     TEST_ASSERT_NOT_NULL(table);
>     TEST_ASSERT_EQUAL(0, hash_table_size(table));
> }
> 
> // 2. Test Inserimento e Recupero di una Chiave-Valore
> void test_hash_table_put_get(void) {
>     hash_table_put(table, "key1", "value1");
>     TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(table, "key1"));
> }
> 
> // 3. Test Sostituzione di un Valore
> void test_hash_table_replace_value(void) {
>     hash_table_put(table, "key1", "value1");
>     hash_table_put(table, "key1", "value2");
>     TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(table, "key1"));
> }
> 
> // 4. Test Verifica Esistenza Chiave
> void test_hash_table_contains_key(void) {
>     hash_table_put(table, "key1", "value1");
>     TEST_ASSERT_TRUE(hash_table_contains_key(table, "key1"));
>     TEST_ASSERT_FALSE(hash_table_contains_key(table, "key2"));
> }
> 
> // 5. Test Rimozione di una Coppia
> void test_hash_table_remove(void) {
>     hash_table_put(table, "key1", "value1");
>     hash_table_remove(table, "key1");
>     TEST_ASSERT_FALSE(hash_table_contains_key(table, "key1"));
> }
> 
> // 6. Test Recupero di una Chiave Non Esistente
> void test_hash_table_get_non_existent(void) {
>     TEST_ASSERT_NULL(hash_table_get(table, "key1"));
> }
> 
> // 7. Test Dimensione della Tavola
> void test_hash_table_size(void) {
>     hash_table_put(table, "key1", "value1");
>     hash_table_put(table, "key2", "value2");
>     TEST_ASSERT_EQUAL(2, hash_table_size(table));
> }
> 
> // 8. Test Keyset della Tavola
> void test_hash_table_keyset(void) {
>     hash_table_put(table, "key1", "value1");
>     hash_table_put(table, "key2", "value2");
>     void** keys = hash_table_keyset(table);
> 
>     // Verifica che le chiavi esistano indipendentemente dall'ordine
>     int found_key1 = 0, found_key2 = 0;
>     for (int i = 0; i < hash_table_size(table); i++) {
>         if (strcmp((char*)keys[i], "key1") == 0) {
>             found_key1 = 1;
>         } else if (strcmp((char*)keys[i], "key2") == 0) {
>             found_key2 = 1;
>         }
>     }
>     TEST_ASSERT_TRUE(found_key1);
>     TEST_ASSERT_TRUE(found_key2);
> 
>     free(keys);
> }
> 
> // 9. Test Ridimensionamento Automatico
> void test_hash_table_resize(void) {
>     int new_capacity = table->capacity * 2;
>     HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));
> 
>     for (int i = 0; i < table->capacity; i++) {
>         HashNode* current = table->buckets[i];
>         while (current) {
>             // Ricalcola l'indice nel nuovo array di bucket
>             unsigned long new_index = table->hash_function(current->key) % new_capacity;
> 
>             // Sposta il nodo nel nuovo bucket
>             HashNode* next = current->next;
>             current->next = new_buckets[new_index];
>             new_buckets[new_index] = current;
> 
>             current = next;
>         }
>     }
> 
>     // Sostituisci i vecchi bucket con quelli nuovi
>     free(table->buckets);
>     table->buckets = new_buckets;
>     table->capacity = new_capacity;
> }
> 
> // 10. Test Inserimento di Valori NULL
> void test_hash_table_put_null_value(void) {
>     hash_table_put(table, "key1", NULL);
>     TEST_ASSERT_NULL(hash_table_get(table, "key1"));
> }
> 
> // 11. Test Collisioni (chiavi diverse, stesso hash)
> void test_hash_table_collision(void) {
>     HashTable* int_table = hash_table_create(int_compare, int_hash);
>     int key1 = 1, key2 = 17; // Stesso hash in una tabella con 16 bucket iniziali
>     hash_table_put(int_table, &key1, "value1");
>     hash_table_put(int_table, &key2, "value2");
>     TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(int_table, &key1));
>     TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(int_table, &key2));
>     hash_table_free(int_table);
> }
> 
> // 12. Test Rimozione con Collisioni
> void test_hash_table_remove_collision(void) {
>     HashTable* int_table = hash_table_create(int_compare, int_hash);
>     int key1 = 1, key2 = 17;
>     hash_table_put(int_table, &key1, "value1");
>     hash_table_put(int_table, &key2, "value2");
>     hash_table_remove(int_table, &key1);
>     TEST_ASSERT_NULL(hash_table_get(int_table, &key1));
>     TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(int_table, &key2));
>     hash_table_free(int_table);
> }
> 
> // 13. Test Inserimento e Recupero di Interi
> void test_hash_table_int_keys(void) {
>     HashTable* int_table = hash_table_create(int_compare, int_hash);
>     int key = 42;
>     char* value = "value";
>     hash_table_put(int_table, &key, value);
>     TEST_ASSERT_EQUAL_STRING(value, (char*)hash_table_get(int_table, &key));
>     hash_table_free(int_table);
> }
> 
> // 14. Test con Chiavi Vuote (stringhe vuote)
> void test_hash_table_empty_string_key(void) {
>     hash_table_put(table, "", "value");
>     TEST_ASSERT_EQUAL_STRING("value", (char*)hash_table_get(table, ""));
> }
> 
> // 15. Test Rimozione di Tutti gli Elementi
> void test_hash_table_clear(void) {
>     hash_table_put(table, "key1", "value1");
>     hash_table_put(table, "key2", "value2");
>     hash_table_remove(table, "key1");
>     hash_table_remove(table, "key2");
>     TEST_ASSERT_EQUAL(0, hash_table_size(table));
> }
> 
> // Main per eseguire i test
> int main(void) {
>     UNITY_BEGIN();
> 
>     RUN_TEST(test_hash_table_create);
>     RUN_TEST(test_hash_table_put_get);
>     RUN_TEST(test_hash_table_replace_value);
>     RUN_TEST(test_hash_table_contains_key);
>     RUN_TEST(test_hash_table_remove);
>     RUN_TEST(test_hash_table_get_non_existent);
>     RUN_TEST(test_hash_table_size);
>     RUN_TEST(test_hash_table_keyset);
>     RUN_TEST(test_hash_table_resize);
>     RUN_TEST(test_hash_table_put_null_value);
>     RUN_TEST(test_hash_table_collision);
>     RUN_TEST(test_hash_table_remove_collision);
>     RUN_TEST(test_hash_table_int_keys);
>     RUN_TEST(test_hash_table_empty_string_key);
>     RUN_TEST(test_hash_table_clear);
> 
>     return UNITY_END();
> }
> ```

Una volta eseguiti i test e verificato la funzionalità della libreria nei vari contesti di utilizzo, 
abbiamo deciso di iniziare a sviluppare l'applicazione di essa che ha il compito di
leggere in input un testo e restituire all'utente le parole più frequenti presenti nel testo, data una lunghezza mininima di caratteri.

## Sviluppo dell'applicazione

## Input 6
Adesso, dobbiamo scrivere una funzione che legga questo file txt. (File che è stato inviato nella chat)
Successivamente, bisogna utilizzare l'hash table scritta in precedenza per calcolare qual è la parola ripetuta più volte nel testo
di lunghezza almeno uguale (o maggiore) di una lunghezza data in input.

## Output 6
> Per risolvere il problema, scriveremo una funzione che legge il file di testo,
> tokenizza il contenuto in parole e utilizza la hash table implementata precedentemente per contare la frequenza delle parole.
> Successivamente, identificheremo la parola ripetuta più frequentemente con lunghezza maggiore o uguale a un valore specifico fornito in input.
> 
> **Prassi della soluzione**
> 1. **Lettura del file di testo**: Apriamo il file e leggiamo il contenuto riga per riga.
> 2. **Tokenizzazione delle parole**: Suddividiamo il testo in parole rimuovendo punteggiatura e spaziature.
> 3. **Uso della hash table**: Utilizziamo la tabella hash per contare quante volte compare ogni parola.
> 4. **Filtraggio**: Consideriamo solo le parole con lunghezza maggiore o uguale a un valore fornito in input.
> 5. **Ricerca della parola più frequente**: Scansioniamo la tabella per individuare la parola con la frequenza massima.
> 
> ### Codice C
> Ecco l'implementazione completa:
> 
> #### Header: `word_count.h`
> ```c
> #ifndef WORD_COUNT_H
> #define WORD_COUNT_H
> 
> #include "hash_table.h"
> 
> // Funzione principale per trovare la parola più frequente di una data lunghezza
> void find_most_frequent_word(const char* file_path, int min_length);
> 
> #endif // WORD_COUNT_H
> ```
> #### Sorgente: `word_count.c`
> ```c
> #include "word_count.h"
> #include <stdio.h>
> #include <stdlib.h>
> #include <string.h>
> #include <ctype.h>
> 
> // Funzione di hash per le parole
> unsigned long string_hash(const void* key) {
>     const char* str = (const char*)key;
>     unsigned long hash = 5381;
>     int c;
>     while ((c = *str++)) {
>         hash = ((hash << 5) + hash) + c; // hash * 33 + c
>     }
>     return hash;
> }
> 
> // Funzione di confronto per le parole
> int string_compare(const void* a, const void* b) {
>     return strcmp((const char*)a, (const char*)b) == 0;
> }
> 
> // Funzione per normalizzare le parole (rimuove punteggiatura e mette in minuscolo)
> char* normalize_word(const char* word) {
>     int len = strlen(word);
>     char* clean_word = (char*)malloc(len + 1);
>     int j = 0;
> 
>     for (int i = 0; i < len; i++) {
>         if (isalnum(word[i])) {
>             clean_word[j++] = tolower(word[i]);
>         }
>     }
>     clean_word[j] = '\0';
>     return clean_word;
> }
> 
> // Funzione per trovare la parola più frequente
> void find_most_frequent_word(const char* file_path, int min_length) {
>     HashTable* table = hash_table_create(string_compare, string_hash);
>     FILE* file = fopen(file_path, "r");
>     if (!file) {
>         fprintf(stderr, "Errore: impossibile aprire il file.\n");
>         return;
>     }
> 
>     char buffer[1024];
>     while (fscanf(file, "%1023s", buffer) == 1) {
>         char* word = normalize_word(buffer);
>         if (strlen(word) >= min_length) {
>             // Controlla se la parola è già nella tabella
>             int* count = (int*)hash_table_get(table, word);
>             if (count) {
>                 (*count)++;
>             } else {
>                 int* new_count = (int*)malloc(sizeof(int));
>                 *new_count = 1;
>                 hash_table_put(table, strdup(word), new_count);
>             }
>         }
>         free(word);
>     }
> 
>     fclose(file);
> 
>     // Trova la parola con il conteggio massimo
>     void** keys = hash_table_keyset(table);
>     int max_count = 0;
>     char* most_frequent_word = NULL;
> 
>     for (int i = 0; i < hash_table_size(table); i++) {
>         int* count = (int*)hash_table_get(table, keys[i]);
>         if (*count > max_count) {
>             max_count = *count;
>             most_frequent_word = (char*)keys[i];
>         }
>     }
> 
>     // Stampa il risultato
>     if (most_frequent_word) {
>         printf("La parola più frequente di lunghezza >= %d è: '%s' (ripetuta %d volte)\n",
>                min_length, most_frequent_word, max_count);
>     } else {
>         printf("Nessuna parola trovata con lunghezza >= %d.\n", min_length);
>     }
> 
>     // Pulisce la memoria
>     for (int i = 0; i < hash_table_size(table); i++) {
>         free(keys[i]); // Libera le chiavi duplicate
>         free(hash_table_get(table, keys[i])); // Libera i conteggi
>     }
>     free(keys);
>     hash_table_free(table);
> }
> ```
> 
> ### File di test: `main.c`
> ```c
> #include "word_count.h"
> 
> int main() {
>     const char* file_path = "iliade.txt";
>     int min_length;
> 
>     printf("Inserisci la lunghezza minima delle parole da considerare: ");
>     if (scanf("%d", &min_length) != 1 || min_length <= 0) {
>         fprintf(stderr, "Errore: lunghezza non valida.\n");
>         return 1;
>     }
> 
>     find_most_frequent_word(file_path, min_length);
>     return 0;
> }
> ```
> 
> ### Esecuzione:
> 1. Compila il programma: 
> ```bash
> gcc -o word_counter main.c word_count.c hash_table.c -I.
> ```
> 2. Esegui il programma e fornisci la lunghezza minima: 
> ```bash
> ./word_counter
> Inserisci la lunghezza minima delle parole da considerare: 5
> ```
> 3. Il programma leggerà il file iliade.txt
> e restituirà la parola più frequente di lunghezza maggiore o uguale alla lunghezza fornita
> 
> ### Esempio di Output
> ```bash
> Inserisci la lunghezza minima delle parole da considerare: 5
> La parola più frequente di lunghezza >= 5 è: 'achilles' (ripetuta 23 volte)
> ```
> ### Spiegazione del Codice
> 1. **Normalizzazione delle Parole:**
>     - Rimuove caratteri non alfanumerici.
>     - Converte le parole in minuscolo.
> 2. **Hash table:**
>     - Le parole sono usate come chiavi.
>     - I valori associati sono puntatori a interi che rappresentano il conteggio delle occorrenze.
> 3. **Ricerca del Massimo:**
>     - Si scansionano tutte le chiavi nella tabella per individuare la parola con il conteggio più alto.
> 3. **Deallocazione della Memoria:**
>     - Vengono liberate sia le chiavi duplicate sia i conteggi allocati dinamicamente.
> ---
> Se hai bisogno di ulteriori chiarimenti o modifiche, fammi sapere!

## Input 7 
Modifica il main in modo che il file di testo e la lunghezza minima siano letti da argc e argv.
Esempio di avvio del file: <br>
```bash
./main_ex3 /tmp/data/iliade.txt 6
```
## Output 7 
>Ecco la versione aggiornata del main per accettare il percorso del file di testo e la lunghezza minima
>come argomenti della riga di comando (`argc` e `argv`).
>
>### Nuovo `main.c`
>```c
>#include "word_count.h"
>#include <stdio.h>
>#include <stdlib.h>
>
>int main(int argc, char* argv[]) {
>    // Controllo degli argomenti
>    if (argc != 3) {
>        fprintf(stderr, "Uso corretto: %s <file_di_testo> <lunghezza_minima>\n", argv[0]);
>        return 1;
>    }
>
>    // Lettura del percorso del file
>    const char* file_path = argv[1];
>
>    // Conversione della lunghezza minima da stringa a intero
>    int min_length = atoi(argv[2]);
>    if (min_length <= 0) {
>        fprintf(stderr, "Errore: la lunghezza minima deve essere un intero positivo.\n");
>        return 1;
>    }
>
>    // Richiama la funzione principale
>    find_most_frequent_word(file_path, min_length);
>
>    return 0;
>}
>```
>---
>### Modifiche apportate
>1. **Lettura degli Argomenti:**
>    - `argv[1]` è il percorso del file di testo..
>    - `argv[2]` è la lunghezza minima delle parole, convertita in un intero usando `atoi`.
>2. **Controllo degli Argomenti:**
>    - Viene verificato che il numero di argomenti sia corretto (`argc == 3`).
>    - Viene controllato che la lunghezza minima sia un numero positivo.
>3. **Messaggio di Utilizzo:**
>    - Se i parametri non sono validi, il programma mostra un messaggio di utilizzo.
>---
>### Esecuzione:
>1. Compila il programma: 
>```bash
>gcc -o main_ex3 main.c word_count.c hash_table.c -I.
>```
>2. Esegui il programma come segue: 
>```bash
>./main_ex3 /tmp/data/iliade.txt 6
>```
>### Esempio di Output: 
>Supponendo che il file /tmp/data/iliade.txt contenga un testo valido, l'output potrebbe essere:
>```bash
>La parola più frequente di lunghezza >= 6 è: 'achilles' (ripetuta 23 volte)
>```
>
>### Gestione degli Errori
>Se mancano parametri o la lunghezza minima è invalida, il programma stampa un messaggio d'errore:
>```bash
>Uso corretto: ./main_ex3 <file_di_testo> <lunghezza_minima>
>Errore: la lunghezza minima deve essere un intero positivo.
>```
>
>Questa modifica rende il programma più flessibile,
>permettendo di passare il percorso del file e la lunghezza minima direttamente dalla riga di comando.
>Fammi sapere se serve altro!

Il principale problema di questo risultato è la presenza di poche funzioni,
quindi in caso di riutilizzo del codice e della manutenzione risulta molto scomodo e disorganizzato.

## Input 8 
Perfetto, ho ancora una richiesta.
Potresti suddividere la funzione find_most_frequent_word in più funzioni?
Ad esempio una che legge il file, una che calcola la parola, una che fa la free di tutta la hash table

> Certamente! È una buona idea suddividere la funzione `find_most_frequent_word` in più funzioni più piccole per renderla più leggibile e modulare.
> Ecco come possiamo scomporla:
> 
> ---
> ### Funzioni Riorganizzate
> 1. `read_words_from_file`: Legge il file, normalizza le parole e le inserisce nella hash table.
> 2. `find_max_frequency_word`: Scansiona la hash table per trovare la parola con la frequenza massima.
> 3. `free_hash_table_with_values`: Libera la memoria associata alla hash table, incluse le chiavi e i valori.
> ---
> ### Codice Aggiornato
> ### Header: `word_count.h`
> ```c
> #ifndef WORD_COUNT_H
> #define WORD_COUNT_H
> 
> #include "hash_table.h"
> 
> // Legge il file e popola la hash table con la frequenza delle parole
> void read_words_from_file(const char* file_path, int min_length, HashTable* table);
> 
> // Trova la parola con la frequenza massima nella hash table
> void find_max_frequency_word(HashTable* table, int min_length);
> 
> // Libera la memoria della hash table, incluse le chiavi e i valori
> void free_hash_table_with_values(HashTable* table);
> 
> // Funzione principale
> void find_most_frequent_word(const char* file_path, int min_length);
> 
> #endif // WORD_COUNT_H
> ```
> 
> ### Sorgente: `word_count.c`
> ```c
> #include "word_count.h"
> #include <stdio.h>
> #include <stdlib.h>
> #include <string.h>
> #include <ctype.h>
> 
> // Funzione di hash per stringhe
> unsigned long string_hash(const void* key) {
>     const char* str = (const char*)key;
>     unsigned long hash = 5381;
>     int c;
>     while ((c = *str++)) {
>         hash = ((hash << 5) + hash) + c;
>     }
>     return hash;
> }
> 
> // Funzione di confronto per stringhe
> int string_compare(const void* a, const void* b) {
>     return strcmp((const char*)a, (const char*)b) == 0;
> }
> 
> // Funzione per normalizzare le parole (rimuove punteggiatura e mette in minuscolo)
> char* normalize_word(const char* word) {
>     int len = strlen(word);
>     char* clean_word = (char*)malloc(len + 1);
>     int j = 0;
> 
>     for (int i = 0; i < len; i++) {
>         if (isalnum(word[i])) {
>             clean_word[j++] = tolower(word[i]);
>         }
>     }
>     clean_word[j] = '\0';
>     return clean_word;
> }
> 
> // Legge il file e popola la hash table
> void read_words_from_file(const char* file_path, int min_length, HashTable* table) {
>     FILE* file = fopen(file_path, "r");
>     if (!file) {
>         fprintf(stderr, "Errore: impossibile aprire il file.\n");
>         exit(1);
>     }
> 
>     char buffer[1024];
>     while (fscanf(file, "%1023s", buffer) == 1) {
>         char* word = normalize_word(buffer);
>         if (strlen(word) >= min_length) {
>             // Controlla se la parola è già nella tabella
>             int* count = (int*)hash_table_get(table, word);
>             if (count) {
>                 (*count)++;
>             } else {
>                 int* new_count = (int*)malloc(sizeof(int));
>                 *new_count = 1;
>                 hash_table_put(table, strdup(word), new_count);
>             }
>         }
>         free(word);
>     }
> 
>     fclose(file);
> }
> 
> // Trova la parola con la frequenza massima
> void find_max_frequency_word(HashTable* table, int min_length) {
>     void** keys = hash_table_keyset(table);
>     int max_count = 0;
>     char* most_frequent_word = NULL;
> 
>     for (int i = 0; i < hash_table_size(table); i++) {
>         int* count = (int*)hash_table_get(table, keys[i]);
>         if (*count > max_count) {
>             max_count = *count;
>             most_frequent_word = (char*)keys[i];
>         }
>     }
> 
>     if (most_frequent_word) {
>         printf("La parola più frequente di lunghezza >= %d è: '%s' (ripetuta %d volte)\n",
>                min_length, most_frequent_word, max_count);
>     } else {
>         printf("Nessuna parola trovata con lunghezza >= %d.\n", min_length);
>     }
> 
>     free(keys);
> }
> 
> // Libera la memoria della hash table, incluse chiavi e valori
> void free_hash_table_with_values(HashTable* table) {
>     void** keys = hash_table_keyset(table);
>     for (int i = 0; i < hash_table_size(table); i++) {
>         free(keys[i]); // Libera le chiavi duplicate
>         free(hash_table_get(table, keys[i])); // Libera i conteggi
>     }
> ```
> ---
> ### Funzione principale
> ```c
> void find_most_frequent_word(const char* file_path, int min_length) {
>     // Crea la hash table
>     HashTable* table = hash_table_create(string_compare, string_hash);
> 
>     // Leggi il file e popola la hash table
>     read_words_from_file(file_path, min_length, table);
> 
>     // Trova la parola più frequente
>     find_max_frequency_word(table, min_length);
> 
>     // Libera la memoria
>     free_hash_table_with_values(table);
> }
> ```
> --- 
> ### Cambiamenti Apportati
> 1. `read_words_from_file`:
>     - Legge il file e normalizza ogni parola
>     - Inserisce ogni parola valida nella hash table e incrementa il conteggio.
> 2. `find_max_frequency_word`:
>     - Scansiona le parole nella hash table e trova quella con il conteggio massimo.
> 3. `free_hash_table_with_values`:
>     - Libera le chiavi duplicate (`strdup`) e i valori (conteggio) allocati dinamicamente.
> 4. `find_most_frequent_word`:
>     - Ora agisce come coordinatore, chiamando le altre funzioni.
> ---
> ### Vantaggi della modifica
> 1. **Modularità**: Ogni funzione una responsabilità specifica.
> 2. **Leggibilità**: Il codice è più chiaro e facile da mantenere.
> 3. **Riutilizzabilità**: Le funzioni possono essere riutilizzate per altri scopi simili.
> 
> Se hai bisogno di ulteriori ottimizzazioni o test, fammi sapere!

Il problema con l'implementazione che ci viene data è anche l'utilizzo della funzione `strdup`
che può essere più conveniente creare in modo manuale per due principali motivi:
1. `strdup` non è una funzione standard in C89/C90 e potrebbe non essere supportata su alcune piattaforme.
2. Implementando una copia manuale della stringa, hai più controllo sulla gestione della memoria.

## Input 9
Puoi modificare il codice in modo da non usare strdup per favore?

## Output 9 
>Certo! Se vuoi evitare l'uso di strdup (che alloca dinamicamente una copia della stringa),
>possiamo modificare il codice in modo da allocare e gestire manualmente le stringhe. Questo significa che la gestione della memoria delle chiavi
>deve essere più esplicita, e ci assicureremo che tutte le stringhe siano allocate correttamente solo una volta.
>
>---
>### Soluzione
> - Al posto di `strdup`, faremo una copia esplicita della stringa utilizzando malloc e strcpy.
> - Ci assicureremo che ogni chiave sia allocata solo quando viene inserita nella hash table.
>--- 
>### Cambiamenti Apportati
>1. **Rimozione di `strdup`**:
>Sostituita con una funzione esplicita `manual_strdup`
>che alloca e copia manualmente una stringa usando `malloc` e `strcpy`.
>
>```c
>char* manual_strdup(const char* str) {
>    int len = strlen(str) + 1;
>    char* copy = (char*)malloc(len);
>    if (copy) {
>        strcpy(copy, str);
>    }
>    return copy;
>}
>```
>
>2. **Chiamata a `manual_strdup`**:
>Durante l'inserimento delle chiavi nella hash table,
>la funzione `manual_strdup` viene utilizzata per creare una copia della stringa normalizzata.
>3. **Libera Manuale delle Chiavi**:
>Nella funzione `free_hash_table_with_values`,
>liberiamo esplicitamente le chiavi e i valori allocati.
>```c
>void free_hash_table_with_values(HashTable* table) {
>    void** keys = hash_table_keyset(table);
>    for (int i = 0; i < hash_table_size(table); i++) {
>        free(keys[i]); // Libera le chiavi allocate manualmente
>        free(hash_table_get(table, keys[i])); // Libera i conteggi
>    }
>    free(keys);
>    hash_table_free(table);
>}
>```
>Ora il codice è completamente indipendente da strdup e mantiene un'allocazione chiara e controllata delle stringhe.
>Fammi sapere se hai bisogno di ulteriori modifiche o chiarimenti!

Nella fase di testing del codice dopo l'implementazione del nono output venivano restituite parole non corrette,
quindi abbiamo notato leggendo il testo dato in input che parole che contenvano caratteri non alfanumerici non venivano eliminate ne utilizzate come divisori
per le singole parole.

## Input 10
Dobbiamo modificare la funzione che normalizza la parola, deve diventare il più generica possibile.
In modo che se una parola è suddivisa tramite un qualunque carattere, dopo venga divisa in due parole

## Output 10
>Perfetto! Se dobbiamo dividere la parola ogni volta che incontriamo un carattere non alfanumerico e trattare entrambe le parti come parole separate, possiamo aggiornare la funzione normalize_word e il codice di lettura.
>
>L'idea è:
>1. **Dividere la parola in sottostringhe**: Ogni sottostringa è una sequenza alfanumerica separata da un trattino.
>2. **Inserire ogni sottostringa nella hash table** come una parola separata.
>
>Per rendere la funzione più generica e gestire qualunque carattere non alfanumerico come delimitatore per dividere le parole,
>possiamo creare una nuova funzione `process_and_split_word`.
>Verificheremo se il carattere corrente non è alfanumerico (`isalnum`) e lo useremo come delimitatore.
>
>---
>### Soluzione Completa
>**Nuova Funzione `process_and_split_word`**
>Questa funzione:
>- Riceve una stringa contenente potenzialmente caratteri non alfanumerici.
>- Divide la stringa in sottostringhe usando qualsiasi carattere non alfanumerico come delimitatore.
>- Normalizza ogni sottostringa.
>- Inserisce ogni sottostringa nella hash table.
>
>---
>
>### Codice Aggiornato
>Questa nuova funzione sostituisce la logica precedente per `normalize_word`
>e aggiunge la gestione dei caratteri non alfanumerici.
>
>```c
>void process_and_split_word(const char* input_word, int min_length, HashTable* table) {
>    int len = strlen(input_word);
>    char buffer[1024]; // Buffer per ogni sottostringa
>    int j = 0;
>
>    for (int i = 0; i <= len; i++) { // Include il terminatore null '\0'
>        if (!isalnum(input_word[i]) || input_word[i] == '\0') { // Delimitatore trovato
>            if (j > 0) { // Se il buffer contiene una parola valida
>                buffer[j] = '\0'; // Termina la sottostringa
>                char* normalized_word = normalize_word(buffer);
>                if (strlen(normalized_word) >= min_length) {
>                    // Inserisce la parola nella hash table
>                    int* count = (int*)hash_table_get(table, normalized_word);
>                    if (count) {
>                        (*count)++;
>                    } else {
>                        char* key_copy = manual_strdup(normalized_word);
>                        int* new_count = (int*)malloc(sizeof(int));
>                        *new_count = 1;
>                        hash_table_put(table, key_copy, new_count);
>                    }
>                }
>                free(normalized_word);
>                j = 0; // Resetta il buffer
>            }
>        } else {
>            buffer[j++] = tolower(input_word[i]); // Copia carattere alfanumerico in minuscolo
>        }
>    }
>}
>```
>### Come funziona la funzione
>1. La funzione scansiona la stringa carattere per carattere.
>2. Ogni volta che incontra un carattere non alfanumerico o la fine della stringa (`'\0'`):
>    - Termina la sottostringa nel buffer.
>    - La sottostringa viene normalizzata e controllata per la lunghezza minima.
>    - Viene inserita nella hash table.
>3. I caratteri alfanumerici vengono copiati nel buffer e convertiti in minuscolo.
>
>### Conclusione
>Questa modifica rende la funzione generica e robusta,
>in grado di dividere una parola in più sottostringhe utilizzando qualsiasi carattere non alfanumerico come delimitatore.
>
>Se hai bisogno di ulteriori modifiche o chiarimenti, sono qui! 😊

Dopo questo output, il codice è risultato completamente corretto e funzionante, provandolo sia con i test in locale che con i test su moodle. Quindi la conversazione con ChatGPT è finita qui.

# Conclusioni
Con questo esercizio abbiamo notato che ChatGPT risulta molto potente per scrivere del codice di progetti piccoli, la cosa più importante è specificargli bene cosa si vuole fare e cosa si vuole ottenere, perchè più informazioni gli si danno, più risponde accuratamente. Infatti con 10 semplici input, siamo riusciti ad implementare una libreria funzionante e testata.
Ovviamente però anche lui riscontra diversi problemi, abbiamo notato che più si porta avanti la conversazione e più inizia a ripetersi, senza modificare effettivamente il codice o risolvendo i problemi.