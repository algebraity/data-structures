#include<stdlib.h>
#include<stddef.h>
#include<limits.h>
#include<math.h>
#include "linked_list.h"


/* ---------- Construct and free methods ---------- */

// Construct a ListNode with a specific value
ListNode* constructNode(int val) {
	ListNode* node = malloc(sizeof(ListNode));
	if (!node) return NULL;
	node->next = NULL;
	node->val = val;
	return node;
}

// Construct a list with a sinle
ListNode* constructList(int* vals, int valSize) {
	if (!vals) return NULL;
	if (valSize < 1) return NULL;

	ListNode* head = constructNode(vals[0]);
	if (!head) return NULL;
	ListNode* cur = head;
	for (int i = 1; i < valSize; i++) {
		ListNode* temp = constructNode(vals[i]);
		if (!temp) freeList(head);
		cur->next = temp;
		temp = cur;
		cur = cur->next;
	}

	return head;
}

// Return an empty list
ListNode* emptyList(void) {
	return NULL;
}

// Free a single ListNode
void freeListNode(ListNode* node) {
	if (!node) return;
	node->next = NULL;
	free(node);
}

// Free a linked list
void freeList(ListNode* head) {
	if (head == NULL) return;
	
	ListNode* cur = head;
	ListNode* next = cur->next;
	while (cur != NULL) {
		next = cur->next;
		freeListNode(cur);
		cur = next;
	}
}


/* ---------- Basic list properties ---------- */

// Return 1 if a list is empty, else 0
int isEmpty(ListNode* head) {
	if (head == NULL) return 1;
	return 0;
}

// Return 1 if a list is non-empty, else 0
int isNonEmpty(ListNode* head) {
	if (isEmpty(head)) return 0;
	return 1;
}

// Return 1 if a list is sorted, else 0
int isSorted(ListNode* head) {
	if (!head) return 0;

	int incPos = 1;
	int decPos = 1;
	ListNode* cur = head;
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
	if (!head) return NULL;
	if (n == 1) return head;
	if (listLength(head) < n) return NULL;

	int count = 1;
	ListNode* cur = head;
	while (count++ < n) {
		cur = cur->next;
	}

	return cur;
}

// Push a value onto the end of the list; 0 = success, -1 = failure
int listPush(ListNode* head, int val) {
	if (!head || val == INT_MIN) return -1;

	ListNode* last = lastNode(head);
	ListNode* next = constructNode(val);
	last->next = next;
	
	return 0;
}

// Pop a value from the end of the list and return its value
int listPop(ListNode* head) {
	if (!head) return INT_MIN;
	
	ListNode* back = head;
	ListNode* front = head->next;
	while (front->next != NULL) {
		back = back->next;
		front = front->next;
	}

	int val = front->val;
	back->next = NULL;
	freeListNode(front);

	return val;
}

// Returns the value of the last node in a list; INT_MIN on error
int listPeek(ListNode* head) {
	if (!head) return INT_MIN;
	
	ListNode* last = lastNode(head);
	int val = last->val;

	return val;
}

// Returns the value of the nth node of a list; INT_MIN on error
int listGetNthVal(ListNode* head, size_t n) {
	if (!head) return INT_MIN;
	if (listLength(head) < n) return INT_MIN;

	ListNode* nth = nthNode(head, n);
	int val = nth->val;

	return val;
}

// Returns the length of a list; 0 for empty list, -1 on failure;
int listLength(ListNode* head) {
	if (!head) return 0;

	int len = 1;
	ListNode* cur = head;
	while (len < MAX_LEN && cur->next != NULL) {
		cur = cur->next;
		len++;
	}

	if (len == MAX_LEN) return -1;
	return len;
}

/* ---------- List manipulation ---------- */

// Remove the nth node from a linked list; 0 = success, -1 = failure
int removeNthNode(ListNode* head, size_t n) {
	if (!head || n == 0) return -1;
	
	if (n == 1) {
		ListNode* newHead = head;
		newHead = head->next;
		freeListNode(head);
		return 1;
	}

	int node = 2;
	ListNode* back = head;
	ListNode* front = head->next;
	while (front->next != NULL) {
		node++;
		back = back->next;
		front = front->next;
	}

	back->next = front->next->next;
	freeListNode(front);

	return 0;
}

// Reverse a linked list; 0 = success, -1 = failure
int reverseList(ListNode* head) {
	if (!head) return -1;
	if (!head->next) return 0;
	if (!head->next->next) {
		ListNode* newHead = head->next->next;
		newHead->next = head->next;
		newHead->next->next = head;
		head->next = NULL;
		head = newHead;
		return 0;
	}
	
	ListNode* ptr1 = NULL;
	ListNode* ptr2 = head;
	ListNode* ptr3 = head->next;

	int count = 1;
	while (ptr3 && count < MAX_LEN) {
		ptr2->next = ptr1;
		ptr1 = ptr2;
		ptr2 = ptr3;
		ptr3 = ptr3->next;
		count++;
	}
	ptr2->next = ptr1;

	head = ptr2;
	return 0;
}

// Helper method for sortList; merges two sorted lists in order
static ListNode* merge(struct ListNode* L, struct ListNode* R) {
    struct ListNode tmp;
    struct ListNode* tail = &tmp;
    tmp.next = NULL;

    while (L != NULL && R != NULL) {
        if (L->val <= R->val) {
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
    return tail;
}

// Helper method for sortList; sorts based on length
static ListNode* sort(struct ListNode* head, size_t len) {
    if (len > 2) {
        size_t newLen = len/2;
        struct ListNode* cur = head;
        for(size_t i = 0; i < newLen-1; i++) {
            cur = cur->next;
        }
        struct ListNode* tmp = cur;
        cur = cur->next;
        tmp->next = NULL;
        return merge(sort(head, newLen), sort(cur, len - newLen));
    }
    if (len == 2) {
        struct ListNode* b = head->next;
        if (b->val < head->val) {
            int tmp = b->val;
            b->val = head->val;
            head->val = tmp;
        }
        return head;
    }
    return head;
}

// Sort a linked list in ascending order; 0 = success, -1 = failure
int sortList(ListNode* head) {
	if (!head) return -1;

	ListNode* cur = head;
    if (head == NULL) return 0;

    size_t len = 1;
    while (cur->next != NULL) {
        cur = cur->next;
        len++;
    }

    sort(head, len);
	return 0;
}

