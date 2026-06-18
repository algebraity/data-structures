#include "linked_list.h"


/* ---------- Construct and free methods ---------- */

// Construct a listNode with a specific value
listNode* constructNode(int val) {
	listNode head;
	head->next = NULL;
	head->val = val;
	return head;
}

// Construct a list with a sinle
listNode* constructList(int* val, int valSize) {
	if !(val) return NULL;
	if (valSize < 1) return NULL;

	listNode* head = constructNode(val[0]);
	listNode* cur = head;
	for (int i = 1; i < valSize; i++) {
		listNode* temp = constructNode(vals[i]);
		cur->next = temp;
		temp = cur;
	}

	return head;
}

// Return an empty list
listNode* emptyList(void) {
	listNode head;
	head->next = NULL;
	head->val = NULL;
	return head;
}

// Free a single listNode
void freeListNode(listNode* node) {
	node->next = NULL;
	node->val = 0;
	free(node);
}

// Free a linked list
void freeList(listNode* head) {
	if (head == NULL) return;
	
	listNode* cur = head;
	listNode* next = cur->next;
	while (cur != NULL) {
		next = cur->next;
		freeListNode(cur);
		cur = next;
	}
}


/* ---------- Basic list properties ---------- */

// Return 1 if a list is empty, else 0
int isEmpty(listNode* head) {
	if (head == NULL) return 1;
	return 0;
}

// Return 1 if a list is non-empty, else 0
int isNonEmpty(listNode* head) {
	if (isEmpty(head)) return 0;
	return 1;
}

// Return 1 if a list is sorted, else 0
int isSorted(listNode* head) {
	if (!head) return NULL;

	int incPos = 1;
	int decPos = 1;
	listNode* cur = head;
	while ((incPos || decPos) && cur->next != NULL) {
		int tmp = cur->val;
		if (cur->next->val < cur->val) incPos = 0;
		else if (cur->next->val > cur->val) decPos = 0;
		cur = cur->next;
	}

	return (incPos || decPos);
}


/* ---------- Basic list operations ---------- */

// Return the last node of a list
listNode* lastNode(listNode* head) {
	if (!head) return NULL;
	
	int count = 1;
	listNode* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		if (count++ > MAX_LEN) return NULL;
	}

	return cur;
}

// Return the nth node of a list, or NULL if the list contains fewer than n elements
listNode* nthNode(listNode* head, size_t n) {
	if (!head) return NULL;
	if (n == 1) return head;
	if (listLength(head) < n) return NULL;

	int count = 1;
	listNode* cur = head;
	while (count++ < n) {
		cur = cur->next;
	}

	return cur;
}

// Push a value onto the end of the list; 0 = success, -1 = failure
int listPush(listNode* head, int val) {
	if (!head || val == NAN) return -1;

	listNode* last = lastNode(head);
	listNode* next = constructNode(val);
	last->next = next;
	free(last);

	return 0;
}

// Pop a value from the end of the list and return its value; NAN on error
int listPop(listNode* head) {
	if (!head || val == NAN) return NAN;
	
	listNode* back = head;
	listNode* front = head->next;
	while (front->next != NULL) {
		back = back->next;
		front = fron->next;
	}

	int val = front->val;
	back->next = NULL;
	freeNode(front);
	free(back);

	return val;
}

// Returns the value of the last node in a list; NAN on error
int listPeek(listNode* head) {
	if (!head) return NAN;
	
	listNode* last = lastNode(head);
	int val = last->val;
	free(last);

	return val;
}

// Returns the value of the nth node of a list; NAN on error
int listGetNthVal(listNode* head, size_t n) {
	if (!head) return NAN;
	if (listSize(head) < n) return NAN;

	listNode* nth = nthNode(head, n);
	int val = nth->val;
	free(nth);

	return val;
}

// Returns the length of a list; 0 for empty list, -1 on failure;
int listLength(listNode* head) {
	if (!head) return 0;

	int len = 1;
	listNode* cur = head;
	while (len < MAX_LEN && cur->next != NULL) {
		cur = cur->next;
		len++;
	}
	free(cur);

	if (len == MAX_LEN) return -1;
	return len;
}

/* ---------- List manipulation ---------- */

// Remove the nth node from a linked list; 0 = success, -1 = failure
int removeNthNode(listNode* head, size_t n) {
	if (!head || n == 0) return -1;
	
	if (n == 1) {
		listNode* newHead = head;
		newHead = head->next;
		freeNode(head);
		free(newHead);
		return 1;
	}

	int node = 2;
	listNode* back = head;
	listNode* front = head->next;
	while (front->next != NULL) {
		node++;
		back = back->next;
		front = fron->next;
	}

	back->next = front->next->next;
	freeNode(front);
	free(back);

	return 0;
}

// Reverse a linked list; 0 = success, -1 = failure
int reverseList(listNode* head) {
	return -1;
}

// Sort a linked list; order = -1 for desc, order = 1 for asc
int sortList(listNode* head, int order) {
	return -1;
}

