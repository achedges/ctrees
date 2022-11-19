//
// Created by Adam Hedges on 7/6/22.
//

#ifndef CTREES_CONTEXT_H
#define CTREES_CONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include "../trees.h"

const extern int LIST_SIZE;
const extern int TEST_KEYS[];
const extern int MAP_KEYS[];
const extern char* MAP_VALUES[];

TreeSet* get_treeset_in_order();
TreeSet* get_treeset_reversed();
TreeSet* get_treeset_scrambled();

void traversal_test_helper(int* results, TreeSet* tree, const int preOrderKeys[], const int postOrderKeys[], const int bfsKeys[]);

// Primitive tests

int test_tree_size();
int test_tree_min_max();
int test_tree_next_prev_nodes();

int test_tree_in_order_traversal();
int test_tree_reversed_traversal();
int test_tree_scrambled_traversal();

int test_tree_delete_inner_node();
int test_tree_delete_minmax_nodes();
int test_tree_delete_root_node();
int test_tree_delete_all_nodes();

// TreeSet tests
int test_treeset_symbols_build();
int test_treeset_lookup();

// TreeMap tests
int test_treemap_keyvalue_pairs();

#endif //CTREES_CONTEXT_H
