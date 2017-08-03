#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node *left;
	struct node *right;
	int val;
};

struct three {
	struct node *root;
};

static struct node *node_create(int val)
{
	struct node *node = calloc(1, sizeof(*node));
	node->val = val;
	return node;
}

static void node_destroy(struct node *node)
{
	if (node->left) {
		node_destroy(node->left);
	}
	if (node->right) {
		node_destroy(node->right);
	}
	free(node);
}

static void node_print(struct node *node, const char *lbl, int depth)
{
	printf("%*s: %d\n", depth, lbl, node->val);
	if (node->left) {
		node_print(node->left, "L", depth + 8);
	}
	if (node->right) {
		node_print(node->right, "R", depth + 8);
	}
}

static void node_insert(struct node *node, int val)
{
	if (val < node->val) {
		if (node->left) {
			node_insert(node->left, val);
		} else {
			node->left = node_create(val);
		}
	} else {
		if (node->right) {
			node_insert(node->right, val);
		} else {
			node->right = node_create(val);
		}
	}
}

static struct three *three_create(void)
{
	return calloc(1, sizeof(struct three));
}

static void three_destroy(struct three *three)
{
	if (three->root) {
		node_destroy(three->root);
	}
	free(three);
}

static void three_insert(struct three *three, int val)
{
	if (three->root) {
		node_insert(three->root, val);
	} else {
		three->root = node_create(val);
	}
}

static void three_print(struct three *three)
{
	if (three->root) {
		node_print(three->root, "/", 0);
	}
}

int main(void)
{
	struct three *three = three_create();
	three_insert(three, 42);
	three_insert(three, -100);
	three_insert(three, 50);
	three_insert(three, 0);
	three_print(three);
	three_destroy(three);
	return 0;
}
