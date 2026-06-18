#include<stdlib.h>
#include "linked_list.h"


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
static int isNumericList(ListNode* head) {
	if (!head) return 1;
	if (isEmpty(head)) return 1;

	int count = 0;
	ListNode* cur = head;
	while (cur != NULL) {
		if (!isNumericValue(cur->val)) return 0;
		cur = cur->next;
		if (++count > MAX_LEN) return 0;
	}

	return 1;
}

// Free a node without freeing its value
static void freeNodeOnly(ListNode* node) {
	if (!node) return;
	node->next = NULL;
	node->val = NULL;
	free(node);
}

// Helper method for sortList; merges two sorted lists in order
static ListNode* merge(ListNode* L, ListNode* R) {
	ListNode tmp;
	ListNode* tail = &tmp;
	tmp.next = NULL;
	tmp.val = NULL;

	while (L != NULL && R != NULL) {
		int result = 0;
		if (compareValues(L->val, R->val, &result) == 0 && result <= 0) {
			tail->next = L;
			L = L->next;
		}
		else {
			tail->next = R;
			R = R->next;
		}
		tail = tail->next;
	}

	tail->next = (L != NULL) ? L : R;
	return tmp.next;
}

// Helper method for sortList; sorts based on length
static ListNode* sort(ListNode* head, size_t len) {
	if (len < 2) return head;

	size_t leftLen = len / 2;
	ListNode* cur = head;
	for (size_t i = 1; i < leftLen; i++) {
		cur = cur->next;
	}

	ListNode* right = cur->next;
	cur->next = NULL;

	return merge(sort(head, leftLen), sort(right, len - leftLen));
}


/* ---------- Construct and free methods ---------- */

// Construct a ListNode with a specific value
ListNode* constructNode(Value* val) {
	ListNode* node = malloc(sizeof(ListNode));
	if (!node) return NULL;
	node->next = NULL;
	node->val = val;
	return node;
}

// Construct a list from an array of values
ListNode* constructList(Value** vals, int valSize) {
	if (valSize < 1) return emptyList();
	if (!vals) return NULL;

	for (int i = 0; i < valSize; i++) {
		if (!vals[i]) {
			for (int j = 0; j < valSize; j++) freeValue(vals[j]);
			return NULL;
		}
	}

	ListNode* head = constructNode(vals[0]);
	if (!head) {
		for (int i = 0; i < valSize; i++) freeValue(vals[i]);
		return NULL;
	}

	ListNode* cur = head;
	for (int i = 1; i < valSize; i++) {
		ListNode* temp = constructNode(vals[i]);
		if (!temp) {
			freeList(head);
			for (int j = i; j < valSize; j++) freeValue(vals[j]);
			return NULL;
		}
		cur->next = temp;
		cur = cur->next;
	}

	return head;
}

// Copy a single ListNode
ListNode* copyListNode(ListNode* node) {
	if (!node) return NULL;

	Value* val = copyValue(node->val);
	if (node->val && !val) return NULL;

	ListNode* copy = constructNode(val);
	if (!copy) {
		freeValue(val);
		return NULL;
	}

	return copy;
}

// Copy a linked list
ListNode* copyList(ListNode* head) {
	if (!head) return NULL;

	ListNode* copy = copyListNode(head);
	if (!copy) return NULL;

	ListNode* copyCur = copy;
	ListNode* cur = head->next;
	while (cur != NULL) {
		ListNode* temp = copyListNode(cur);
		if (!temp) {
			freeList(copy);
			return NULL;
		}
		copyCur->next = temp;
		copyCur = copyCur->next;
		cur = cur->next;
	}

	return copy;
}

// Return an empty list
ListNode* emptyList(void) {
	return constructNode(NULL);
}

// Free a single ListNode
void freeNode(ListNode* node) {
	if (!node) return;
	freeValue(node->val);
	node->next = NULL;
	node->val = NULL;
	free(node);
}

// Free a linked list
void freeList(ListNode* head) {
	ListNode* cur = head;
	while (cur != NULL) {
		ListNode* next = cur->next;
		freeNode(cur);
		cur = next;
	}
}


