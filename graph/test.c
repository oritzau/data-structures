#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pqueue.h"

// Return 1 on success, 0 on failure
typedef int (*testfn_t)(void);

int *dijkstras(Graph *g, int source)
{
	if (source >= g->num_vertices) return 0;

	struct PQNode *head = 0;
	int i, current;
	int *visited = calloc(g->num_vertices, sizeof(int));
	int *distance = malloc(g->num_vertices * sizeof(int));
	for (int i = 0; i < g->num_vertices; i++)
		distance[i] = INT_MAX;
	distance[source] = 0;

	insert_with_priority(&head, source, 0);
	while (!is_empty(&head))
	{
		int current = dequeue(&head);
		if (visited[current])
			continue;
		visited[current] = 1;
		for (i = 0; i < g->num_vertices; i++)
		{
			int weight;
			if ((weight = get_weight(g, current, i)))
			{
				int curr_distance = distance[current] + weight;
				if (curr_distance < distance[i])
					distance[i] = curr_distance;
				insert_with_priority(&head, i, distance[i]);
			}
		}
	}
	free(visited);
	return distance;
}

int main(void)
{
	testfn_t tests[] = {
	};

	for (int i = 0; i < (sizeof tests) / sizeof (testfn_t); i++)
	{
		if (!tests[i]())
		{
			printf("Failure on test #%d\n", i);
			return 1;
		}
	}

	int num_vertices = 4;
	int source = 3;
	Graph *g = graph_new(num_vertices);
	add_undirected_edge(g, 0, 1, 6);
	add_undirected_edge(g, 1, 2, 2);
	add_undirected_edge(g, 0, 2, 10);
	add_undirected_edge(g, 2, 3, 7);
	add_undirected_edge(g, 0, 3, 4);
	int *shortest_paths = dijkstras(g, source);
	for (int i = 0; i < num_vertices; i++)
		printf("%d->%d: %d\n", source, i, shortest_paths[i]);

	free(shortest_paths);
	graph_free(g);
	puts("All tests passing");
}
