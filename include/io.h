#ifndef IO_H
#define IO_H

#include "graph.h"
#include <stdbool.h>

Graph* load_graph_from_text(const char *filename);

void save_graph_results(Graph *g, const char *filename, bool binary);

#endif