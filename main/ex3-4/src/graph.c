#include "../headers/graph.h"
#include "../../ex3/headers/hash_table.h"

int graph_is_directed(const Graph gr) {
  if (gr != NULL)
    return gr->directed;
  else
    return -1;
}                                                           // dice se il grafo è diretto o meno -- O(1)

int graph_is_labelled(const Graph gr) {
  if (gr != NULL)
    return gr->directed;
  else
    return -1;
}                                                           // dice se il grafo è etichettato o meno -- O(1)

int graph_is_empty(const Graph gr) {
  if (gr != NULL) {
    if (gr->num_nodes == 0)
      return 1;
    else
      return 0;
  }
  else
    return -1;
}

int graph_add_node(Graph gr, const void* node) {

}                                                  // aggiunge un nodo -- O(1)

int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label){
  
}           // aggiunge un arco dati estremi ed etichetta -- O(1) (*)

int graph_contains_node(const Graph gr, const void* node) {

}                                       // controlla se un nodo è nel grafo -- O(1)

int graph_contains_edge(const Graph gr, const void* node1, const void* node2);                   // controlla se un arco è nel grafo -- O(1) (*)

int graph_remove_node(Graph gr, const void* node);                                               // rimuove un nodo dal grafo -- O(N)

int graph_remove_edge(Graph gr, const void* node1, const void* node2);                           // rimuove un arco dal grafo -- O(1) (*)

int graph_num_nodes(const Graph gr) {
  if (gr != NULL)
    return gr->num_nodes;
  else
    return -1;
}                                                             // numero di nodi -- O(1)

int graph_num_edges(const Graph gr) {
  if (gr != NULL)
    return gr->num_edges;
  else
    return -1;
}                                                             // numero di archi -- O(N)

void** graph_get_nodes(const Graph gr);                                                          // recupero dei nodi del grafo -- O(N)

Edge** graph_get_edges(const Graph gr);                                                          // recupero degli archi del grafo -- O(N)

void** graph_get_neighbours(const Graph gr, const void* node);                                   // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)

int graph_num_neighbours(const Graph gr, const void* node);                                      // recupero del numero di nodi adiacenti ad un dato nodo -- O(1)

void* graph_get_label(const Graph gr, const void* node1, const void* node2);                     // recupero dell'etichetta di un arco -- O(1) (*)

void graph_free(Graph gr) {
  if (gr != NULL) {
    for (int i = 0; i < gr->num_nodes; i++) {
      free(gr->nodes[i]);
    }
    free(gr->nodes);
    for (int i = 0; i < gr->num_edges; i++) {
      free(gr->edges[i]);
    }
    free(gr->edges);
    free(gr);
  }
}

