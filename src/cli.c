#include "../include/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <getopt.h>

void print_help() {
    printf("Użycie: grafy -i <plik_we> [-o <plik_wy>] [-a <algorytm>] [-b] [-v] [-h]\n");
    printf("Opcje:\n");
    printf("  -i <ścieżka>  Ścieżka do pliku wejściowego (wymagany)\n");
    printf("  -o <ścieżka>  Ścieżka do pliku wyjściowego (domyślnie: stdout)\n");
    printf("  -a <nazwa>    Wybór algorytmu: fr (Fruchterman), tutte (Tutte). Domyślnie: fr\n");
    printf("  -b            Zapis pliku wyjściowego w formacie binarnym\n");
    printf("  -v            Tryb gadatliwy (verbose)\n");
    printf("  -h            Wyświetla tę pomoc\n");
}

int parse_arguments(int argc, char *argv[], AppConfig *config) {
    config->input_file = NULL;
    config->output_file = NULL;
    config->algorithm = "fr"; 
    config->binary_output = false;
    config->verbose = false;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:a:bvh")) != -1) {
        switch (opt) {
            case 'i': config->input_file = optarg; break;
            case 'o': config->output_file = optarg; break;
            case 'a': config->algorithm = optarg; break;
            case 'b': config->binary_output = true; break;
            case 'v': config->verbose = true; break;
            case 'h': 
                print_help(); 
                exit(0); 
            case '?': 
                return -1; 
            default: 
                return -1;
        }
    }

    if (config->input_file == NULL) {
        return -1; 
    }

    return 0;
}