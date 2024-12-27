#include "../main/ex3-4/headers/graph.h"
#include "Unity/unity.h"
#include <string.h>
#include <stdlib.h>

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

Graph graph;

void setUp(void) {
    graph = graph_create(1, 1, string_compare, string_hash);
}

void tearDown(void) {
    graph_free(graph);
}

void test_graph_create(void) {
    TEST_ASSERT_NOT_NULL(graph);
    TEST_ASSERT_EQUAL(1, graph_is_directed(graph));
    TEST_ASSERT_EQUAL(1, graph_is_labelled(graph));
    TEST_ASSERT_EQUAL(0, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL(0, graph_num_edges(graph));
}

void test_graph_add_node(void) {
    TEST_ASSERT_EQUAL(1, graph_add_node(graph, "A"));
    TEST_ASSERT_EQUAL(1, graph_contains_node(graph, "A"));
    TEST_ASSERT_EQUAL(1, graph_num_nodes(graph));
}

void test_graph_add_edge(void) {
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    TEST_ASSERT_EQUAL(1, graph_add_edge(graph, "A", "B", "label1"));
    TEST_ASSERT_EQUAL(1, graph_contains_edge(graph, "A", "B"));
    TEST_ASSERT_EQUAL(1, graph_num_edges(graph));
    TEST_ASSERT_EQUAL_STRING("label1", (char*)graph_get_label(graph, "A", "B"));
}

void test_graph_add_duplicate_node(void) {
    TEST_ASSERT_EQUAL(1, graph_add_node(graph, "A"));
    TEST_ASSERT_EQUAL(0, graph_add_node(graph, "A"));
    TEST_ASSERT_EQUAL(1, graph_num_nodes(graph));
}

void test_graph_add_duplicate_edge(void) {
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    TEST_ASSERT_EQUAL(1, graph_add_edge(graph, "A", "B", "label1"));
    TEST_ASSERT_EQUAL(0, graph_add_edge(graph, "A", "B", "label2"));
    TEST_ASSERT_EQUAL_STRING("label1", (char*)graph_get_label(graph, "A", "B"));
    TEST_ASSERT_EQUAL(1, graph_num_edges(graph));
}

void test_graph_remove_node(void) {
    graph_add_node(graph, "A");
    TEST_ASSERT_EQUAL(1, graph_remove_node(graph, "A"));
    TEST_ASSERT_EQUAL(0, graph_contains_node(graph, "A"));
    TEST_ASSERT_EQUAL(0, graph_num_nodes(graph));
}

void test_graph_remove_edge(void) {
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    graph_add_edge(graph, "A", "B", "label1");
    TEST_ASSERT_EQUAL(1, graph_remove_edge(graph, "A", "B"));
    TEST_ASSERT_EQUAL(0, graph_contains_edge(graph, "A", "B"));
    TEST_ASSERT_EQUAL(0, graph_num_edges(graph));
}

void test_graph_get_nodes(void) {
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    void** nodes = graph_get_nodes(graph);
    TEST_ASSERT_EQUAL_STRING("A", (char*)nodes[0]);
    TEST_ASSERT_EQUAL_STRING("B", (char*)nodes[1]);
    free(nodes);
}

void test_graph_get_edges(void) {
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    graph_add_edge(graph, "A", "B", "label1");
    Edge** edges = graph_get_edges(graph);
    TEST_ASSERT_EQUAL_STRING("A", (char*)edges[0]->source);
    TEST_ASSERT_EQUAL_STRING("B", (char*)edges[0]->dest);
    TEST_ASSERT_EQUAL_STRING("label1", (char*)edges[0]->label);
    free(edges[0]);
    free(edges);
}

void test_undirected_graph(void) {
    graph_free(graph);
    graph = graph_create(1, 0, string_compare, string_hash);
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    TEST_ASSERT_EQUAL(1, graph_add_edge(graph, "A", "B", "label1"));
    TEST_ASSERT_EQUAL(1, graph_contains_edge(graph, "B", "A"));
    TEST_ASSERT_EQUAL_STRING("label1", (char*)graph_get_label(graph, "B", "A"));
}

void test_unlabelled_graph(void) {
    graph_free(graph);
    graph = graph_create(0, 1, string_compare, string_hash);
    graph_add_node(graph, "A");
    graph_add_node(graph, "B");
    TEST_ASSERT_EQUAL(1, graph_add_edge(graph, "A", "B", NULL));
    TEST_ASSERT_EQUAL(NULL, graph_get_label(graph, "A", "B"));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_graph_create);
    RUN_TEST(test_graph_add_node);
    RUN_TEST(test_graph_add_edge);
    RUN_TEST(test_graph_add_duplicate_node);
    RUN_TEST(test_graph_add_duplicate_edge);
    RUN_TEST(test_graph_remove_node);
    RUN_TEST(test_graph_remove_edge);
    RUN_TEST(test_graph_get_nodes);
    RUN_TEST(test_graph_get_edges);
    RUN_TEST(test_undirected_graph);
    RUN_TEST(test_unlabelled_graph);

    return UNITY_END();
}
