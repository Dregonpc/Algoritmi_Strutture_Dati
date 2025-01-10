# Esercizio 3-4 - Grafi sparsi e Visita in Ampiezza

## Table of Contents
1. [Scelta implentativa](#scelta-implementativa)
2. [Tempi di esecuzione](#tempi-di-esecuzione)
3. [Osservazioni](#osservazioni)
4. [Conclusioni](#conclusioni)

## Scelta implentativa
Data la richiesta dell'esercizio abbiamo sviluppato una struttura dati `graph.h` che utilizza i puntatori `void *` per avere un'implementazione il pìu generica possibile, a discrezione dell'utente il grafo può essere ettichettato (`labelled`) oppure no, diretto (`directed`) e non diretto.
Il grafo viene rappresentato utilizzando le hash table, **ogni nodo del grafo è una chiave** della tabella, **il suo valore associato è un'altra tabella hash che rappresenta la sua lista di adiacenza**.<br>
Successivamente abbiamo creato l'applicazione che ha il compito di elencare tutte le città che è possibile visitare data una città di partenza, questo è possibile immagazzinando le città e i loro collegamenti tramite un grafo ettichettato e non diretto.
La visita del grafo viene effettuata con la funzione `breadth_first_visit` che esplora in ampiezza la struttura dati con il supporto di una coda (implementata con la libreria `queue.h`) che ne migliora le prestazioni.

## Tempi di esecuzione
|   Città   |   Time   |
|---------  |----------|
| Torino    |  0,233s  |
| Caselette |  0,220s  |
| Massafra  |  0,204s  |

I tempi per l'esecuzione sono stati calcolati con il comando "time" che il terminale di Linux ci mette a disposizione. <br>

## Osservazioni
Durante alcune prove abbiamo riscontrato che nel file che viene dato in input sono presenti 4 città che non sono collegate con le altre, nello specifico:
- da Borsoi è possibile arrivare a Chies d'alpago, ma non sono presenti città che arrivano a Borsoi
- da Levanzo è possibile arrivare a De Giergi (e viceversa), ma non sono presenti città che arrivano ne a Levanzo ne a De Giergi.

Inoltre il file contiene ripetizioni della stessa città magari in lingua differente, come ad esempio Torino e Turin, cosa che rende ulteriormente il file molto grezzo.

## Conclusioni
Questo esercizio ci ha permesso di comprendere a pieno che i grafi sono ottimi per quanto rigurarda la memorizzazione di informazioni complesse come appunto la distanza di varie città italiane connesse tra di loro.