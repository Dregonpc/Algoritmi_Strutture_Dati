/**
 * @brief struct representing a graph
 * @param labelled 1 if the graph is labelled, 0 otherwise
 * @param directed 1 if the graph is directed, 0 otherwise
 * @param hash function to hash nodes
 * @param compare function to compare nodes
 * @param nodes set of nodes
 * @param edges set of edges
 * @param num_nodes number of nodes
 * @param num_edges number of edges
 * @param size size of the set of nodes
 * @param size_edges size of the set of edges
 */

typedef struct graph {
   int labelled;
   int directed;
   unsigned long (*hash)(const void*);
   int (*compare)(const void*, const void*);
   void* nodes;
   void* edges;
   size_t num_nodes;
   size_t num_edges;
   size_t size;
   size_t size_edges;
} *Graph;

/**
 * @brief struct representing an edge
 * @param source the source node
 * @param dest the destination node
 * @param label the label of the edge
 */
typedef struct edge {
   void* source; //nodo d'origine
   void* dest; //nodo di destinazione
   void* label; //etichetta dell'arco
}Edge;

/**
 * @brief create a new graph
 * @param labelled 1 if the graph is labelled, 0 otherwise
 * @param directed 1 if the graph is directed, 0 otherwise
 * @param compare function to compare nodes
 * @param hash function to hash nodes -- O(1)
 */
Graph graph_create(int labelled, int directed, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));

//crea un grafo vuoto, etichettato se labelled == 1 e diretto se directed == 1,
//le funzioni f1 e f2 sono necessarie per la costruzione della tavola hash che deve essere usata dalla libreria -- O(1)

/**
 * @brief determinate if the graph is directed or not
 * @param gr the graph
 * @return 1 if the graph is directed, 0 if the graph is not directed, -1 if the graph is NULL
 */
int graph_is_directed(const Graph gr);                                                           // dice se il grafo è diretto o meno -- O(1)

/**
 * @brief determinate if the graph is labelled or not
 * @param gr the graph
 * @return 1 if the graph is labelled, 0 if the graph is not labelled, -1 if the graph is NULL
 */
int graph_is_labelled(const Graph gr);                                                           // dice se il grafo è etichettato o meno -- O(1)

/**
 * @brief determinate if the graph is empty or not
 * @param gr the graph
 */
int graph_is_empty(const Graph gr);                                                              // dice se il grafo è vuoto -- O(1)

/**
 * @brief add a node to the graph
 * @param gr the graph
 * @param node the node to add
 */
int graph_add_node(Graph gr, const void* node);                                                  // aggiunge un nodo -- O(1)

/**
 * @brief add an edge to the graph
 * @param gr the graph
 * @param node1 the first node
 * @param node2 the second node
 * @param label the label of the edge
 */
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);           // aggiunge un arco dati estremi ed etichetta -- O(1) (*)

/**
 * @brief determinate if a node is in the graph
 * @param gr the graph
 */
int graph_contains_node(const Graph gr, const void* node);                                       // controlla se un nodo è nel grafo -- O(1)

/**
 * @brief determinate if an edge is in the graph
 * @param gr the graph
 */
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);                   // controlla se un arco è nel grafo -- O(1) (*)

/**
 * @brief remove a node from the graph
 * @param gr the graph
 * @param node the node to remove
 */
int graph_remove_node(Graph gr, const void* node);                                               // rimuove un nodo dal grafo -- O(N)

/**
 * @brief remove an edge from the graph
 * @param gr the graph
 * @param node1 the first node
 * @param node2 the second node
 */
int graph_remove_edge(Graph gr, const void* node1, const void* node2);                           // rimuove un arco dal grafo -- O(1) (*)

/**
 * @brief get the number of nodes in the graph
 * @param gr the graph
 */
int graph_num_nodes(const Graph gr);                                                             // numero di nodi -- O(1)

/**
 * @brief get the number of edges in the graph
 * @param gr the graph
 */
int graph_num_edges(const Graph gr);                                                             // numero di archi -- O(N)

/**
 * @brief get the nodes of the graph
 * @param gr the graph
 */
void** graph_get_nodes(const Graph gr);                                                          // recupero dei nodi del grafo -- O(N)

/**
 * @brief get the edges of the graph
 * @param gr the graph
 */
Edge** graph_get_edges(const Graph gr);                                                          // recupero degli archi del grafo -- O(N)

/**
 * @brief get the neighbours of a node
 * @param gr the graph
 * @param node the node
 */
void** graph_get_neighbours(const Graph gr, const void* node);                                   // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)

/**
 * @brief get the number of neighbours of a node
 * @param gr the graph
 * @param node the node
 */
int graph_num_neighbours(const Graph gr, const void* node);                                      // recupero del numero di nodi adiacenti ad un dato nodo -- O(1)

/**
 * @brief get the label of an edge
 * @param gr the graph
 * @param node1 the first node
 * @param node2 the second node
 */
void* graph_get_label(const Graph gr, const void* node1, const void* node2);                     // recupero dell'etichetta di un arco -- O(1) (*)

/**
 * @brief free the memory of the graph
 * @param gr the graph
 */
void graph_free(Graph gr);

