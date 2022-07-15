//
// Created by Adam Hedges on 7/6/22.
//

#include <stdbool.h>
#include "trees.h"

extern KeyValueNode* insert_node(TreeMap* tree, KeyValueNode* root, KeyValueNode* node);
extern void delete_node(TreeMap* tree, KeyValueNode* node);
extern KeyValueNode* find_node(TreeMap* tree, void* key);
extern void walk_keys(TreeMap* tree, KeyValueNode* root, TreeWalkOrder order, void** keys, size_t* count);
extern KeyValueNode* get_subtree_min(KeyValueNode* root);
extern KeyValueNode* get_subtree_max(KeyValueNode* root);
extern KeyValueNode* next(TreeMap* tree, KeyValueNode* node);
extern KeyValueNode* prev(TreeMap* tree, KeyValueNode* node);

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
	tree->root = (KeyNode*)insert_node((TreeMap*)tree, (KeyValueNode*)tree->root, (KeyValueNode*)node);
	tree->root->p = NULL;
}

void TreeSet_delete(TreeSet* tree, KeyNode* node) {
	delete_node((TreeMap*)tree, (KeyValueNode*)node);
}

KeyNode* TreeSet_find(TreeSet* tree, void* key) {
	return (KeyNode*)find_node((TreeMap*)tree, key);
}

void** TreeSet_get_keys(TreeSet* tree, TreeWalkOrder order) {
	void** keys = malloc(sizeof(void*) * tree->size);
	size_t count = 0;
	walk_keys((TreeMap*)tree, (KeyValueNode*)tree->root, order, keys, &count);
	return keys;
}

bool TreeSet_contains(TreeSet* tree, void* key) {
	return TreeSet_find(tree, key) != NULL;
}

KeyNode* TreeSet_min(TreeSet* tree) {
	if (tree->root == NULL) return NULL;
	return (KeyNode*)get_subtree_min((KeyValueNode*)tree->root);
}

KeyNode* TreeSet_max(TreeSet* tree) {
	if (tree->root == NULL) return NULL;
	return (KeyNode*)get_subtree_max((KeyValueNode*)tree->root);
}

KeyNode* TreeSet_next(TreeSet* tree, KeyNode* node) {
	return (KeyNode*)next((TreeMap*)tree, (KeyValueNode*)node);
}

KeyNode* TreeSet_prev(TreeSet* tree, KeyNode* node) {
	return (KeyNode*)prev((TreeMap*)tree, (KeyValueNode*)node);
}
