//
// Created by Adam Hedges on 7/6/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "base.h"

size_t get_max_subtree_height(KeyNode* node) {
	size_t lh = 0, rh = 0;
	if (node->l != NULL) lh = node->l->height;
	if (node->r != NULL) rh = node->r->height;
	return lh > rh ? lh : rh;
}

KeyNode* get_subtree_min(KeyNode* node) {
	KeyNode* n = node;
	while (n->l != NULL) n = n->l;
	return n;
}

KeyNode* get_subtree_max(KeyNode* node) {
	KeyNode* n = node;
	while (n->r != NULL) n = n->r;
	return n;
}

KeyNode* rotate_left(KeyNode* node) {
	KeyNode* newroot = node->r;
	KeyNode* tmp = newroot->l;
	newroot->l = node;
	node->r = tmp;

	if (tmp != NULL) tmp->p = node;

	node->height = get_max_subtree_height(node) + 1;
	newroot->height = get_max_subtree_height(newroot) + 1;

	return newroot;
}

KeyNode* rotate_right(KeyNode* node) {
	KeyNode* newroot = node->l;
	KeyNode* tmp = newroot->r;
	newroot->r = node;
	node->l = tmp;

	if (tmp != NULL) tmp->p = node;

	node->height = get_max_subtree_height(node) + 1;
	newroot->height = get_max_subtree_height(node) + 1;

	return newroot;
}

KeyNode* replace_node(KeyNode* old, KeyNode* new) {
	new->l = old->l;
	new->r = old->r;
	new->p = old->p;
	new->height = old->height;
	new->key = old->key;
	return new;
}

KeyNode* insert_node(TreeSet* tree, KeyNode* root, KeyNode* node) {
	if (root == NULL) {
		root = node;
		tree->size += 1;
		return root;
	}

	int keycomp = tree->compare(node->key, root->key);
	if (keycomp < 0) {
		root->l = insert_node(tree, root->l, node);
		root->l->p = root;
	} else if (keycomp > 0) {
		root->r = insert_node(tree, root->r, node);
		root->r->p = root;
	} else {
		root = replace_node(root, node);
	}

	int lheight = 0, rheight = 0;

	if (root->l != NULL) lheight = (int)root->l->height;
	if (root->r != NULL) rheight = (int)root->r->height;

	root->height = 1 + (lheight > rheight ? lheight : rheight);
	int balance = lheight - rheight;

	if (balance > 1 && tree->compare(node->key, root->l->key) < 0) {
		root = rotate_right(root);
	} else if (balance < -1 && tree->compare(node->key, root->r->key) > 0) {
		root = rotate_left(root);
	} else if (balance > 1 && tree->compare(node->key, root->l->key) > 0) {
		root->l = rotate_left(root->l);
		root = rotate_right(root);
	} else if (balance < -1 && tree->compare(node->key, root->r->key) < 0) {
		root->r = rotate_right(root->r);
		root = rotate_left(root);
	}

	if (root->l != NULL) root->l->p = root;
	if (root->r != NULL) root->r->p = root;

	return root;
}

void transplant_node(TreeSet* tree, KeyNode* old, KeyNode* new) {
	if (old->p == NULL) {
		tree->root = new;
	} else if (old->p->l != NULL && tree->compare(old->key, old->p->l->key) == 0) {
		old->p->l = new;
	} else {
		old->p->r = new;
	}

	if (new != NULL)
		new->p = old->p;
}

void delete_node(TreeSet* tree, KeyNode* node) {
	if (node == NULL) return;

	if (node->l == NULL) {
		transplant_node(tree, node, node->r);
	} else if (node->r == NULL) {
		transplant_node(tree, node, node->l);
	} else {
		KeyNode* y = get_subtree_min(node->r);
		if (tree->compare(y->p->key, node->key) != 0) {
			transplant_node(tree, y, y->r);
			y->r = node->r;
			y->r->p = y;
		}
		transplant_node(tree, node, y);
		y->l = node->l;
		y->l->p = y;
	}

	tree->size -= 1;
}

KeyNode* find_node(TreeSet* tree, void* key) {
	KeyNode* node = tree->root;
	while (node != NULL) {
		int keycomp = tree->compare(key, node->key);
		if (keycomp == 0) {
			break;
		} else {
			node = keycomp < 0 ? node->l : node->r;
		}
	}
	return node;
}

typedef struct {
	void** keys;
	size_t size;
	size_t count;
} BfsItems;

BfsItems* bfs_items_init(size_t depth) {
	BfsItems* items = malloc(sizeof(BfsItems));
	items->count = 0;
	items->size = 1;

	for (int i = 0; i < depth; i++) {
		items->size <<= 1;
	}

	items->keys = malloc(sizeof(void*) * items->size);
	return items;
}

void bfs(KeyNode* node, BfsItems** depthmap, size_t depth) {
	if (depthmap[depth] == NULL)
		depthmap[depth] = bfs_items_init(depth);
	depthmap[depth]->keys[depthmap[depth]->count++] = node->key;
	if (node->l != NULL)
		bfs(node->l, depthmap, depth + 1);
	if (node->r != NULL)
		bfs(node->r, depthmap, depth + 1);
}

void walk_keys(TreeSet* tree, KeyNode* node, TreeWalkOrder order, void** keys, size_t* count) {
	size_t bfsdepth = 1;
	size_t bfscount = 0;
	BfsItems** depthmap;

	switch (order) {
		case InOrder:
			if (node->l != NULL) walk_keys(tree, node->l, order, keys, count);
			keys[(*count)++] = node->key;
			if (node->r != NULL) walk_keys(tree, node->r, order, keys, count);
			break;
		case PreOrder:
			keys[(*count)++] = node->key;
			if (node->l != NULL) walk_keys(tree, node->l, order, keys, count);
			if (node->r != NULL) walk_keys(tree, node->r, order, keys, count);
			break;
		case PostOrder:
			if (node->l != NULL) walk_keys(tree, node->l, order, keys, count);
			if (node->r != NULL) walk_keys(tree, node->r, order, keys, count);
			keys[(*count)++] = node->key;
			break;
		case BreadthFirst:
			while ((1 << bfsdepth) < tree->size) bfsdepth += 1;

			depthmap = malloc(sizeof(BfsItems*) * bfsdepth);
			for (int d = 0; d < bfsdepth; d++) depthmap[d] = NULL;
			bfs(tree->root, depthmap, 0);

			for (int d = 0; d < bfsdepth; d++) {
				for (int k = 0; k < depthmap[d]->count; k++) {
					keys[bfscount++] = depthmap[d]->keys[k];
				}
			}

			break;
		default:
			break;
	}
}

KeyNode* next(TreeSet* tree, KeyNode* node) {
	if (node->r != NULL)
		return get_subtree_min(node->r);

	KeyNode* parent = node->p;
	while (parent != NULL && parent->r != NULL && tree->compare(node->key, parent->r->key) == 0) {
		node = parent;
		parent = parent->p;
	}

	return parent;
}

KeyNode* prev(TreeSet* tree, KeyNode* node) {
	if (node->l != NULL)
		return get_subtree_max(node->l);

	KeyNode* parent = node->p;
	while (parent != NULL && parent->l != NULL && tree->compare(node->key, parent->l->key) == 0) {
		node = parent;
		parent = parent->p;
	}

	return parent;
}
