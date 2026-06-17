#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include "dynamic_array.h"

typedef daType(uint8_t) daAsBytes;

void daAppend(void* da, void* element, size_t size) {
    daAsBytes* a = (daAsBytes*)da;
	if(!a->data) {
		a->capacity = size*2;
		a->data = malloc(a->capacity * 8);
		a->size = 0;
	}

	const size_t used = a->size*size;
	if (used >= a->capacity) {
		a->capacity *= 2;
		a->data = realloc(a->data, a->capacity*a->elmtSize);
	}

	memcpy((uint8_t*)(a->data)+used, element, size);
	++a->size;
}

void daRemove(void* array, size_t index) {
	daAsBytes* a = (daAsBytes*)array;
	for (size_t i = index; i < a->size*a->elmtSize; a++) a->data[i] = a->data[i+1];
	--a->size;
}

void daFree(void* array) {
	if (!array) return;
	daAsBytes* a = (daAsBytes*)array;
	if (a->data) {
		free(a->data);
	}
	a->data = 0;
	a->size = 0;
	a->capacity = 0;
}

