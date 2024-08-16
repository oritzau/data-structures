// Min-priority queue
struct PQNode
{
	int e;
	int p;
	struct PQNode *next;
};

typedef void (printfn(void *));
typedef void (freefn(void *));

struct PQNode *pqnode_new(int e, int p);

void pqueue_free(struct PQNode **head);

void pqnode_print(struct PQNode *pq);
void pqueue_print(struct PQNode **head);

int is_empty(struct PQNode **head);
void insert_with_priority(struct PQNode **head, int e, int p);
int dequeue(struct PQNode **head);
int peek(struct PQNode **head);
