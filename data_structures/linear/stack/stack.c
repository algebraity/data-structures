#include<stdlib.h>
#include<limits.h>
#include "stack.h"

/* ---------- Methods ---------- */

// Construct a Stack
Stack* constructStack(Value** vals, size_t valsSize) {
    if (!vals && valsSize == 0) return emptyStack();
    if (!vals && valsSize > 0) return NULL;
    if (valsSize > INT_MAX) return NULL;

    Stack* stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = (int)valsSize - 1;
    stack->capacity = 2;
    while (stack->capacity < valsSize) stack->capacity *= 2;

    stack->values = malloc(stack->capacity * sizeof(Value*));
    if (!stack->values) {
        free(stack);
        return NULL;
    }

    for (size_t i = 0; i < valsSize; i++) {
        if (!vals[i]) {
            free(stack->values);
            free(stack);
            return NULL;
        }
    }
    for (size_t i = 0; i < valsSize; i++) {
        stack->values[i] = copyValue(vals[i]);
        if (!stack->values[i]) {
            for (size_t j = 0; j < i; j++) freeValue(stack->values[j]);
            free(stack->values);
            free(stack);
            return NULL;
        }
    }

    return stack;
}

// Construct and return an empty Stack
Stack* emptyStack(void) {
    Stack* stack = malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->values = malloc(sizeof(Value*));
    if (!stack->values) {
        free(stack);
        return NULL;
    }
    
    stack->top = -1;
    stack->capacity = 1;

    return stack;
}

// Free the memory associated with a Stack
void freeStack(Stack* stack) {
    if (!stack) return;
    for (int i = 0; i < stack->top+1; i++) freeValue(stack->values[i]);
    free(stack->values);
    free(stack);
}

// Push a Value onto the Stack; returns 0 for success, -1 for failure
int stackPush(Stack* stack, Value* value) {
    if (!stack) return -1;
    if (!value) return -1;

    Value* newVal = copyValue(value);
    if (!newVal) return -1;

    if ((size_t)(stack->top + 1) == stack->capacity) {
        Value** newValues = realloc(stack->values, 2 * stack->capacity * sizeof(Value*));
        if (!newValues) {
            freeValue(newVal);
            return -1;
        }
        stack->values = newValues;
        stack->capacity *= 2;
    }

    stack->values[++stack->top] = newVal;
    return 0;
}

// Pop a Value from the top of the Stack, removing it and returning a copy of it
Value* stackPop(Stack* stack) {
    if (!stack) return NULL;
    if (stack->top < 0) return NULL;

    Value* val = copyValue(stack->values[stack->top]);
    if (!val) return NULL;
    freeValue(stack->values[stack->top]);
    stack->top--;

    return val;
}

// Get a Value from the top of the Stack without removing it
Value* stackPeek(Stack* stack) {
    if (!stack) return NULL;
    if (stack->top == -1) return NULL;

    Value* val = copyValue(stack->values[stack->top]);

    return val;
}