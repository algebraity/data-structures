#include<stdlib.h>
#include "doubly_linked_list.h"


/* ---------- Helper methods ---------- */

// Return 1 if a value can be treated as numeric, else 0
static int isNumericValue(Value* val) {
	if (!val) return 0;
	return val->type == VALUE_INT || val->type == VALUE_DOUBLE || val->type == VALUE_CHAR;
}

// Convert a numeric value to a double
static double numericValue(Value* val) {
	if (val->type == VALUE_INT) return val->data.intVal;
	if (val->type == VALUE_DOUBLE) return val->data.floatVal;
	return val->data.charVal;
}

// Compare two numeric values; -1 = failure, 0 = success
static int compareValues(Value* left, Value* right, int* result) {
	if (!isNumericValue(left) || !isNumericValue(right) || !result) return -1;

	double leftVal = numericValue(left);
	double rightVal = numericValue(right);

	if (leftVal < rightVal) *result = -1;
	else if (leftVal > rightVal) *result = 1;
	else *result = 0;

	return 0;
}

// Return 1 if a list contains only numeric values, else 0
static int isNumericDList(DListNode* head) {
	if (!head) return 1;

	int count = 0;
	DListNode* cur = head;
	while (cur != NULL) {
		if (!isNumericValue(cur->val)) return 0;
		cur = cur->next;
		if (++count > MAX_LEN) return 0;
	}

	return 1;
}

// Free a node without freeing its value
static void freeDNodeOnly(DListNode* node) {
	if (!node) return;
	node->next = NULL;
	node->prev = NULL;
	node->val = NULL;
	free(node);
}

// Helper method for sortDList; merges two sorted lists in order
static DListNode* merge(DListNode* L, DListNode* R) {
	DListNode tmp;
	DListNode* tail = &tmp;
	tmp.next = NULL;
	tmp.prev = NULL;
	tmp.val = NULL;

	while (L != NULL && R != NULL) {
		int result = 0;
		if (compareValues(L->val, R->val, &result) == 0 && result <= 0) {
			tail->next = L;
			L->prev = (tail == &tmp) ? NULL : tail;
			L = L->next;
		}
		else {
			tail->next = R;
			R->prev = (tail == &tmp) ? NULL : tail;
			R = R->next;
		}
		tail = tail->next;
	}

	tail->next = (L != NULL) ? L : R;
	if (tail->next) tail->next->prev = (tail == &tmp) ? NULL : tail;
	return tmp.next;
}

// Helper method for sortDList; sorts based on length
static DListNode* sort(DListNode* head, size_t len) {
	if (len < 2) return head;

	size_t leftLen = len / 2;
	DListNode* cur = head;
	for (size_t i = 1; i < leftLen; i++) {
		cur = cur->next;
	}

	DListNode* right = cur->next;
	cur->next = NULL;
	if (right) right->prev = NULL;

	return merge(sort(head, leftLen), sort(right, len - leftLen));
}


/* ---------- Construct and free methods ---------- */

// Construct a DListNode with a specific value
DListNode* constructDNode(Value* val) {
	DListNode* node = malloc(sizeof(DListNode));
	if (!node) return NULL;
	node->next = NULL;
	node->prev = NULL;
	node->val = copyValue(val);
	if (val && !node->val) {
		free(node);
		return NULL;
	}
	return node;
}

// Construct a list from an array of values
DListNode* constructDList(Value** vals, int valSize) {
	if (valSize < 1) return emptyDList();
	if (!vals) return NULL;

	for (int i = 0; i < valSize; i++) {
		if (!vals[i]) return NULL;
	}

	DListNode* head = constructDNode(vals[0]);
	if (!head) return NULL;

	DListNode* cur = head;
	for (int i = 1; i < valSize; i++) {
		DListNode* temp = constructDNode(vals[i]);
		if (!temp) {
			freeDList(head);
			return NULL;
		}
		cur->next = temp;
		temp->prev = cur;
		cur = cur->next;
	}

	return head;
}

// Copy a single DListNode
DListNode* copyDListNode(DListNode* node) {
	if (!node) return NULL;
	return constructDNode(node->val);
}

// Copy a doubly linked list
DListNode* copyDList(DListNode* head) {
	if (!head) return NULL;

	DListNode* copy = copyDListNode(head);
	if (!copy) return NULL;

	DListNode* copyCur = copy;
	DListNode* cur = head->next;
	while (cur != NULL) {
		DListNode* temp = copyDListNode(cur);
		if (!temp) {
			freeDList(copy);
			return NULL;
		}
		copyCur->next = temp;
		temp->prev = copyCur;
		copyCur = copyCur->next;
		cur = cur->next;
	}

	return copy;
}

// Return an empty list
DListNode* emptyDList(void) {
	return NULL;
}

// Free a single DListNode
void freeDNode(DListNode* node) {
	if (!node) return;
	freeValue(node->val);
	node->next = NULL;
	node->prev = NULL;
	node->val = NULL;
	free(node);
}

// Free a doubly linked list
void freeDList(DListNode* head) {
	DListNode* cur = head;
	while (cur != NULL) {
		DListNode* next = cur->next;
		freeDNode(cur);
		cur = next;
	}
}


