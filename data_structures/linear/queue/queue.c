#include<stdlib.h>
#include<limits.h>
#include "queue.h"

/* ---------- Methods ---------- */

// Free a Queue node without freeing its value
static void freeQueueNodeOnly(ListNode* node) {
    if (!node) return;
    node->next = NULL;
    node->val = NULL;
    free(node);
}

// Construct a Queue
Queue* constructQueue(Value** vals, size_t valsSize) {
    if (valsSize == 0) return emptyQueue();
    if (!vals && valsSize > 0) return NULL;
    if (valsSize > MAX_LEN) return NULL;
    
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->length = valsSize;

    queue->head = constructList(vals, (int)valsSize);
    if (!queue->head) {
        free(queue);
        return NULL;
    }

    queue->tail = lastNode(queue->head);

    return queue;
}

// Construct and return an empty Queue
Queue* emptyQueue(void) {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;

    return queue;
}

// Returns 1 if a Queue is empty, else 0
int queueIsEmpty(Queue* queue) {
    if (!queue) return 1;
    return queue->length == 0;
}

// Free the memory associated with a Queue
void freeQueue(Queue* queue) {
    if (!queue) return;
    freeList(queue->head);
    free(queue);
}

// Add a Value to the end of the Queue, updating Queue->tail to point at it
// 0 = success, -1 = failure
int enqueue(Queue* queue, Value* value) {
    if (!queue || !value) return -1;
    if (queue->length == MAX_LEN) return -1;

    ListNode* newTail = constructNode(value);
    if (!newTail) return -1;
    if (queue->length == 0) {
        queue->head = newTail;
        queue->head->next = NULL;
    }
    else queue->tail->next = newTail;
    queue->tail = newTail;
    queue->length++;

    return 0;
}

// Remove a Value from the front of the Queue, updating Queue->head
Value* dequeue(Queue* queue) {
    if (!queue) return NULL;
    if (queueIsEmpty(queue)) return NULL;
        
    ListNode* newHead = queue->head->next;
    if (queue->length == 1) {
        newHead = NULL;
        queue->tail = NULL;
    }
    Value* val = queue->head->val;
    freeQueueNodeOnly(queue->head);

    queue->head = newHead;
    queue->length--;

    return val;
}

// Peek at the value at the front of the Queue, returning a copy of its contents
Value* queuePeek(Queue* queue) {
    if (!queue) return NULL;
    if (queueIsEmpty(queue)) return NULL;

    Value* val = copyValue(queue->head->val);
    if (!val) return NULL;

    return val;
}
