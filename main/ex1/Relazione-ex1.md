# Relazione esercizio 1 - Merge Sort e Quick Sort

## Indice
1. [Tabella dei tempi](#tabella-dei-tempi-registrati)
2. [Tabella dei tempi medi](#tabella-dei-tempi-medi)
3. [Considerazioni sui tipi dei campi](#considerazioni-sui-tipi-dei-campi)
4. [Considerazioni sugli algoritmi di ordinamento](#considerazioni-sugli-algoritmi-di-ordinamento)

## Tabella dei tempi registrati
|                 |            Merge           |            Quick           |
|-----------------|----------------------------|----------------------------|
| (String) Field 1|   23s, 28s, 23s, 23s, 22s  |   30s, 29s, 29s, 29s, 29s  |
| (Int) Field 2   |   14s, 14s, 13s, 13s, 13s  |   17s, 16s, 17s, 17s, 16s  |
| (FLoat) Field 3 |   12s, 12s, 12s, 12s, 12s  |   16s, 15s, 15s, 15s, 15s  |

Per la nostra relazione i dati rilevati sono stati calcolati tramite la libreria time che il linguaggio C ci mette a disposizione e abbiamo scelto di effettuare 5 rilevazioni per ogni tipologia di dato e per ogni algoritmo di ordinamento

## Tabella dei tempi medi
|                 |   Merge  |   Quick  |
|-----------------|----------|----------|
| (String) Field 1|   23,8s  |   29,2s  |
| (Int) Field 2   |   13,4s  |   16,6s  |
| (Float) Field 3 |   12,0s  |   15,2s  |

Successivamente per avere una comparazione più semplice abbiamo calcolato la media aritmetica dei vari tempi di esecuzione.

## Considerazioni sui tipi dei campi
Dai dati ottenuti possiamo constatare che i tempi di ordinamento **sono più lunghi per quanto riguarda il campo delle stringhe**, cosa abbastanza logica dato che per comparare due stringhe viene utilizzata la funzione strcmp() che ha il compito di dover scorrere le stringhe fino a quando non si incontrano due caratteri diversi oppure tutta la stringa nel caso che si tratti di due stringhe, di conseguenza è una comparazione più lenta rispetto al confronto tra valori numerici.

Sorprendentemente se confrontiamo i dati di tipo int e float hanno una piccola differenza di confronto che posizionano i **numeri in virgola mobile al primo posto per la velocità di ordinamento**, nonostante il confronto con dei numeri float sia più complesso rispetto agli int, una possibile spiegazione è data dalle FPU ovvero le Floating-Point Unit che sono unità di calcolo progettate per operare su vettori di dati, il che può accelerare notevolmente le operazioni di ordinamento.

## Considerazioni sugli algoritmi di ordinamento
Come si evince dai dati **in questo caso** di utilizzo **il Merge sort ha effettuato tempi migliori** e quindi più bassi rispetto al Quick sort, questo probabilmente è dovuto ad una scelta particolarmente sbilanciata nel pivot nel Quick sort, questo implica che la complessità da O(n log n) di media arriva a O(n²) questo comporta una instabilità non presente nel Merge che ha sempre la stessa complessità O(n log n).