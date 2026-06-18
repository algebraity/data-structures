#ifndef VALUE_H
#define VALUE_H

#include<stddef.h>

/* ---------- Definitions of structs ----------- */

typedef struct Value Value;

typedef enum {
	VALUE_INT,
	VALUE_DOUBLE,
	VALUE_CHAR,
	VALUE_STRING
} ValueType;

struct Value {
	union {
		int intVal;
		double floatVal;
		char charVal;
		char* strVal;
	} data;
	ValueType type;
};

/* ---------- Methods ---------- */
Value* constructValueFromInt(int data);
Value* constructValueFromDouble(double data);
Value* constructValueFromChar(char data);
Value* constructValueFromString(char* data);
Value* copyValue(Value* value);
void freeValue(Value* value);

#endif