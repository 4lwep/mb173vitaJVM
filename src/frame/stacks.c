#include<stacks.h>
#include<heap.h>

Slot *createStack(int maxSize){
    if (!maxSize) return NULL;
    Slot *stack = malloc(sizeof(Slot) * maxSize);

    return stack;
}

int compareSlots(Slot *slot1, Slot *slot2){ //Principalmente para verificar que dos slots coinciden al meter uno nuevo y verificar que la operación es exitosa
    if (slot1->type == slot2->type && 
        slot1->double_value == slot2->double_value &&
        slot1->float_value == slot2->float_value &&
        slot1->int_value == slot2->int_value &&
        slot1->long_value == slot2->long_value &&
        slot1->ref_value == slot2->ref_value) 
    return 1; else return 0;

}

int stackPush(Slot newEntry, Slot *stack, int *current_stack_entry, int maxStack){
    if (*current_stack_entry + 1 < maxStack){
        *current_stack_entry += 1;
        stack[*current_stack_entry] = newEntry;

        Slot *newValue = &stack[*current_stack_entry];

        return compareSlots(&newEntry, newValue); // Estoy comparando la dirección de newEntry con newValue justo después de asignarlo, siempre va a dar bien. El argumento newEntry tal vez debería ser un puntero 
    }
    return NULL_PTR;
}

Slot stackPop(Slot *stack, int *current_stack_entry){
    if (*current_stack_entry > NULL_PTR) {
        Slot popValue = stack[*current_stack_entry];
        *current_stack_entry -= 1;
        return popValue;
    } 
    Slot fail;
    return fail;
}