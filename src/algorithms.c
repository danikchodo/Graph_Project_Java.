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
                    // TODO: wektor odpychający u od v i dodaj do dx/dy
                }
            }
        }

        for (int e = 0; e < g->num_edges; e++) {
            int v = g->edges[e].from;
            int u = g->edges[e].to;
            
            // TODO: wektor przyciągający 'v' i 'u' do siebie
            // TODO: dodaj siłę do v->dx/dy, a odjac od u->dx/dy
        }

        for (int v = 0; v < g->num_vertices; v++) {
            // TODO: przesuniecie o wektor
        }

        temp *= 0.95; 
    }
    
    printf("Algorytm zakonczony pomyslnie.\n");
}