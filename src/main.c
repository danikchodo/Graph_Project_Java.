#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/cli.h"
#include "../include/graph.h"
#include "../include/algorithms.h"
#include "../include/io.h" 

void check_planarity_and_exit(Graph *g) {
    if (g != NULL && g->num_vertices > 2) {
        int max_edges_general = 3 * g->num_vertices - 6;
    
        if (g->num_edges > max_edges_general) {
            fprintf(stderr, "\nGraf jest nieplanarny.\n");        
            destroy_graph(&g);
            exit(1); 
        }

        int max_edges_bipartite = 2 * g->num_vertices - 4;
        if (g->num_edges > max_edges_bipartite) {
             fprintf(stderr, "\nGraf jest nieplanarny.\n");
             destroy_graph(&g);
             exit(1); 
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    AppConfig config;

    if (parse_arguments(argc, argv, &config) != 0) {
        // błąd [3] z dokumentacji
        return 3;
    }

    if (config.verbose) {
        printf("--- LOG: Start programu ---\n");
        printf("Wczytywanie: %s\n", config.input_file);
    }

    Graph *g = load_graph_from_text(config.input_file);
      
    
    if (g == NULL) {
        fprintf(stderr, "Błąd [1]: Nie udało się wczytać grafu z pliku %s\n", config.input_file);
        return 1;
    }

    check_planarity_and_exit(g);

    if (config.verbose) {
        printf("Wczytano graf: %d wierzchołków, %d krawędzi.\n", g->num_vertices, g->num_edges);
    }

    if (strcmp(config.algorithm, "fr") == 0 || strcmp(config.algorithm, "fruchterman") == 0) {
        run_fruchterman_reingold(g);
    } 
    else if (strcmp(config.algorithm, "tutte") == 0) {
        run_tutte(g);
    } 
    else {
        fprintf(stderr, "Błąd: Nieznany algorytm '%s'. Użyj 'fr' lub 'tutte'.\n", config.algorithm);
        destroy_graph(&g);
        return 1;
    }

    save_graph_results(g, config.output_file, config.binary_output);

    if (config.verbose) {
        printf("Wyniki zapisane do: %s\n", config.output_file ? config.output_file : "konsoli (stdout)");
    }

    destroy_graph(&g);

    if (config.verbose) {
        printf("--- LOG: Program zakończony poprawnie ---\n");
    }

    return 0;
}