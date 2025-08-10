#ifndef STACKS_H
#define STACKS_H

#include<malloc.h>

typedef enum {
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_REF,
    VALUE_DOUBLE,
    VALUE_LONG,
    VALUE_NONE
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_value;
        float float_value;
        int ref_value;     // Índice dentro del heap
        double double_value;
        long long_value;
    };
} Slot;

Slot *createStack(int maxSize);
int stackPush(Slot newEntry, Slot *stack, int *current_operand_stack_entry, int *maxStack);
Slot stackPop(Slot *stack, int *current_operand_stack_entry);

#endif