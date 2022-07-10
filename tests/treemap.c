//
// Created by Adam Hedges on 7/9/22.
//

#include "context.h"

int test_treemap_keyvalue_pairs() {
	int results = 0;
	int mapsize = 4;

	TreeMap* map = TreeMap_init(&int_comparer);
	for (int i = 0; i < mapsize; i++) {
		KeyValueNode* node = KeyValueNode_init((void*)&MAP_KEYS[i], (void*)&MAP_VALUES[i]);
		TreeMap_insert(map, node);
	}

	if (map->treeset->size != mapsize) {
		printf("Incorrect map size: %zu\n", map->treeset->size);
		results += 1;
	}

	for (int i = 0; i < mapsize; i++) {
		KeyValueNode* node = TreeMap_find(map, (void*)&MAP_KEYS[i]);
		if (string_comparer(node->value, (void*)&MAP_VALUES[i]) != 0) {
			printf("Incorrect value at node %d\n", *(int*)node->keynode->key);
			results += 1;
		}
	}

	KeyValueNode* node = TreeMap_min(map);
	if (*(int*)node->keynode->key != 1) {
		printf("Unexpected tree map min: %d\n", *(int*)node->keynode->key);
		results += 1;
	}

	if (string_comparer(node->value, "A") != 0) {
		printf("Unexpected tree map min value: %s\n", (char*)node->value);
		results += 1;
	}

	node = TreeMap_max(map);
	if (*(int*)node->keynode->key != 4) {
		printf("Unexpected tree map max: %d\n", *(int*)node->keynode->key);
		results += 1;
	}

	if (string_comparer(node->value, "D") != 0) {
		printf("Unexpected tree map max value: %s\n", (char*)node->value);
		results += 1;
	}

	int nokey = 0;
	KeyValueNode* shouldBeNull = TreeMap_find(map, &nokey);
	if (shouldBeNull != NULL) {
		printf("Unexpected value for absent key\n");
		results += 1;
	}

	int newkey = 1;
	char* newval = "E";
	KeyValueNode* newnode = KeyValueNode_init((void*)&newkey, (void*)newval);
	TreeMap_insert(map, newnode);
	newnode = TreeMap_find(map, (void*)&newkey);
	if (string_comparer(newnode->value, "E") != 0) {
		printf("Unexpected value after replacement\n");
		results += 1;
	}

	return results;
}
