//
// Created by Adam Hedges on 7/6/22.
//

#include <stdbool.h>
#include "base.h"

TreeSet* TreeSet_init(int (*key_comparer)(const void* a, const void* b)) {
	TreeSet* tree = malloc(sizeof(TreeSet));
	tree->size = 0;
	tree->compare = key_comparer;
	tree->root = NULL;
	return tree;
}

KeyNode* KeyNode_init(void* key) {
	KeyNode* node = malloc(sizeof(KeyNode));
	node->l = NULL;
	node->r = NULL;
	node->p = NULL;
	node->height = 1;
	node->key = key;
	return node;
}

void TreeSet_insert(TreeSet* tree, KeyNode* node) {
	tree->root = insert_node(tree, tree->root, node);
	tree->root->p = NULL;
}

void TreeSet_delete(TreeSet* tree, KeyNode* node) {
	delete_node(tree, node);
}

KeyNode* TreeSet_find(TreeSet* tree, void* key) {
	return find_node(tree, key);
}

void** TreeSet_get_keys(TreeSet* tree, TreeWalkOrder order) {
	void** keys = malloc(sizeof(void*) * tree->size);
	size_t count = 0;
	walk_keys(tree, tree->root, order, keys, &count);
	return keys;
}

bool TreeSet_contains(TreeSet* tree, void* key) {
	return TreeSet_find(tree, key) != NULL;
}

KeyNode* TreeSet_min(TreeSet* tree) {
	if (tree->root == NULL) return NULL;
	return get_subtree_min(tree->root);
}

KeyNode* TreeSet_max(TreeSet* tree) {
	if (tree->root == NULL) return NULL;
	return get_subtree_max(tree->root);
}

KeyNode* TreeSet_next(TreeSet* tree, KeyNode* node) {
	return next(tree, node);
}

KeyNode* TreeSet_prev(TreeSet* tree, KeyNode* node) {
	return prev(tree, node);
}
