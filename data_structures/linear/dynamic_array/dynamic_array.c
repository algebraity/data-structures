#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "dynamic_array.h"

typedef daType(uint8_t) daAsBytes;

void daAppend(void* da, void* element, size_t size) {
	daAsBytes* a = (daAsBytes*)da;
	if (!a || !element || size == 0) return;
	if (a->elmtSize == 0) a->elmtSize = size;
	if (a->elmtSize != size) return;

	size_t used = a->size * a->elmtSize;
	size_t needed = used + a->elmtSize;

	if (!a->data) {
		a->capacity = a->elmtSize * 2;
		while (a->capacity < needed) {
			if (a->capacity > SIZE_MAX / 2) return;
			a->capacity *= 2;
		}
		a->data = malloc(a->capacity);
		if (!a->data) {
			a->capacity = 0;
			return;
		}
		a->size = 0;
	}

	if (needed > a->capacity) {
		size_t newCapacity = a->capacity;
		while (newCapacity < needed) {
			if (newCapacity > SIZE_MAX / 2) return;
			newCapacity *= 2;
		}

		uint8_t* newData = realloc(a->data, newCapacity);
		if (!newData) return;
		a->data = newData;
		a->capacity = newCapacity;
	}

	memcpy(a->data + used, element, a->elmtSize);
	++a->size;
}

void daRemove(void* array, size_t index) {
	daAsBytes* a = (daAsBytes*)array;
	if (!a || !a->data || a->elmtSize == 0 || index >= a->size) return;

	if (index < a->size - 1) {
		uint8_t* dest = a->data + index * a->elmtSize;
		uint8_t* src = dest + a->elmtSize;
		size_t bytes = (a->size - index - 1) * a->elmtSize;
		memmove(dest, src, bytes);
	}
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
