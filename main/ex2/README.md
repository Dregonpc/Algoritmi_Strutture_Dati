# Relazione esercizio 2 - Edit distance
## Studenti : 
- **Davide Trapani**
- **Matteo Saracino**

## Indice
1. [Scelta implentativa](#scelta-implementativa)
2. [Problema della mancanza di un contesto](#problema-della-mancanza-di-un-contesto)
3. [Tempi di esecuzione](#tempi-di-esecuzione)

## Scelta implementativa
Abbiamo deciso che per ogni parola del testo da correggere, venissero stampate a schermo 5 parole con la distanza minima, anche per le parole corrette (in cui quindi la parola con la distanza minima era se stessa). Questo porta sicuramente ad uno spreco di risorse, ma abbiamo deciso di farlo per far visualizzare la correttezza dell'algoritmo.

## Problema della mancanza di un contesto
Con la mancanza di un contesto, il programma non è in grado di capire il significato delle parole che sta correggendo, quindi le parole con la distanza minima che verranno stampate saranno le prime trovate in ordine alfabetico, anche se magari sono parole senza senso e più basso nel dizionario c'è n'è sono altre che hanno un senso ma hanno la stessa distanza delle precedenti.

## Tempi di esecuzione
I tempi per l'esecuzione sono stati calcolati con il comando "time" che il terminale di Linux ci mette a disposizione. <br>
Nel funzionamento normale il programma ha impiegato 28.289 secondi per calcolare e stampare tutte le parole con le rispettive correzioni.<br>
Se invece rimuoviamo l'interfaccia utente (quindi tutte le varie printf) il programma impiega 25.915 secondi.<br>
