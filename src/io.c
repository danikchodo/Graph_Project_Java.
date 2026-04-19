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
    int min_id = 2147483647; 
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
    if (!filename) {
        for (int i = 0; i < g->num_vertices; i++) {
            printf("%d %.4f %.4f\n", i + 1, g->vertices[i].x, g->vertices[i].y);
        }
        return;
    }

    if (binary) {
        FILE *file = fopen(filename, "wb");
        if (!file) return;

        fwrite(&g->num_vertices, sizeof(int), 1, file);
        for (int i = 0; i < g->num_vertices; i++) {
            int id = i + 1;
            double x = g->vertices[i].x;
            double y = g->vertices[i].y;
            fwrite(&id, sizeof(int), 1, file);
            fwrite(&x, sizeof(double), 1, file);
            fwrite(&y, sizeof(double), 1, file);
        }
        fclose(file);
    } else {
        FILE *file = fopen(filename, "w");
        if (!file) return;

        for (int i = 0; i < g->num_vertices; i++) {
            fprintf(file, "%d %.4f %.4f\n", i + 1, g->vertices[i].x, g->vertices[i].y);
        }
        fclose(file);
    }
}