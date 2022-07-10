//
// Created by Adam Hedges on 7/6/22.
//

#ifndef CTREES_BASE_H
#define CTREES_BASE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum {
	InOrder,
	PreOrder,
	PostOrder,
	BreadthFirst
} TreeWalkOrder;

typedef struct keynode {
	struct keynode* l;
	struct keynode* r;
	struct keynode* p;
	size_t height;
	void* key;
} KeyNode;

typedef struct keyvaluenode {
	KeyNode* keynode;
	void* value;
} KeyValueNode;

typedef struct {
	size_t size;
	int (*compare)(const void* a, const void* b);
	KeyNode* root;
} TreeSet;

typedef struct {
	TreeSet* treeset;
	KeyValueNode* root;
} TreeMap;

KeyNode* get_subtree_min(KeyNode* node);
KeyNode* get_subtree_max(KeyNode* node);
KeyNode* insert_node(TreeSet* tree, KeyNode* root, KeyNode* node);
KeyNode* find_node(TreeSet* tree, void* key);
void delete_node(TreeSet* tree, KeyNode* node);
void walk_keys(TreeSet* tree, KeyNode* node, TreeWalkOrder order, void** keys, size_t* count);
KeyNode* next(TreeSet* tree, KeyNode* node);
KeyNode* prev(TreeSet* tree, KeyNode* node);

KeyNode* KeyNode_init(void* key);
KeyValueNode* KeyValueNode_init(void* key, void* value);

TreeSet* TreeSet_init(int (*compare)(const void* a, const void* b));
void TreeSet_insert(TreeSet* tree, KeyNode* node);
void TreeSet_delete(TreeSet* tree, KeyNode* node);
KeyNode* TreeSet_find(TreeSet* tree, void* key);
void** TreeSet_get_keys(TreeSet* tree, TreeWalkOrder order);
bool TreeSet_contains(TreeSet* tree, void* key);
KeyNode* TreeSet_min(TreeSet* tree);
KeyNode* TreeSet_max(TreeSet* tree);
KeyNode* TreeSet_next(TreeSet* tree, KeyNode* node);
KeyNode* TreeSet_prev(TreeSet* tree, KeyNode* node);

TreeMap* TreeMap_init(int (*compare)(const void* a, const void* b));
void TreeMap_insert(TreeMap* tree, KeyValueNode* node);
void TreeMap_delete(TreeMap* tree, KeyValueNode* node);
KeyValueNode* TreeMap_find(TreeMap* tree, void* key);
void** TreeMap_get_keys(TreeMap* tree, TreeWalkOrder order);
bool TreeMap_contains(TreeMap* tree, void* key);
KeyValueNode* TreeMap_min(TreeMap* tree);
KeyValueNode* TreeMap_max(TreeMap* tree);
KeyValueNode* TreeMap_next(TreeMap* tree, KeyValueNode* node);
KeyValueNode* TreeMap_prev(TreeMap* tree, KeyValueNode* node);

#endif //CTREES_BASE_H
