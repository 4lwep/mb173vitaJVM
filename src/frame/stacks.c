#include "stacks.h"
#include "heap.h"

Slot *createStack(int max_size){
    if (!max_size) return NULL;
    Slot *stack = malloc(sizeof(Slot) * max_size);

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

int stackPush(Slot new_entry, Slot *stack, int *current_stack_entry, int max_stack){
    if (*current_stack_entry + 1 < max_stack){
        *current_stack_entry += 1;
        stack[*current_stack_entry] = new_entry;

        Slot *new_value = &stack[*current_stack_entry];

        return compareSlots(&new_entry, new_value); // Estoy comparando la dirección de newEntry con newValue justo después de asignarlo, siempre va a dar bien. El argumento newEntry tal vez debería ser un puntero 
    }
    return JVM_NULL_PTR;
}

Slot stackPop(Slot *stack, int *current_stack_entry){
    Slot pop_value;
    if (*current_stack_entry > JVM_NULL_PTR) {
        Slot pop_value = stack[*current_stack_entry];
        *current_stack_entry -= 1;
        return pop_value;
    }
    return pop_value;
}