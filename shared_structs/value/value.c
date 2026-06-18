#include<stdlib.h>
#include<string.h>
#include "value.h"

// Construct a Value from an int
Value* constructValueFromInt(int data) {
	Value* val = malloc(sizeof(Value));
	if (!val) return NULL;
	val->type = VALUE_INT;
	val->data.intVal = data;
	return val;
}

// Construct a Value from a double
Value* constructValueFromDouble(double data) {
	Value* val = malloc(sizeof(Value));
	if (!val) return NULL;
	val->type = VALUE_DOUBLE;
	val->data.floatVal = data;
	return val;
}

// Construct a Value from a char
Value* constructValueFromChar(char data) {
	Value* val = malloc(sizeof(Value));
	if (!val) return NULL;
	val->type = VALUE_CHAR;
	val->data.charVal = data;
	return val;
}

// Construct a Value from a string
Value* constructValueFromString(char* data) {
	if (!data) return NULL;

	Value* val = malloc(sizeof(Value));
	if (!val) return NULL;

	size_t len = strlen(data);
	val->data.strVal = malloc(len + 1);
	if (!val->data.strVal) {
		free(val);
		return NULL;
	}

	memcpy(val->data.strVal, data, len + 1);
	val->type = VALUE_STRING;
	return val;
}

// Copy a Value
Value* copyValue(Value* value) {
	if (!value) return NULL;

	if (value->type == VALUE_INT) return constructValueFromInt(value->data.intVal);
	if (value->type == VALUE_DOUBLE) return constructValueFromDouble(value->data.floatVal);
	if (value->type == VALUE_CHAR) return constructValueFromChar(value->data.charVal);
	if (value->type == VALUE_STRING) return constructValueFromString(value->data.strVal);

	return NULL;
}

// Free a single Value
void freeValue(Value* val) {
	if (!val) return;
	if (val->type == VALUE_STRING) free(val->data.strVal);
	free(val);
}