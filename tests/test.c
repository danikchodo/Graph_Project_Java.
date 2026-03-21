#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../include/graph.h"

void test_create_and_destroy() {
    printf("Test 1: Tworzenie i niszczenie grafu...\n");
    
    Graph *g = create_graph(5, 10);
    assert(g != NULL);
    assert(g->num_vertices == 5);
    assert(g->num_edges == 10);
    
    destroy_graph(&g);
    assert(g == NULL);
    
    printf("Test 1 zaliczony!\n\n");
}

void test_valid_graph_logic() {
    printf("Test 2: Walidacja poprawnego grafu...\n");
    
    Graph *g = create_graph(2, 1);
    g->edges[0].from = 0;
    g->edges[0].to = 1;
    g->edges[0].weight = 1.5;
    
    assert(is_graph_valid(g) == true);
    
    destroy_graph(&g);
    printf("Test 2 zaliczony!\n\n");
}

void test_invalid_graph_logic() {
    printf("Test 3: Walidacja błędnego grafu...\n");
    printf("(Spodziewamy sie komunikatu o Błędzie [5]):\n");
    
    Graph *g = create_graph(2, 1);
    g->edges[0].from = 0;
    g->edges[0].to = 99; 
    
    assert(is_graph_valid(g) == false); 
    
    destroy_graph(&g);
    printf("Test 3 zaliczony\n\n");
}

int main() {
    printf("Rozpoczynamy testy jednostkowe\n\n");
    
    test_create_and_destroy();
    test_valid_graph_logic();
    test_invalid_graph_logic();
    
    printf("Wszystkie testy zaliczone\n");
    return 0;
}