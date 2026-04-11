
#include <stdio.h>
#include "../include/cli.h"

int main(int argc, char *argv[]) {
    AppConfig config;

    if (parse_arguments(argc, argv, &config) != 0) {
        fprintf(stderr, "Błąd [3]: Nieprawidłowe argumenty wywołania. Użyj flagi -h, aby wyświetlić pomoc.\n");
        return 3;
    }

    if (config.verbose) {
        printf("--- TRYB GADATLIWY (VERBOSE) WLACZONY ---\n");
        printf("Plik wejściowy: %s\n", config.input_file);
        printf("Plik wyjściowy: %s\n", config.output_file ? config.output_file : "stdout");
        printf("Wybrany algorytm: %s\n", config.algorithm);
        printf("Zapis binarny: %s\n", config.binary_output ? "TAK" : "NIE");
        printf("-----------------------------------------\n");
    }

    return 0;
}