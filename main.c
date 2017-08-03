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

static int node_find_min_val(struct node *node)
{
	if (!node->left) {
		return node->val;
	} else {
		return node_find_min_val(node->left);
	}
}

static struct node *node_remove(struct node *node, int val)
{
	if (node->val != val) {
		if (val < node->val && node->left) {
			node->left = node_remove(node->left, val);
		}
		if (val > node->val && node->right) {
			node->right = node_remove(node->right, val);
		}
		return node;
	} else {
		if (node->left && node->right) {
			node->val = node_find_min_val(node->right);
			node->right = node_remove(node->right, node->val);
			return node;
		} else if (node->left) {
			struct node *left = node->left;
			node->left = NULL;
			node_destroy(node);
			return left;
		} else if (node->right) {
			struct node *right = node->right;
			node->right = NULL;
			node_destroy(node);
			return right;
		} else {
			node_destroy(node);
			return NULL;
		}
	}
}

static void three_remove(struct three *three, int val)
{
	if (three->root) {
		three->root = node_remove(three->root, val);
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
	three_insert(three, 61);
	three_insert(three, 50);
	three_insert(three, 63);
	three_insert(three, 5);
	three_insert(three, 777);
	three_insert(three, 43);
	three_insert(three, 0);
	three_print(three);

	printf("remove(42):\n");
	three_remove(three, 42);
	three_print(three);

	printf("remove(61):\n");
	three_remove(three, 61);
	three_print(three);

	three_destroy(three);
	return 0;
}
