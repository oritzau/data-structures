struct BTNode {
	struct BTNode *left;
	struct BTNode *right;
	int value;
};

struct BTNode *btn_new(int value);
void bt_insert(struct BTNode **root, int value);
void bt_print(struct BTNode *root);
void bt_free(struct BTNode **root);
void bt_delete(struct BTNode **root, int target);
struct BTNode *bt_search(struct BTNode **root, int target);
