#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Graph* create_graph(int num_vertices, int num_edges) {
    
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Błąd [4]: Brak pamięci operacyjnej do przetworzenia grafu.\n");
        return NULL;
    }

    graph->num_vertices = num_vertices;
    graph->num_edges = num_edges;
    graph->vertices = NULL;
    graph->edges =NULL;

    if (num_vertices > 0) {
        graph->vertices = (Vertex*)malloc(num_vertices * sizeof(Vertex));
        if (graph->vertices == NULL) { 
            fprintf(stderr, "Błąd [4]: Brak pamięci operacyjnej do przetworzenia grafu.\n");
            free(graph);
            return NULL;
        }
    }

    if (num_edges > 0) {
        graph->edges = (Edge*)malloc(num_edges * sizeof(Edge));
        if (graph->edges == NULL) {
            fprintf(stderr, "Błąd [4]: Brak pamięci operacyjnej do przetworzenia grafu.\n");
            free(graph->vertices);
            graph->vertices = NULL;
            free(graph);
            return NULL;
        }
    }

    return graph;
}


void destroy_graph(Graph **graph) {
    if (graph == NULL || *graph == NULL) {
        return;
    }

    if ((*graph)->vertices != NULL) {
        free((*graph)->vertices);
        (*graph)->vertices = NULL; 
    }

    if ((*graph)->edges != NULL) {
        free((*graph)->edges);
        (*graph)->edges = NULL;
    }

    free(*graph);
    *graph = NULL; 
}

bool is_graph_valid(const Graph *graph) {
    if (graph == NULL) {
        fprintf(stderr, "Błąd [5]: Wskaźnik na graf jest pusty (NULL).\n");
        return false;
    }

    if (graph->num_vertices <= 0) {
        fprintf(stderr, "Błąd [5]: Graf musi mieć co najmniej 1 wierzchołek.\n");
        return false;
    }

    if (graph->num_edges < 0) {
        fprintf(stderr, "Błąd [5]: Liczba krawędzi nie może być ujemna.\n");
        return false;
    }

    for (int i = 0; i < graph->num_edges; i++) {
        int from = graph->edges[i].from;
        int to = graph->edges[i].to;

        if (from < 0 || from >= graph->num_vertices || to < 0 || to >= graph->num_vertices) {
            fprintf(stderr, "Błąd [5]: Krawędź %d łączy nieistniejące wierzchołki (%d i %d).\n", i, from, to);
            return false;
        }
    }

    return true;
}