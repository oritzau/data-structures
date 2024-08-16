#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>

struct PQNode *pqnode_new(int e, int p)
{
	struct PQNode *pq = malloc(sizeof(*pq));
	if (!pq)
		exit(1);
	pq->e = e;
	pq->p= p;
	pq->next = 0;
	return pq;
}

void pqueue_free(struct PQNode **head)
{
	if (is_empty(head)) return;
	pqueue_free(&(*head)->next);
	free(*head);
	*head = 0;
}

void pqnode_print(struct PQNode *pq)
{
	printf("PQNode {\n\te: %d,\n\tp: %d\n}\n", pq->e, pq->p);
}

void pqueue_print(struct PQNode **head)
{
	if (is_empty(head)) return;
	struct PQNode *tmp = *head;
	while (tmp)
	{
		pqnode_print(tmp);
		tmp = tmp->next;
	}
}

int is_empty(struct PQNode **head)
{
	return (!head || !*head);
}

void insert_with_priority(struct PQNode **head, int e, int p)
{
	struct PQNode *pq, *tmp;
	pq = pqnode_new(e, p);
	if (is_empty(head))
	{
		*head = pq;
		return;
	}
	tmp = *head;
	if (p < tmp->p)
	{
		pq->next = tmp;
		*head = pq;
		return;
	}
	while (tmp->next && tmp->next->p < p)
		tmp = tmp->next;
	pq->next = tmp->next;
	tmp->next = pq;
}

int dequeue(struct PQNode **head)
{
	if (is_empty(head)) return 0;
	struct PQNode *highest = *head;
	*head = highest->next;
	int r = highest->e;
	free(highest);
	return r;
}

int peek(struct PQNode **head)
{
	if (is_empty(head)) return 0;
	return (*head)->e;
}
