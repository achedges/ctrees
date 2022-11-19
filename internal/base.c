//
// Created by Adam Hedges on 7/6/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "../trees.h"

size_t get_max_subtree_height(KeyValueNode* node) {
	size_t lh = 0, rh = 0;
	if (node->l != NULL) lh = node->l->height;
	if (node->r != NULL) rh = node->r->height;
	return lh > rh ? lh : rh;
}

KeyValueNode* get_subtree_min(KeyValueNode* node) {
	KeyValueNode* n = node;
	while (n->l != NULL) n = n->l;
	return n;
}

KeyValueNode* get_subtree_max(KeyValueNode* node) {
	KeyValueNode* n = node;
	while (n->r != NULL) n = n->r;
	return n;
}

KeyValueNode* rotate_left(KeyValueNode* node) {
	KeyValueNode* newroot = node->r;
	if (newroot == NULL) {
		return node;
	}
	KeyValueNode* tmp = newroot->l;
	newroot->l = node;
	node->r = tmp;

	if (tmp != NULL) tmp->p = node;

	node->height = get_max_subtree_height(node) + 1;
	newroot->height = get_max_subtree_height(newroot) + 1;

	return newroot;
}

KeyValueNode* rotate_right(KeyValueNode* node) {
	KeyValueNode* newroot = node->l;
	if (newroot == NULL) {
		return node;
	}
	KeyValueNode* tmp = newroot->r;
	newroot->r = node;
	node->l = tmp;

	if (tmp != NULL) tmp->p = node;

	node->height = get_max_subtree_height(node) + 1;
	newroot->height = get_max_subtree_height(node) + 1;

	return newroot;
}

KeyValueNode* replace_node(KeyValueNode* old, KeyValueNode* new) {
	new->l = old->l;
	new->r = old->r;
	new->p = old->p;
	new->height = old->height;
	new->key = old->key;
	return new;
}

KeyValueNode* insert_node(TreeMap* tree, KeyValueNode* root, KeyValueNode* node) {
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

void transplant_node(TreeMap* tree, KeyValueNode* old, KeyValueNode* new) {
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

void delete_node(TreeMap* tree, KeyValueNode* node) {
	if (node == NULL) return;

	if (node->l == NULL) {
		transplant_node(tree, node, node->r);
	} else if (node->r == NULL) {
		transplant_node(tree, node, node->l);
	} else {
		KeyValueNode* y = get_subtree_min(node->r);
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

KeyValueNode* find_node(TreeMap* tree, void* key) {
	KeyValueNode* node = tree->root;
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

void bfs(KeyValueNode* node, BfsItems** depthmap, size_t depth) {
	if (depthmap[depth] == NULL)
		depthmap[depth] = bfs_items_init(depth);
	depthmap[depth]->keys[depthmap[depth]->count++] = node->key;
	if (node->l != NULL)
		bfs(node->l, depthmap, depth + 1);
	if (node->r != NULL)
		bfs(node->r, depthmap, depth + 1);
}

void walk_keys(TreeMap* tree, KeyValueNode* node, TreeWalkOrder order, void** keys, size_t* count) {
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
			while ((1 << bfsdepth) <= tree->size) bfsdepth += 1;

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

KeyValueNode* next(TreeMap* tree, KeyValueNode* node) {
	if (node->r != NULL)
		return get_subtree_min(node->r);

	KeyValueNode* parent = node->p;
	while (parent != NULL && parent->r != NULL && tree->compare(node->key, parent->r->key) == 0) {
		node = parent;
		parent = parent->p;
	}

	return parent;
}

KeyValueNode* prev(TreeMap* tree, KeyValueNode* node) {
	if (node->l != NULL)
		return get_subtree_max(node->l);

	KeyValueNode* parent = node->p;
	while (parent != NULL && parent->l != NULL && tree->compare(node->key, parent->l->key) == 0) {
		node = parent;
		parent = parent->p;
	}

	return parent;
}
