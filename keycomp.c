//
// Created by Adam Hedges on 7/6/22.
//

#include <string.h>

int int_comparer(const void* a, const void* b) {
	int _a = *(int*)a;
	int _b = *(int*)b;
	if (_a < _b)
		return -1;
	else if (_a > _b)
		return 1;
	else
		return 0;
}

int long_comparer(const void* a, const void* b) {
	long _a = *(long*)a;
	long _b = *(long*)b;
	if (_a < _b)
		return -1;
	else if (_a > _b)
		return 1;
	else
		return 0;
}

int string_comparer(const void* a, const void* b) {
	return strcmp((char*)a, (char*)b);
}