/* ---------- Basic list properties ---------- */

// Return 1 if a list is empty, else 0
int dIsEmpty(DListNode* head) {
	if (!head) return 1;
	return 0;
}

// Return 1 if a list is non-empty, else 0
int dIsNonEmpty(DListNode* head) {
	if (dIsEmpty(head)) return 0;
	return 1;
}

// Return 1 if a list is sorted, else 0
int dIsSorted(DListNode* head) {
	if (!head) return 1;
	if (!isNumericDList(head)) return 0;

	DListNode* cur = head;
	while (cur->next != NULL) {
		int result = 0;
		if (compareValues(cur->val, cur->next->val, &result) != 0) return 0;
		if (result > 0) return 0;
		cur = cur->next;
	}

	return 1;
}


/* ---------- Basic list operations ---------- */

// Return the last node of a list
DListNode* dLastNode(DListNode* head) {
	if (!head) return NULL;

	int count = 1;
	DListNode* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		if (count++ > MAX_LEN) return NULL;
	}

	return cur;
}

// Return the nth node of a list, or NULL if the list contains fewer than n elements
DListNode* dNthNode(DListNode* head, size_t n) {
	if (!head || n == 0) return NULL;

	size_t count = 1;
	DListNode* cur = head;
	while (cur != NULL && count < n) {
		cur = cur->next;
		count++;
		if (count > MAX_LEN) return NULL;
	}

	if (!cur || !cur->val) return NULL;
	return cur;
}

// Push a value onto the front of the list; 0 = success, -1 = failure
int dListPushFront(DListNode** head, Value* val) {
	if (!head || !val) return -1;

	DListNode* newHead = constructDNode(val);
	if (!newHead) return -1;

	newHead->next = *head;
	if (*head) (*head)->prev = newHead;
	*head = newHead;

	return 0;
}

// Push a value onto the back of the list; 0 = success, -1 = failure
int dListPushBack(DListNode** head, Value* val) {
	if (!head || !val) return -1;
	if (!*head) return dListPushFront(head, val);

	DListNode* last = dLastNode(*head);
	if (!last || !last->val) return -1;

	DListNode* next = constructDNode(val);
	if (!next) return -1;
	last->next = next;
	next->prev = last;

	return 0;
}

// Pop a value from the front of the list and return its value
Value* dListPopFront(DListNode** head) {
	return popNthDNode(head, 1);
}

// Pop a value from the back of the list and return its value
Value* dListPopBack(DListNode** head) {
	if (!head || !*head) return NULL;
	int len = dListLength(*head);
	if (len < 1) return NULL;
	return popNthDNode(head, len);
}

// Returns a copy of the value of the frontmost node in a list
Value* dListPeekFront(DListNode* head) {
	if (!head) return NULL;
	return copyValue(head->val);
}

// Returns a copy of the value of the backmost node in a list
Value* dListPeekBack(DListNode* head) {
	if (!head) return NULL;

	DListNode* last = dLastNode(head);
	if (!last) return NULL;

	return copyValue(last->val);
}

// Returns a copy of the value of the nth node of a list
Value* dListGetNthVal(DListNode* head, size_t n) {
	DListNode* nth = dNthNode(head, n);
	if (!nth) return NULL;

	return copyValue(nth->val);
}

// Returns the length of a list; 0 for empty list, -1 on failure
int dListLength(DListNode* head) {
	if (!head) return 0;

	int len = 0;
	DListNode* cur = head;
	while (cur != NULL) {
		if (!cur->val) return -1;
		cur = cur->next;
		len++;
		if (len > MAX_LEN) return -1;
	}

	return len;
}


/* ---------- List manipulation ---------- */

// Pop the nth node from a doubly linked list and return its value
Value* popNthDNode(DListNode** head, size_t n) {
	if (!head || !*head || n == 0) return NULL;

	DListNode* node = dNthNode(*head, n);
	if (!node) return NULL;

	Value* val = node->val;
	if (node->prev) node->prev->next = node->next;
	else *head = node->next;
	if (node->next) node->next->prev = node->prev;

	freeDNodeOnly(node);
	return val;
}

// Reverse a doubly linked list in place; 0 = success, -1 = failure
int reverseDList(DListNode** head) {
	if (!head) return -1;
	if (!*head) return 0;

	DListNode* cur = *head;
	DListNode* newHead = NULL;
	while (cur != NULL) {
		DListNode* next = cur->next;
		cur->next = cur->prev;
		cur->prev = next;
		newHead = cur;
		cur = next;
	}

	*head = newHead;
	return 0;
}

// Sort a doubly linked list in ascending order in place; 0 = success, -1 = failure
int sortDList(DListNode** head) {
	if (!head) return -1;
	if (!*head) return 0;

	int len = dListLength(*head);
	if (len < 0) return -1;
	if (len < 2) return 0;
	if (!isNumericDList(*head)) return -1;

	*head = sort(*head, len);
	if (!*head) return -1;

	DListNode* prev = NULL;
	DListNode* cur = *head;
	while (cur != NULL) {
		cur->prev = prev;
		prev = cur;
		cur = cur->next;
	}

	return 0;
}
