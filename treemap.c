//
// Created by Adam Hedges on 7/6/22.
//

#include "base.h"
#include <stdlib.h>

TreeMap* TreeMap_init(int (*comparer)(const void* a, const void* b)) {
	TreeMap* tree = malloc(sizeof(TreeMap));
	tree->treeset = TreeSet_init(comparer);
	tree->root = NULL;
	return tree;
}

KeyValueNode* KeyValueNode_init(void* key, void* value) {
	KeyValueNode* node = malloc(sizeof(KeyValueNode));
	node->keynode = KeyNode_init(key);
	node->value = value;
	return node;
}

void TreeMap_insert(TreeMap* tree, KeyValueNode* node) {
	insert_node((TreeSet*)tree, (KeyNode*)tree->root, (KeyNode*)node);
	tree->root->keynode->p = NULL;
}

void TreeMap_delete(TreeMap* tree, KeyValueNode* node) {
	delete_node((TreeSet*)tree, (KeyNode*)node);
}

KeyValueNode* TreeMap_find(TreeMap* tree, void* key) {
	return (KeyValueNode*)find_node((TreeSet*)tree, key);
}

void** TreeMap_get_keys(TreeMap* tree, TreeWalkOrder order) {
	void** keys = malloc(sizeof(void*) * tree->treeset->size);
	size_t count = 0;
	walk_keys((TreeSet*)tree, (KeyNode*)tree->root, order, keys, &count);
	return keys;
}

bool TreeMap_contains(TreeMap* tree, void* key) {
	return TreeSet_find(tree->treeset, key) != NULL;
}

KeyValueNode* TreeMap_min(TreeMap* tree) {
	if (tree->treeset->root == NULL) return NULL;
	return (KeyValueNode*)get_subtree_min(tree->treeset->root);
}

KeyValueNode* TreeMap_max(TreeMap* tree) {
	if (tree->treeset->root == NULL) return NULL;
	return (KeyValueNode*)get_subtree_max(tree->treeset->root);
}

KeyValueNode* TreeMap_next(TreeMap* tree, KeyValueNode* node) {
	return (KeyValueNode*)next(tree->treeset, (KeyNode*)node);
}

KeyValueNode* TreeMap_prev(TreeMap* tree, KeyValueNode* node) {
	return (KeyValueNode*)prev(tree->treeset, (KeyNode*)node);
}
