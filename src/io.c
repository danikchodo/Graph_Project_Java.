#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/io.h"
#include "../include/graph.h"

Graph* load_graph_from_text(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Błąd [1]: Nie można otworzyć pliku %s\n", filename);
        return NULL;
    }

    char line[256];
    char edge_name[50];
    int u, v;
    double weight;
    int max_id = -1;
    int min_id = 2147483647; // Max int
    int edge_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49s %d %d %lf", edge_name, &u, &v, &weight) == 4) {
            if (u > max_id) max_id = u;
            if (v > max_id) max_id = v;
            if (u < min_id) min_id = u;
            if (v < min_id) min_id = v;
            edge_count++;
        }
    }

    if (edge_count == 0) {
        fclose(file);
        return NULL;
    }

    int num_vertices = max_id - min_id + 1;

    Graph *g = create_graph(num_vertices, edge_count);
    if (!g) {
        fclose(file);
        return NULL;
    }

    rewind(file);
    int current_edge = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49s %d %d %lf", edge_name, &u, &v, &weight) == 4) {
            // Przesuwamy ID tak, aby zawsze zaczynały się od 0 w tablicy
            g->edges[current_edge].from = u - min_id; 
            g->edges[current_edge].to = v - min_id;
            g->edges[current_edge].weight = weight;
            current_edge++;
        }
    }

    fclose(file);
    return g;
}

void save_graph_results(Graph *g, const char *filename, bool binary) {
    FILE *file = filename ? fopen(filename, "w") : stdout;
    if (!file) return;

    for (int i = 0; i < g->num_vertices; i++) {
        fprintf(file, "%d %.1f %.1f\n", i + 1, g->vertices[i].x, g->vertices[i].y);
    }

    if (filename) fclose(file);
}