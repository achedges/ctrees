//
// Created by Adam Hedges on 7/6/22.
//

#include <stdio.h>
#include "context.h"

int main(int argc, char** args) {

	int results = 0;

	// Primitive tests

	results += test_tree_size();
	results += test_tree_min_max();
	results += test_tree_next_prev_nodes();

	results += test_tree_in_order_traversal();
	results += test_tree_reversed_traversal();
	results += test_tree_scrambled_traversal();

	results += test_tree_delete_inner_node();
	results += test_tree_delete_minmax_nodes();
	results += test_tree_delete_root_node();
	results += test_tree_delete_all_nodes();

	// TreeSet tests
	results += test_treeset_lookup();

	// TreeMap tests
	results += test_treemap_keyvalue_pairs();

	if (results == 0) {
		printf("Ok\n");
	} else {
		printf("!! Failed %d test%s\n", results, results == 1 ? "" : "s");
	}

}