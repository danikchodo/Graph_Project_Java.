#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../include/algorithms.h"
#include "../include/graph.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void init_random_positions(Graph *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        g->vertices[i].x = (double)(rand() % 800); 
        g->vertices[i].y = (double)(rand() % 800);
        g->vertices[i].dx = 0.0;
        g->vertices[i].dy = 0.0;
    }
}

void run_fruchterman_reingold(Graph *g) {
    if (g == NULL || g->num_vertices == 0) return;

    printf("Rozpoczynam algorytm Fruchtermana-Reingolda...\n");

    int max_iterations = 500;
    double area = 800.0 * 800.0;
    
    // k: optymalny dystans miedzy wierzcholkami
    double k = sqrt(area / g->num_vertices); 
    
    double temp = 800.0 / 10.0; 

    init_random_positions(g);

    for (int iter = 0; iter < max_iterations; iter++) {

        for (int v = 0; v < g->num_vertices; v++) {
            g->vertices[v].dx = 0.0;
            g->vertices[v].dy = 0.0;
            for (int u = 0; u < g->num_vertices; u++) {
                if (v != u) {
                    double delta_x = g->vertices[v].x - g->vertices[u].x;
                    double delta_y = g->vertices[v].y - g->vertices[u].y;

                    double distance = sqrt(delta_x * delta_x + delta_y * delta_y);
                    if (distance < 0.0001) distance = 0.0001;

                    double force = (k * k) / distance;

                    g->vertices[v].dx += (delta_x / distance) * force;
                    g->vertices[v].dy += (delta_y / distance) * force;

                }
            }
        }

        for (int e = 0; e < g->num_edges; e++) {
            int v = g->edges[e].from;
            int u = g->edges[e].to;

            double delta_x = g->vertices[v].x - g->vertices[u].x;
            double delta_y = g->vertices[v].y - g->vertices[u].y;

            double distance = sqrt(delta_x * delta_x + delta_y * delta_y);
            if (distance < 0.0001) distance = 0.0001;
            
            double force = (distance * distance) / k;
            
            double force_x = (delta_x / distance) * force;
            double force_y = (delta_y / distance) * force;
            
            g->vertices[v].dx -= force_x;
            g->vertices[v].dy -= force_y;
            g->vertices[u].dx += force_x;
            g->vertices[u].dy += force_y;
            
        }

        for (int v = 0; v < g->num_vertices; v++) {
            double dx = g->vertices[v].dx;
            double dy = g->vertices[v].dy;
            double displacement = sqrt(dx * dx + dy * dy);

            if (displacement > 0.0001) {
                double limited_dist = (displacement < temp) ? displacement : temp;

                g->vertices[v].x += (dx / displacement) * limited_dist;
                g->vertices[v].y += (dy / displacement) * limited_dist;
            }

            double margin = 20.0;
            double max_w = 800.0 - margin;

            if (g->vertices[v].x < margin) g->vertices[v].x = margin;
            if (g->vertices[v].x > max_w)  g->vertices[v].x = max_w;
            if (g->vertices[v].y < margin) g->vertices[v].y = margin;
            if (g->vertices[v].y > max_w)  g->vertices[v].y = max_w;
        }

        temp *= 0.95; 
    }
    
    printf("Algorytm zakonczony pomyslnie.\n");
}

//szukanie cyklu 
static bool dfs_find_cycle(Graph *g, int u, int p, int *visited, int *parent, int *c_start, int *c_end) {
    visited[u] = 1;
    for (int i = 0; i < g->num_edges; i++) {
        int v = -1;
        if (g->edges[i].from == u) v = g->edges[i].to;
        else if (g->edges[i].to == u) v = g->edges[i].from;

        if (v != -1 && v != p) {
            if (visited[v] == 1) { 
                *c_start = v;
                *c_end = u;
                return true;
            }
            if (visited[v] == 0) {
                parent[v] = u;
                if (dfs_find_cycle(g, v, u, visited, parent, c_start, c_end)) {
                    return true;
                }
            }
        }
    }
    visited[u] = 2; 
    return false;
}

void run_tutte(Graph *g) {
    if (g == NULL || g->num_vertices < 3) return;
    printf("Rozpoczynam pelny algorytm Tutte'a (z dynamicznym wykrywaniem brzegow)...\n");

    int *visited = calloc(g->num_vertices, sizeof(int));
    int *parent = malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) parent[i] = -1;

    int c_start = -1, c_end = -1;
    bool has_cycle = false;

    for (int i = 0; i < g->num_vertices; i++) {
        if (visited[i] == 0) {
            if (dfs_find_cycle(g, i, -1, visited, parent, &c_start, &c_end)) {
                has_cycle = true;
                break;
            }
        }
    }

    int *boundary = malloc(g->num_vertices * sizeof(int));
    int b_count = 0;
    bool *is_boundary = calloc(g->num_vertices, sizeof(bool));

    if (has_cycle) {
        int curr = c_end;
        while (curr != c_start && curr != -1) {
            boundary[b_count++] = curr;
            is_boundary[curr] = true;
            curr = parent[curr];
        }
        boundary[b_count++] = c_start;
        is_boundary[c_start] = true;
    } else {
        b_count = (g->num_vertices >= 3) ? 3 : g->num_vertices;
        for(int i = 0; i < b_count; i++) {
            boundary[i] = i;
            is_boundary[i] = true;
        }
    }

    double radius = 350.0;
    double center_x = 400.0, center_y = 400.0;

    for (int i = 0; i < b_count; i++) {
        int v = boundary[i];
        double angle = 2.0 * M_PI * i / b_count;
        g->vertices[v].x = center_x + radius * cos(angle);
        g->vertices[v].y = center_y + radius * sin(angle);
    }

    for (int i = 0; i < g->num_vertices; i++) {
        if (!is_boundary[i]) {
            g->vertices[i].x = center_x;
            g->vertices[i].y = center_y;
        }
    }

    double *new_x = malloc(g->num_vertices * sizeof(double));
    double *new_y = malloc(g->num_vertices * sizeof(double));
    int max_iterations = 1000;

    for (int iter = 0; iter < max_iterations; iter++) {
        for (int i = 0; i < g->num_vertices; i++) {
            if (is_boundary[i]) continue; 

            double sum_x = 0.0, sum_y = 0.0;
            int degree = 0;

            for (int j = 0; j < g->num_edges; j++) {
                int neighbor = -1;
                if (g->edges[j].from == i) neighbor = g->edges[j].to;
                else if (g->edges[j].to == i) neighbor = g->edges[j].from;

                if (neighbor != -1) {
                    sum_x += g->vertices[neighbor].x;
                    sum_y += g->vertices[neighbor].y;
                    degree++;
                }
            }

            if (degree > 0) {
                new_x[i] = sum_x / degree;
                new_y[i] = sum_y / degree;
            } else {
                new_x[i] = g->vertices[i].x;
                new_y[i] = g->vertices[i].y;
            }
        }

        for (int i = 0; i < g->num_vertices; i++) {
            if (!is_boundary[i]) {
                g->vertices[i].x = new_x[i];
                g->vertices[i].y = new_y[i];
            }
        }
    }

    free(visited); free(parent); free(boundary); free(is_boundary);
    free(new_x); free(new_y);
    printf("Algorytm zakonczony pomyslnie.\n");
}