#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/graph.h"

/**
 * @brief visit the graph in depth first order
 * @param gr the graph
 * @param start the starting node
 * @param compare the comparison function
 * @param hash the hash function
 * @return the array of nodes in the order of visit, null if the starting node is not in the graph
 */
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));
//start è il nodo di partenza da cui cominciare la visita, la funzione restituisce l'array dei nodi nell'ordine di visita.
//eventualmente, la funzione restituisce null se il nodo start non è presente nel grafo gr.



int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Error, to start:\nmain_ex3-4.c (Path of the file to read) (City) (Path of the file to write on)");
    exit(EXIT_FAILURE);
  }

  char* readFile = argv[1];
  char* city = argv[2];
  char* writeFile = argv[3];

  //Graph gr = graph_create(0, 0, );
  //load_graph_from_csv(gr, readFile);

}

void load_graph_from_csv(Graph gr, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("Error opening file (input file).\n");
    exit(EXIT_FAILURE);
  }

  char line[1024];
  while (fgets(line, sizeof(line), file)) {
    char* place1 = strtok(line, ",");
    char* place2 = strtok(NULL, ",");
    char* distance_str = strtok(NULL, ",");
    if (!place1 || !place2 || !distance_str)
      continue;

    float distance = atof(distance_str);

    graph_add_node(gr, strdup(place1));
    graph_add_node(gr, strdup(place2));
    graph_add_edge(gr, place1, place2, strdup(distance_str));
  }

  fclose(file);
}