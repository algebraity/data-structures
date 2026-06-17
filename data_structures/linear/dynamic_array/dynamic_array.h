#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

/* ---------- Preprocessor macros ---------- */
#define daType(T)\
	struct {\
		T* data;\
		size_t size, capacity, elmtSize;\
	}

#define daConstruct(type) {\
	.elmtSize = sizeof(type)\
}

/* ---------- Structs ---------- */
typedef struct DA DA;

/* ---------- Functions ---------- */
void daAppend(void* da, void* element, size_t size);
void daRemove(void* da, size_t index);
void daFree(void* array);

#endif

