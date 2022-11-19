//
// Created by Adam Hedges on 7/9/22.
//

#include <strings.h>
#include "context.h"

int test_treeset_symbols_build() {
	int results = 0;

	// this progression of inputs was producing a SIGSEGV error due to a NULL 'newroot' during rotation
	const char* symbols[] = { "BIIB", "LRCX", "MU", "PDD", "SPLK", "INCY", "CSCO", "MAR", "BIDU", "PTON", "NVDA", "SBUX", "SNPS", "WBA", "AMD", "DLTR", "LULU" };

	TreeSet* tree = TreeSet_init(&string_comparer);
	for (int i = 0; i < sizeof(symbols) / sizeof(char*); i++) {
		char* symbolkey = calloc(10, sizeof(char));
		strcpy(symbolkey, symbols[i]);
		KeyNode* node = KeyNode_init(symbolkey);
		TreeSet_insert(tree, node);
	}
	for (int i = 0; i < sizeof(symbols) / sizeof(char*); i++) {
		KeyNode* findnode = TreeSet_find(tree, (void*)symbols[i]);
		if (findnode == NULL) {
			printf("%s not found after tree insert\n", symbols[i]);
			results += 1;
		}
	}
	return results;
}

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