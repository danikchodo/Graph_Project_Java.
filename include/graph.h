#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
typedef struct{
    double x;
    double y;
    double dx;
    double dy;
} Vertex;

typedef struct{
    char name[50];
    int from;
    int to;
    double weight;
}Edge;

typedef struct{
    int num_vertices;
    int num_edges;
    Vertex *vertices;
    Edge *edges;
} Graph;

Graph* create_graph(int num_vertices, int num_edges);
void destroy_graph(Graph **graph);
bool is_graph_valid(const Graph *graph);

#endif