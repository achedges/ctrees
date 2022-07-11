//
// Created by Adam Hedges on 7/6/22.
//

#include "base.h"
#include <stdlib.h>

TreeMap* TreeMap_init(int (*comparer)(const void* a, const void* b)) {
	TreeMap* tree = malloc(sizeof(TreeMap));
	tree->size = 0;
	tree->compare = comparer;
	tree->root = NULL;
	return tree;
}

KeyValueNode* KeyValueNode_init(void* key, void* value) {
	KeyValueNode* node = malloc(sizeof(KeyValueNode));
	node->l = NULL;
	node->r = NULL;
	node->p = NULL;
	node->height = 1;
	node->key = key;
	node->value = value;
	return node;
}

void TreeMap_insert(TreeMap* tree, KeyValueNode* node) {
	tree->root = insert_node(tree, tree->root, node);
	tree->root->p = NULL;
}

void TreeMap_delete(TreeMap* tree, KeyValueNode* node) {
	delete_node(tree, node);
}

KeyValueNode* TreeMap_find(TreeMap* tree, void* key) {
	return find_node(tree, key);
}

void** TreeMap_get_keys(TreeMap* tree, TreeWalkOrder order) {
	void** keys = malloc(sizeof(void*) * tree->size);
	size_t count = 0;
	walk_keys(tree, tree->root, order, keys, &count);
	return keys;
}

bool TreeMap_contains(TreeMap* tree, void* key) {
	return TreeMap_find(tree, key) != NULL;
}

KeyValueNode* TreeMap_min(TreeMap* tree) {
	if (tree->root == NULL) return NULL;
	return get_subtree_min(tree->root);
}

KeyValueNode* TreeMap_max(TreeMap* tree) {
	if (tree->root == NULL) return NULL;
	return get_subtree_max(tree->root);
}

KeyValueNode* TreeMap_next(TreeMap* tree, KeyValueNode* node) {
	return next(tree, node);
}

KeyValueNode* TreeMap_prev(TreeMap* tree, KeyValueNode* node) {
	return prev(tree, node);
}
