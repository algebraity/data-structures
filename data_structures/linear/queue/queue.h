#ifndef QUEUE_H
#define QUEUE_H

#include<stddef.h>
#include "../linked_list/linked_list.h"
#include "../../../shared_structs/value/value.h"

/* ---------- Definitions of structs ---------- */

typedef struct Queue Queue;

struct Queue {
    ListNode* head;
    ListNode* tail;
    size_t length;
};

/* ---------- Methods ---------- */
Queue* constructQueue(Value** vals, size_t valSize);
Queue* emptyQueue(void);
int queueIsEmpty(Queue* queue);
void freeQueue(Queue* queue);
int enqueue(Queue* queue, Value* value);
Value* dequeue(Queue* queue);
Value* queuePeek(Queue* queue);

#endif