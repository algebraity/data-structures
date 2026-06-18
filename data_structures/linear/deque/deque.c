#include<stdlib.h>
#include "deque.h"

/* ---------- Methods ---------- */

// Free a Deque node without freeing its value
static void freeDequeNodeOnly(DListNode* node) {
    if (!node) return;
    node->next = NULL;
    node->prev = NULL;
    node->val = NULL;
    free(node);
}

// Construct a Deque
Deque* constructDeque(Value** vals, size_t valsSize) {
    if (valsSize == 0) return emptyDeque();
    if (!vals && valsSize > 0) return NULL;
    if (valsSize > MAX_LEN) return NULL;

    Deque* deque = emptyDeque();
    if (!deque) return NULL;

    for (size_t i = 0; i < valsSize; i++) {
        if (dequePushBack(deque, vals[i]) != 0) {
            freeDeque(deque);
            return NULL;
        }
    }

    return deque;
}

// Construct and return an empty Deque
Deque* emptyDeque(void) {
    Deque* deque = malloc(sizeof(Deque));
    if (!deque) return NULL;

    deque->head = NULL;
    deque->tail = NULL;
    deque->length = 0;

    return deque;
}

// Returns 1 if a Deque is empty, else 0
int dequeIsEmpty(Deque* deque) {
    if (!deque) return 1;
    return deque->length == 0;
}

// Free the memory associated with a Deque
void freeDeque(Deque* deque) {
    if (!deque) return;
    freeDList(deque->head);
    free(deque);
}

// Add a Value to the front of the Deque, updating Deque->head to point at it
// 0 = success, -1 = failure
int dequePushFront(Deque* deque, Value* value) {
    if (!deque || !value) return -1;
    if (deque->length >= MAX_LEN) return -1;

    DListNode* newHead = constructDNode(value);
    if (!newHead) return -1;

    if (deque->length == 0) {
        deque->head = newHead;
        deque->tail = newHead;
    }
    else {
        newHead->next = deque->head;
        deque->head->prev = newHead;
        deque->head = newHead;
    }
    deque->length++;

    return 0;
}

// Add a Value to the back of the Deque, updating Deque->tail to point at it
// 0 = success, -1 = failure
int dequePushBack(Deque* deque, Value* value) {
    if (!deque || !value) return -1;
    if (deque->length >= MAX_LEN) return -1;

    DListNode* newTail = constructDNode(value);
    if (!newTail) return -1;

    if (deque->length == 0) {
        deque->head = newTail;
        deque->tail = newTail;
    }
    else {
        newTail->prev = deque->tail;
        deque->tail->next = newTail;
        deque->tail = newTail;
    }
    deque->length++;

    return 0;
}

// Remove a Value from the front of the Deque, updating Deque->head
Value* dequePopFront(Deque* deque) {
    if (!deque) return NULL;
    if (dequeIsEmpty(deque)) return NULL;

    DListNode* oldHead = deque->head;
    DListNode* newHead = oldHead->next;
    Value* val = oldHead->val;

    deque->head = newHead;
    if (newHead) newHead->prev = NULL;
    else {
        deque->tail = NULL;
    }

    freeDequeNodeOnly(oldHead);
    deque->length--;

    return val;
}

// Remove a Value from the back of the Deque, updating Deque->tail
Value* dequePopBack(Deque* deque) {
    if (!deque) return NULL;
    if (dequeIsEmpty(deque)) return NULL;

    DListNode* oldTail = deque->tail;
    DListNode* newTail = oldTail->prev;
    Value* val = oldTail->val;

    deque->tail = newTail;
    if (newTail) newTail->next = NULL;
    else {
        deque->head = NULL;
    }

    freeDequeNodeOnly(oldTail);
    deque->length--;

    return val;
}

// Peek at the value at the front of the Deque, returning a copy of its contents
Value* dequePeekFront(Deque* deque) {
    if (!deque) return NULL;
    if (dequeIsEmpty(deque)) return NULL;

    Value* val = copyValue(deque->head->val);
    if (!val) return NULL;

    return val;
}

// Peek at the value at the back of the Deque, returning a copy of its contents
Value* dequePeekBack(Deque* deque) {
    if (!deque) return NULL;
    if (dequeIsEmpty(deque)) return NULL;

    Value* val = copyValue(deque->tail->val);
    if (!val) return NULL;

    return val;
}
