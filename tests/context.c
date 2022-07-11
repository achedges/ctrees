//
// Created by Adam Hedges on 7/6/22.
//

#include <stdio.h>
#include "context.h"

const int LIST_SIZE = 10;
const int TEST_KEYS[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int MAP_KEYS[] = { 1, 2, 3, 4 };
const char* MAP_VALUES[] = { "A", "B", "C", "D" };

TreeSet* get_treeset_in_order() {
	TreeSet* tree = TreeSet_init(&int_comparer);
	for (int i = 0; i < LIST_SIZE; i++) {
		KeyNode* node = KeyNode_init((void*)&TEST_KEYS[i]);
		TreeSet_insert(tree, node);
	}
	return tree;
}

TreeSet* get_treeset_reversed() {
	TreeSet* tree = TreeSet_init(&int_comparer);
	for (int i = LIST_SIZE - 1; i >= 0; i--) {
		KeyNode* node = KeyNode_init((void*)&TEST_KEYS[i]);
		TreeSet_insert(tree, node);
	}
	return tree;
}

TreeSet* get_treeset_scrambled() {
	TreeSet* tree = TreeSet_init(&int_comparer);
	int insertionorder[] = { 0, 2, 1, 6, 4, 5, 3, 9, 7, 8 };
	for (int i = 0; i < LIST_SIZE; i++) {
		KeyNode* node = KeyNode_init((void*)&TEST_KEYS[insertionorder[i]]);
		TreeSet_insert(tree, node);
	}
	return tree;
}

void traversal_test_helper(int* results, TreeSet* tree, const int preOrderKeys[], const int postOrderKeys[], const int bfsKeys[]) {
	void** treekeys;
	treekeys = TreeSet_get_keys(tree, InOrder);
	for (int i = 0; i < tree->size; i++) {
		int key = *(int*)treekeys[i];
		if (key != TEST_KEYS[i]) {
			printf("Incorrect in-order key traversal: %d\n", key);
			(*results) += 1;
		}
	}

	treekeys = TreeSet_get_keys(tree, PreOrder);
	for (int i = 0; i < tree->size; i++) {
		int key = *(int*)treekeys[i];
		if (key != preOrderKeys[i]) {
			printf("Incorrect pre-order key traversal: %d\n", key);
			(*results) += 1;
		}
	}

	treekeys = TreeSet_get_keys(tree, PostOrder);
	for (int i = 0; i < tree->size; i++) {
		int key = *(int*)treekeys[i];
		if (key != postOrderKeys[i]) {
			printf("Incorrect post-order key traversal: %d\n", key);
			(*results) += 1;
		}
	}

	treekeys = TreeSet_get_keys(tree, BreadthFirst);
	for (int i = 0; i < tree->size; i++) {
		int key = *(int*)treekeys[i];
		if (key != bfsKeys[i]) {
			printf("Incorrect breadth-first key traversal: %d\n", key);
			(*results) += 1;
		}
	}
}
