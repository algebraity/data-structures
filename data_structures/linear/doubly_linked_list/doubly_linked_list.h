#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include<stddef.h>
#include "../../../shared_structs/value/value.h"

#define MAX_LEN 10000

/* ---------- Definition of structs ---------- */

typedef struct DListNode DListNode;

struct DListNode {
	DListNode* next;
	DListNode* prev;
	Value* val;
};

/* ---------- Construct and free methods ---------- */
DListNode* constructDNode(Value* val);
DListNode* constructDList(Value** vals, int valSize);
DListNode* copyDListNode(DListNode* node);
DListNode* copyDList(DListNode* head);
DListNode* emptyDList(void);
void freeDNode(DListNode* node);
void freeDList(DListNode* head);

/* ---------- Basic list operations ---------- */
DListNode* dLastNode(DListNode* head);
DListNode* dNthNode(DListNode* head, size_t n);
int dListPushFront(DListNode** head, Value* val);
int dListPushBack(DListNode** head, Value* val);
Value* dListPopFront(DListNode** head);
Value* dListPopBack(DListNode** head);
Value* dListPeekFront(DListNode* head);
Value* dListPeekBack(DListNode* head);
Value* dListGetNthVal(DListNode* head, size_t n);
int dListLength(DListNode* head);

/* ---------- Basic list properties ---------- */
int dIsEmpty(DListNode* head);
int dIsNonEmpty(DListNode* head);
int dIsSorted(DListNode* head);

/* ---------- List manipulation ---------- */
Value* popNthDNode(DListNode** head, size_t n);
DListNode* reverseDList(DListNode** head);
DListNode* sortDList(DListNode** head);

#endif
