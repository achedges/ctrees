//
// Created by Adam Hedges on 7/9/22.
//

#include "context.h"

int test_treeset_lookup() {
	int results = 0;
	TreeSet* tree = get_treeset_in_order();
	for (int i = 0; i < LIST_SIZE; i++) {
		KeyNode* node = TreeSet_find(tree, (void*)&TEST_KEYS[i]);
		if (*(int*)node->key != TEST_KEYS[i]) {
			printf("Unexpected lookup key: %d", *(int*)node->key);
			results += 1;
		}
	}

	return results;
}