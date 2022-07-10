//
// Created by Adam Hedges on 7/6/22.
//

#include "context.h"

int test_tree_size() {
	TreeSet* tree = get_treeset_in_order();
	if (tree->size != LIST_SIZE) {
		printf("Incorrect tree size: %zu", tree->size);
		return 1;
	}
	return 0;
}

int test_tree_min_max() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();
	int minkey = *(int*)TreeSet_min(tree)->key;
	int maxkey = *(int*)TreeSet_max(tree)->key;

	if (minkey != 0 || maxkey != 9) {
		printf("Incorrect min/max: %d/%d", minkey, maxkey);
		results += 1;
	}

	if (TreeSet_next(tree, TreeSet_max(tree)) != NULL) {
		printf("Next node detected after max\n");
		results += 1;
	}

	if (TreeSet_prev(tree, TreeSet_min(tree)) != NULL) {
		printf("Previous node detected after min\n");
		results += 1;
	}

	return results;
}

int test_tree_next_prev_nodes() {
	int results = 0;

	TreeSet* tree = get_treeset_in_order();
	KeyNode* node = TreeSet_min(tree);
	KeyNode* next = TreeSet_next(tree, node);
	int nodekey, nextkey, prevkey;

	if (next == NULL) {
		printf("Initial next node is null\n");
		results += 1;
	}

	while (next != NULL) {
		nodekey = *(int*)node->key;
		nextkey = *(int*)next->key;
		if (nextkey != nodekey + 1) {
			printf("Unexpected next key %d\n", nextkey);
			results += 1;
		}
		node = next;
		next = TreeSet_next(tree, next);
	}

	node = TreeSet_max(tree);
	KeyNode* prev = TreeSet_prev(tree, node);

	if (prev == NULL) {
		printf("Initial previous node is null\n");
		results += 1;
	}

	while (prev != NULL) {
		nodekey = *(int*)node->key;
		prevkey = *(int*)prev->key;
		if (prevkey != nodekey - 1) {
			printf("Unexpected previous key %d\n", prevkey);
			results += 1;
		}
		node = prev;
		prev = TreeSet_prev(tree, prev);
	}

	return results;
}

int test_tree_in_order_traversal() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();
	int preOrderKeys[] = { 3, 1, 0, 2, 7, 5, 4, 6, 8, 9 };
	int postOrderKeys[] = { 0, 2, 1, 4, 6, 5, 9, 8, 7, 3 };
	int bfsKeys[] = { 3, 1, 7, 0, 2, 5, 8, 4, 6, 9 };
	traversal_test_helper(&results, tree, preOrderKeys, postOrderKeys, bfsKeys);
	return results;
}

int test_tree_reversed_traversal() {
	int results = 0;
	TreeSet* tree = get_treeset_reversed();
	int preOrderKeys[] = { 6, 2, 1, 0, 4, 3, 5, 8, 7, 9 };
	int postOrderKeys[] = { 0, 1, 3, 5, 4, 2, 7, 9, 8, 6 };
	int bfsKeys[] = { 6, 2, 8, 1, 4, 7, 9, 0, 3, 5 };
	traversal_test_helper(&results, tree, preOrderKeys, postOrderKeys, bfsKeys);
	return results;
}

int test_tree_scrambled_traversal() {
	int results = 0;
	TreeSet* tree = get_treeset_scrambled();
	int preOrderKeys[] = { 4, 1, 0, 2, 3, 6, 5, 8, 7, 9 };
	int postOrderKeys[] = { 0, 3, 2, 1, 5, 7, 9, 8, 6, 4 };
	int bfsKeys[] = { 4, 1, 6, 0, 2, 5, 8, 3, 7, 9 };
	traversal_test_helper(&results, tree, preOrderKeys, postOrderKeys, bfsKeys);
	return results;
}

int test_tree_delete_inner_node() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();

	int key = 5;
	TreeSet_delete(tree, TreeSet_find(tree, &key));
	if (tree->size != 9) {
		printf("Unexpected tree size after delete: %zu\n", tree->size);
		results += 1;
	}

	KeyNode* node = TreeSet_find(tree, &key);
	if (node != NULL) {
		printf("Node found after delete\n");
		results += 1;
	}

	return results;
}

int test_tree_delete_minmax_nodes() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();

	TreeSet_delete(tree, TreeSet_min(tree));
	TreeSet_delete(tree, TreeSet_max(tree));

	KeyNode* minnode = TreeSet_min(tree);
	KeyNode* maxnode = TreeSet_max(tree);

	if (*(int*)minnode->key != 1) {
		printf("Unexpected minimum node after delete: %d\n", *(int*)minnode->key);
		results += 1;
	}

	if (*(int*)maxnode->key != 8) {
		printf("Unexpected maximum node after delete: %d\n", *(int*)maxnode->key);
		results += 1;
	}

	return results;
}

int test_tree_delete_root_node() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();
	TreeSet_delete(tree, tree->root);
	if (*(int*)tree->root->key != 4) {
		printf("Unexpected root node after delete: %d\n", *(int*)tree->root->key);
		results += 1;
	}
	return results;
}

int test_tree_delete_all_nodes() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();

	for (int i = 0; i < LIST_SIZE; i++) {
		KeyNode* node = TreeSet_find(tree, (void*)&TEST_KEYS[i]);
		TreeSet_delete(tree, node);
	}

	if (tree->size != 0) {
		printf("Tree is not empty after deleting all nodes\n");
		results += 1;
	}

	if (tree->root != NULL) {
		printf("Tree root is not NULL after deleting all nodes\n");
		results += 1;
	}

	return results;
}
