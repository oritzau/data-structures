typedef struct Graph
{
	int *G;
	int num_vertices;
} Graph;

Graph *graph_new(int num_vertices);
void graph_free(Graph *g);
void graph_print(Graph *g);
void add_directed_edge(Graph *g, int from, int to, int weight);
void add_undirected_edge(Graph *g, int from, int to, int weight);
int get_weight(Graph *g, int from, int to);

void dfs(Graph *g, int target);
void bfs(Graph *g, int target);
