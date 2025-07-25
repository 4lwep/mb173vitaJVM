#include<stacks.h>

Slot *createStack(int maxSize){
    Slot *stack = malloc(sizeof(Slot) * maxSize);

    return stack;
}