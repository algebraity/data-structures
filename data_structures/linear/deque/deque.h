#ifndef DEQUE_H
#define DEQUE_H

#include<stddef.h>
#include "../doubly_linked_list/doubly_linked_list.h"
#include "../../../shared_structs/value/value.h"

/* ---------- Definitions of structs ---------- */

typedef struct Deque Deque;

struct Deque {
    DListNode* head;
    DListNode* tail;
    size_t length;
};

/* ---------- Methods ---------- */
Deque* constructDeque(Value** vals, size_t valSize);
Deque* emptyDeque(void);
int dequeIsEmpty(Deque* deque);
void freeDeque(Deque* deque);
int dequePushFront(Deque* deque, Value* value);
int dequePushBack(Deque* deque, Value* value);
Value* dequePopFront(Deque* deque);
Value* dequePopBack(Deque* deque);
Value* dequePeekFront(Deque* deque);
Value* dequePeekBack(Deque* deque);

#endif
