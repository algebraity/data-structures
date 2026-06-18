#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_LEN 10000

/* ---------- Definition of structs ---------- */
typedef struct ListNode ListNode;

struct ListNode {
	ListNode* next;
	int val;
};

/* ---------- Construct and free methods ---------- */
ListNode* constructNode(int val);
ListNode* constructList(int* vals, int valSize);
ListNode* emptyList(void);
void freeNode(ListNode* node);
void freeList(ListNode* head);

/* ---------- Basic list operations ---------- */
ListNode* lastNode(ListNode* head);
ListNode* nthNode(ListNode* head, size_t n);
int listPush(ListNode* head, int val);
int listPop(ListNode* head);
int listPeek(ListNode* head);
int listGetNthVal(ListNode* head, size_t n);
int listLength(ListNode* head);

/* ---------- Basic list properties ---------- */
int isEmpty(ListNode* head);
int isSorted(ListNode* head);

/* ---------- List manipulation ---------- */
int removeNthNode(ListNode* head, size_t n);
int reverseList(ListNode* head);
int sortList(ListNode* head);

#endif
