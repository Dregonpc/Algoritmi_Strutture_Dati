#include "../headers/graph.h"
#include "../headers/hash_table.h"
#include <stdio.h>

struct graph {
  HashTable* nodes;
  int directed;
  int labelled;
  int num_nodes;
  int num_edges;
};

Graph graph_create(int labelled, int directed, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
  Graph gr = (Graph)malloc(sizeof(Graph));

  if (gr == NULL) {
    printf("Error allocation memory for graph!");
    return NULL;
  }

  gr->nodes = hash_table_create(compare, hash);
  gr->directed = directed;
  gr->labelled = labelled;
  gr->num_nodes = 0;
  gr->num_edges = 0;
  
  return gr;
}

int graph_is_directed(const Graph gr) {
  if (gr != NULL)
    return gr->directed;
  else
    return -1;
}

int graph_is_labelled(const Graph gr) {
  if (gr != NULL)
    return gr->directed;
  else
    return -1;
}

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
  if (gr == NULL) 
    return -1;

  if (hash_table_contains_key(gr->nodes, node))
    return 0;
  
  HashTable* adjacency_list = hash_table_create(gr->nodes->compare_keys, gr->nodes->hash_function);
  hash_table_put(gr->nodes, (void*)node, adjacency_list);
  gr->num_nodes++;
  
  return 1;
}

int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label){
  if (gr == NULL)
    return -1;
  
  if (!hash_table_contains_key(gr->nodes, node1) || !hash_table_contains_key(gr->nodes, node2))
    return 0;

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node1);
  if (hash_table_contains_key(adjacency_list, node2))
    return 0;
  
  hash_table_put(adjacency_list, (void*)node2, (void*)label);
  gr->num_edges++;

  if (!gr->directed) {
    HashTable* reverse_adjacency_list = (HashTable*)hash_table_get(gr->nodes, node2);
    hash_table_put(reverse_adjacency_list, (void*)node1, (void*)label);
  }

  return 1;
}

int graph_contains_node(const Graph gr, const void* node) {
  if (gr == NULL)
    return -1;

  return hash_table_contains_key(gr->nodes, node);
}

int graph_contains_edge(const Graph gr, const void* node1, const void* node2) {
  if (gr == NULL)
    return -1;

  if (!hash_table_contains_key(gr->nodes, node1))
    return 0;

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node1);
  return hash_table_contains_key(adjacency_list, node2);
}

int graph_remove_node(Graph gr, const void* node) {
  if (gr == NULL)
    return -1;

  if (!hash_table_contains_key(gr->nodes, node))
    return 0;
  
  void** all_nodes = graph_get_nodes(gr);
  for (int i = 0; i < gr->num_nodes; i++) {
    HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, all_nodes[i]);
    if (hash_table_contains_key(adjacency_list, node)) {
      hash_table_remove(adjacency_list, node);
      gr->num_edges--;
    }
  }
  free(all_nodes);

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node);
  hash_table_free(adjacency_list);

  hash_table_remove(gr->nodes, node);
  gr->num_nodes--;

  return 1;
}

int graph_remove_edge(Graph gr, const void* node1, const void* node2) {
  if (gr == NULL)
    return -1;
  
  if (!hash_table_contains_key(gr->nodes, node1) || !hash_table_contains_key(gr->nodes, node2))
    return 0;

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node1);
  if (!hash_table_contains_key(adjacency_list, node2))
    return 0;

  hash_table_remove(adjacency_list, node2);
  gr->num_edges--;

  if (!gr->directed) {
    HashTable* reverse_adjacency_list = (HashTable*)hash_table_get(gr->nodes, node2);
    hash_table_remove(reverse_adjacency_list, node1);
  }

  return 1;
}

int graph_num_nodes(const Graph gr) {
  if (gr != NULL)
    return gr->num_nodes;
  else
    return -1;
}

int graph_num_edges(const Graph gr) {
  if (gr != NULL)
    return gr->num_edges;
  else
    return -1;
}

void** graph_get_nodes(const Graph gr) {
  if (gr == NULL)
    return NULL;
  
  return hash_table_keyset(gr->nodes);
}

Edge** graph_get_edges(const Graph gr) {
  if (gr == NULL)
    return NULL;
  
  Edge** edges = (Edge**)malloc(gr->num_edges * sizeof(Edge*));

  if (edges == NULL) {
    printf("Error allocation memory for edges!");
    return NULL;
  }

  int index = 0;

  void** nodes = graph_get_nodes(gr);
  for (int i = 0; i < gr->num_nodes; i++) {
    HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, nodes[i]);
    void** neighbours = hash_table_keyset(adjacency_list);
    for (int j = 0; j < hash_table_size(adjacency_list); j++) {
      Edge* edge = (Edge*)malloc(sizeof(Edge));
      if (edge == NULL) {
        printf("Error allocation memory for edge!");
        free(edges);
        return NULL;
      }
      edge->source = nodes[i];
      edge->dest = neighbours[j];
      edge->label = hash_table_get(adjacency_list, neighbours[j]);
      edges[index++] = edge;
    }
    free(neighbours);
  }
  free(nodes);

  return edges;
}

void** graph_get_neighbours(const Graph gr, const void* node) {
  if (gr == NULL)
    return NULL;
  
  if (!hash_table_contains_key(gr->nodes, node))
    return NULL;

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node);
  return hash_table_keyset(adjacency_list);
}

int graph_num_neighbours(const Graph gr, const void* node) {
  if (gr == NULL)
    return -1;
  
  if (!hash_table_contains_key(gr->nodes, node))
    return 0;

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node);
  return hash_table_size(adjacency_list);
}

void* graph_get_label(const Graph gr, const void* node1, const void* node2) {
  if (gr == NULL)
    return NULL;
  
  if (!hash_table_contains_key(gr->nodes, node1))
    return NULL;

  HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, node1);
  return hash_table_get(adjacency_list, node2);
}

void graph_free(Graph gr) {
  if (gr == NULL)
    return;

  void** nodes = graph_get_nodes(gr);

  for (int i = 0; i < gr->num_nodes; i++) {
    HashTable* adjacency_list = (HashTable*)hash_table_get(gr->nodes, nodes[i]);

    void** neighbours = hash_table_keyset(adjacency_list);

    if (gr->labelled) {
      for (int j = 0; j < hash_table_size(adjacency_list); j++) {
        free(hash_table_get(adjacency_list, neighbours[j]));
      }
    }

    free(neighbours);
    hash_table_free(adjacency_list);
  }

  free(nodes);
  hash_table_free(gr->nodes);
  free(gr);
}
