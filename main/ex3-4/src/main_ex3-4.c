#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/queue.h"
#include "../headers/hash_table.h"
#include "../headers/graph.h"

unsigned long string_hash(const void* key) {
  const char* str = (const char*)key;
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

int string_compare(const void* a, const void* b) {
  return strcmp((const char*)a, (const char*)b) == 0;
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

    //float distance = atof(distance_str);
    char* place1_copy = strdup(place1);
    char* place2_copy = strdup(place2);
    char* distance_copy = strdup(distance_str);

    graph_add_node(gr, place1_copy);
    graph_add_node(gr, place2_copy);
    graph_add_edge(gr, place1_copy, place2_copy, distance_copy);
  }

  fclose(file);
}

/**
 * @brief visit the graph in depth first order
 * @param gr the graph
 * @param start the starting node
 * @param compare the comparison function
 * @param hash the hash function
 * @return the array of nodes in the order of visit, null if the starting node is not in the graph
 */
//start è il nodo di partenza da cui cominciare la visita, la funzione restituisce l'array dei nodi nell'ordine di visita.
//eventualmente, la funzione restituisce null se il nodo start non è presente nel grafo gr.
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
  if (!graph_contains_node(gr, start)) {
    return NULL;
  }

  int num_nodes = graph_num_nodes(gr);
  void** visited_nodes = (void**)malloc(num_nodes * sizeof(void*));
  if (!visited_nodes) {
    printf("Error allocation memory!\n");
    return NULL;
  }

  HashTable* visited = hash_table_create(compare, hash);

  Queue* queue = create_queue(num_nodes);
  enqueue(queue, start);
  hash_table_put(visited, start, (void*)1);

  int index = 0;

  while (!is_queue_empty(queue)) {
    void* current = dequeue(queue);
    visited_nodes[index++] = current;

    void** neighbours = graph_get_neighbours(gr, current);
    int num_neighbours = graph_num_neighbours(gr, current);

    for (int i = 0; i < num_neighbours; i++) {
      if (!hash_table_contains_key(visited, neighbours[i])) {
        enqueue(queue, neighbours[i]);
        hash_table_put(visited, neighbours[i], (void*)1);
      }
    }

    free(neighbours);
  }

  free_queue(queue);
  hash_table_free(visited);

  return visited_nodes;
}

void write_to_file(Graph gr, void** visited, char* outFile) {
  FILE* file = fopen(outFile, "w");
  if (file == NULL) {
    printf("Error opening the file %s!\n", outFile);
    free(visited);
    return;
  }

  int num_nodes = graph_num_nodes(gr);
  for (int i = 0; i < num_nodes; i++) {
    if (visited[i] != NULL && strlen((char*)visited[i]) > 0) 
      fprintf(file, "%s\n", (char*)visited[i]);
  }

  fclose(file);
  free(visited);

  printf("I nomi delle città visitate sono stati salvati in %s.\n", outFile);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Error, to start:\nmain_ex3-4.c (Path of the file to read) (City) (Path of the file to write on)");
    exit(EXIT_FAILURE);
  }

  char* readFile = argv[1];
  char* city = argv[2];
  char* writeFile = argv[3];

  Graph gr = graph_create(1, 0, string_compare, string_hash);
  load_graph_from_csv(gr, readFile);

  void** visited = breadth_first_visit(gr, city, string_compare, string_hash);

  if (visited == NULL) {
    printf("La città di partenza non è stata trovata dentro al grafo.\n");
  }
  else {
    write_to_file(gr, visited, writeFile);
  }

  graph_free(gr);

  return 0;
}
