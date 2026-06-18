#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_LEN 10000

/* ---------- Definition of structs ---------- */
typedef struct listNode listNode;

struct {
	listNode* next;
	int val;
} listNodeS;

/* ---------- Construct and free methods ---------- */
listNode* constructNode(int val);
listNode* constructList(int* vals, int valSize);
listNode* emptyList(void);
void freeNode(listNode* node);
void freeList(listNode* head);

/* ---------- Basic list operations ---------- */
listNode* lastNode(listNode* head);
listNode* nthNode(listNode* head, size_t n);
int listPush(listNode* head, int val);
int listPop(listNode* head);
int listPeek(listNode* head);
int listGetNthVal(listNode* head, size_t n);
int listLength(listNode* head);

/* ---------- Basic list properties ---------- */
int isEmpty(listNode* head);
int isSorted(listNode* head);

/* ---------- List manipulation ---------- */
int removeNthNode(listNode* head);
int reverseList(listNode* head);
int sortList(listNode* head);



