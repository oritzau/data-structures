#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph *graph_new(int num_vertices)
{
	Graph *g = malloc(sizeof(Graph));
	int *G = calloc(num_vertices * num_vertices, sizeof(int));
	g->G = G;
	g->num_vertices = num_vertices;
	return g;
}

void graph_free(Graph *g)
{
	free(g->G);
	free(g);
}

void graph_print(Graph *g)
{
	puts("Graph\n{");
	for (int i = 0; i < g->num_vertices; i++)
		for (int j = 0; j < g->num_vertices; j++)
			printf("%d%c", *(g->G + (i * g->num_vertices + j)), (j + 1) % g->num_vertices == 0 ? '\n' : ' ');
	puts("}");
}

void add_directed_edge(Graph *g, int from, int to, int weight)
{
	g->G[from * g->num_vertices + to] = weight;
}

void add_undirected_edge(Graph *g, int from, int to, int weight)
{
	add_directed_edge(g, from, to, weight);
	add_directed_edge(g, to, from, weight);
}

int get_weight(Graph *g, int from, int to)
{
	return g->G[from * g->num_vertices + to];
}
