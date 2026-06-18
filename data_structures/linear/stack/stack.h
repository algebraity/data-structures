#ifndef STACK_H
#define STACK_H

#include<stddef.h>
#include "../../../shared_structs/value/value.h"

/* ---------- Definitions of structs ---------- */

typedef struct Stack Stack;

struct Stack {
    Value** values;
    int top;
    size_t capacity;
};

/* ---------- Methods ---------- */
Stack* constructStack(Value** vals, size_t valsSize);
Stack* emptyStack(void);
void freeStack(Stack* stack);
int stackPush(Stack* stack, Value* value);
Value* stackPop(Stack* stack);
Value* stackPeek(Stack* stack);


#endif
