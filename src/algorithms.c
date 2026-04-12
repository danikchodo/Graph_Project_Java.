#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/algorithms.h"
#include "../include/graph.h"


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