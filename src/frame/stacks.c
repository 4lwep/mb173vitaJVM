#include<stacks.h>
#include<heap.h>

Slot *createStack(int maxSize){
    if (!maxSize) return NULL;
    Slot *stack = malloc(sizeof(Slot) * maxSize);

    return stack;
}

int compareSlots(Slot *slot1, Slot *slot2){
    if (slot1->type == slot2->type && 
        slot1->double_value == slot2->double_value &&
        slot1->float_value == slot2->float_value &&
        slot1->int_value == slot2->int_value &&
        slot1->long_value == slot2->long_value &&
        slot1->ref_value == slot2->ref_value) 
    return 1; else return 0;

}

int stackPush(Slot newEntry, Slot *stack, int *current_operand_stack_entry){
    *current_operand_stack_entry += 1;
    stack[*current_operand_stack_entry] = newEntry;

    Slot *newValue = &stack[*current_operand_stack_entry];

    return compareSlots(&newEntry, newValue);
}

Slot stackPop(Slot *stack, int *current_operand_stack_entry){
    if (*current_operand_stack_entry > -1) {
        Slot popValue = stack[*current_operand_stack_entry];
        *current_operand_stack_entry -= 1;
        fprintf(log_file, "Curr op stack after pop %d\n", *current_operand_stack_entry);
        return popValue;
    } 
    Slot fail;
    return fail;
}