/* ---------- Basic list properties ---------- */

// Return 1 if a list is empty, else 0
int isEmpty(ListNode* head) {
	if (!head) return 1;
	return head->val == NULL && head->next == NULL;
}

// Return 1 if a list is non-empty, else 0
int isNonEmpty(ListNode* head) {
	if (isEmpty(head)) return 0;
	return 1;
}

// Return 1 if a list is sorted, else 0
int isSorted(ListNode* head) {
	if (!head || isEmpty(head)) return 1;
	if (!isNumericList(head)) return 0;

	ListNode* cur = head;
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
ListNode* lastNode(ListNode* head) {
	if (!head) return NULL;
	
	int count = 1;
	ListNode* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		if (count++ > MAX_LEN) return NULL;
	}

	return cur;
}

// Return the nth node of a list, or NULL if the list contains fewer than n elements
ListNode* nthNode(ListNode* head, size_t n) {
	if (!head || n == 0 || isEmpty(head)) return NULL;

	size_t count = 1;
	ListNode* cur = head;
	while (cur != NULL && count < n) {
		cur = cur->next;
		count++;
		if (count > MAX_LEN) return NULL;
	}

	if (!cur || !cur->val) return NULL;
	return cur;
}

// Push a value onto the end of the list; 0 = success, -1 = failure
int listPush(ListNode* head, Value* val) {
	if (!head || !val) return -1;

	if (isEmpty(head)) {
		head->val = val;
		return 0;
	}

	ListNode* last = lastNode(head);
	if (!last || !last->val) return -1;

	ListNode* next = constructNode(val);
	if (!next) return -1;
	last->next = next;
	
	return 0;
}

// Pop a value from the end of the list and return its value
Value* listPop(ListNode* head) {
	int len = listLength(head);
	if (len < 1) return NULL;
	return popNthNode(head, len);
}

// Returns a copy of the value of the last node in a list
Value* listPeek(ListNode* head) {
	if (!head || isEmpty(head)) return NULL;
	
	ListNode* last = lastNode(head);
	if (!last || !last->val) return NULL;

	return copyValue(last->val);
}

// Returns a copy of the value of the nth node of a list
Value* listGetNthVal(ListNode* head, size_t n) {
	ListNode* nth = nthNode(head, n);
	if (!nth) return NULL;

	return copyValue(nth->val);
}

// Returns the length of a list; 0 for empty list, -1 on failure
int listLength(ListNode* head) {
	if (!head || isEmpty(head)) return 0;

	int len = 0;
	ListNode* cur = head;
	while (cur != NULL) {
		if (!cur->val) return -1;
		cur = cur->next;
		len++;
		if (len > MAX_LEN) return -1;
	}

	return len;
}


/* ---------- List manipulation ---------- */

// Pop the nth node from a linked list and return its value
Value* popNthNode(ListNode* head, size_t n) {
	if (!head || n == 0 || isEmpty(head)) return NULL;

	if (n == 1) {
		Value* val = head->val;
		if (!head->next) {
			head->val = NULL;
		}
		else {
			ListNode* next = head->next;
			head->val = next->val;
			head->next = next->next;
			freeNodeOnly(next);
		}
		return val;
	}

	ListNode* back = head;
	ListNode* front = head->next;
	size_t count = 2;
	while (front != NULL && count < n) {
		back = front;
		front = front->next;
		count++;
		if (count > MAX_LEN) return NULL;
	}

	if (!front || !front->val) return NULL;

	Value* val = front->val;
	back->next = front->next;
	freeNodeOnly(front);
	return val;
}

// Reverse a linked list
ListNode* reverseList(ListNode* head) {
	int len = listLength(head);
	if (!head || len < 2) return head;
	
	ListNode* prev = NULL;
	ListNode* cur = head;
	while (cur != NULL) {
		ListNode* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}

// Sort a linked list in ascending order
ListNode* sortList(ListNode* head) {
	int len = listLength(head);
	if (!head || len < 2) return head;
	if (!isNumericList(head)) return head;

	return sort(head, len);
}
