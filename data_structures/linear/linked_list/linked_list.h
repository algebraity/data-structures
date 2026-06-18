#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<stddef.h>
#include "../../../shared_structs/value/value.h"

#define MAX_LEN 10000

/* ---------- Definition of structs ---------- */

typedef struct ListNode ListNode;

struct ListNode {
	ListNode* next;
	Value* val;
};

/* ---------- Construct and free methods ---------- */
ListNode* constructNode(Value* val);
ListNode* constructList(Value** vals, int valSize);
ListNode* copyListNode(ListNode* node);
ListNode* copyList(ListNode* head);
ListNode* emptyList(void);
void freeNode(ListNode* node);
void freeList(ListNode* head);

/* ---------- Basic list operations ---------- */
ListNode* lastNode(ListNode* head);
ListNode* nthNode(ListNode* head, size_t n);
int listPush(ListNode** head, Value* val);
Value* listPop(ListNode** head);
Value* listPeek(ListNode* head);
Value* listGetNthVal(ListNode* head, size_t n);
int listLength(ListNode* head);

/* ---------- Basic list properties ---------- */
int isEmpty(ListNode* head);
int isNonEmpty(ListNode* head);
int isSorted(ListNode* head);

/* ---------- List manipulation ---------- */
Value* popNthNode(ListNode** head, size_t n);
ListNode* reverseList(ListNode** head);
ListNode* sortList(ListNode** head);

#endif
