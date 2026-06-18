CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -pedantic
BUILD_DIR := build

VALUE_OBJ := $(BUILD_DIR)/shared_structs/value/value.o
LINKED_LIST_OBJ := $(BUILD_DIR)/data_structures/linear/linked_list/linked_list.o
DOUBLY_LINKED_LIST_OBJ := $(BUILD_DIR)/data_structures/linear/doubly_linked_list/doubly_linked_list.o
STACK_OBJ := $(BUILD_DIR)/data_structures/linear/stack/stack.o
QUEUE_OBJ := $(BUILD_DIR)/data_structures/linear/queue/queue.o
DYNAMIC_ARRAY_OBJ := $(BUILD_DIR)/data_structures/linear/dynamic_array/dynamic_array.o
DEQUE_OBJ := $(BUILD_DIR)/data_structures/linear/deque/deque.o

.PHONY: all value linked_list doubly_linked_list stack queue dynamic_array deque clean

all: value linked_list doubly_linked_list stack queue dynamic_array deque

value: $(VALUE_OBJ)

linked_list: $(LINKED_LIST_OBJ)

doubly_linked_list: $(DOUBLY_LINKED_LIST_OBJ)

stack: $(STACK_OBJ)

queue: $(QUEUE_OBJ)

dynamic_array: $(DYNAMIC_ARRAY_OBJ)

deque: $(DEQUE_OBJ)

$(VALUE_OBJ): shared_structs/value/value.c shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LINKED_LIST_OBJ): data_structures/linear/linked_list/linked_list.c data_structures/linear/linked_list/linked_list.h shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DOUBLY_LINKED_LIST_OBJ): data_structures/linear/doubly_linked_list/doubly_linked_list.c data_structures/linear/doubly_linked_list/doubly_linked_list.h shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(STACK_OBJ): data_structures/linear/stack/stack.c data_structures/linear/stack/stack.h shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(QUEUE_OBJ): data_structures/linear/queue/queue.c data_structures/linear/queue/queue.h data_structures/linear/linked_list/linked_list.h shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DYNAMIC_ARRAY_OBJ): data_structures/linear/dynamic_array/dynamic_array.c data_structures/linear/dynamic_array/dynamic_array.h shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEQUE_OBJ): data_structures/linear/deque/deque.c data_structures/linear/deque/deque.h data_structures/linear/doubly_linked_list/doubly_linked_list.h shared_structs/value/value.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
