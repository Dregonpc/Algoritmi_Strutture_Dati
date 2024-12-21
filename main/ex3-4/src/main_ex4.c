#include <stdio.h>
#include <stdlib.h>
#include "../headers/graph.h"

void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));
//start è il nodo di partenza da cui cominciare la visita, la funzione restituisce l'array dei nodi nell'ordine di visita.
//eventualmente, la funzione restituisce null se il nodo start non è presente nel grafo gr.



int main(int argc, char* argv[]) {
  return 0;
}