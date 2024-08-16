#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int main(void) 
{
	struct BTNode *root = 0;
	bt_insert(&root, 5);
	bt_insert(&root, 3);
	bt_insert(&root, 2);
	bt_insert(&root, 9);
	bt_insert(&root, 8);
	bt_insert(&root, 0);
	bt_print(root);
	puts("");
	puts("Deleting 5");
	bt_delete(&root, 5);
	puts("Finished deletion");
	bt_print(root);
	puts("");
	bt_free(&root);
}

struct BTNode *btn_new(int value) 
{
	struct BTNode *bt = (struct BTNode *)malloc(sizeof(struct BTNode));
	bt->value = value;
	bt->left = bt->right = 0;
	return bt;
}

void bt_print(struct BTNode *root) 
{
	if (!root)
		return;

	printf("[%d]", root->value);
	printf(" Left: ");
	bt_print(root->left);
	printf(" Right: ");
	bt_print(root->right);
}

void bt_insert(struct BTNode **root, int value) 
{
	if (!root) return;

	struct BTNode *curr = *root;
	if (!curr) 
	{
		struct BTNode *insert = btn_new(value);
		*root = insert;
		return;
	}
	struct BTNode **next = value < curr->value ? &(*root)->left : &(*root)->right;
	bt_insert(next, value);
}

void bt_free(struct BTNode **root)
{
	if (!root || !*root) return;
	struct BTNode *tmp = *root;
	bt_free(&tmp->left);
	bt_free(&tmp->right);
	free(tmp);
}

void bt_delete(struct BTNode **root, int target) 
{
	if (!root || !*root) return;
	struct BTNode *curr, *prev, *tmp;
	int is_left;

	curr = *root;
	prev = 0;
	while (1)
	{
		if (DEBUG)
		{
			printf("curr: %d\n", curr->value);
			if (prev)
				printf("prev: %d\n", prev->value);
		}

		if (curr->value == target)
		{
			if (!curr->left && !curr->right)
			{
				if (!prev) 
				{
					free(curr);
					return;
				}

				if (is_left)
					prev->left = 0;
				else
					prev->right = 0;
				free(curr);
				return;
			}
			if (!curr->right)
			{
				if (!prev)
				{
					*root = prev;
					free(curr);
					return;
				}
				if (is_left)
					prev->left = curr->left;
				else
					prev->right = curr->left;
				free(curr);
				return;
			}
			// The delete target has a right subtree, so we need the leftmost node of the right subtree
			tmp = curr;
			curr = curr->right;
			while (curr->left)
			{
				prev = curr;
				curr = curr->left;
			}
			tmp->value = curr->value;
			if (prev) // Right subtree had a left subtree
				prev->left = 0;
			else // Right subtree was a leaf
				tmp->right = 0;
			free(curr);
			return;
		}
		prev = curr;
		is_left = target < curr->value;
		curr = target < curr->value ? curr->left : curr->right;
	}
}

struct BTNode *bt_search(struct BTNode **root, int target) 
{
	if (!root || !*root) return 0;

	struct BTNode *curr = *root;
	if (curr->value == target) 
		return *root;
	if (curr->value < target)
		return bt_search(&(*root)->right, target);
	return bt_search(&(*root)->left, target);
}
