#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef struct {
    char *input_file;
    char *output_file;
    char *algorithm;
    bool binary_output;
    bool verbose;
} AppConfig;

int parse_arguments(int argc, char *argv[], AppConfig *config);
void print_help();

#endif