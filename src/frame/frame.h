#ifndef FRAME_H
#define FRAME_H

#include<stdint.h>
#include<string.h>
#include<stacks.h>

#define MAX_JVM_STACK 256

#define STACK_DEFAULT_SIZE 1
#define TRUE 1
#define FALSE 0

typedef struct{
    Slot *local_stack;
    Slot *operand_stack;
    int current_local_stack_entry;
    int current_operand_stack_entry;
    int *pc_ptr;
    int curr_pc_context;
    int method_ptr;
    int method_area_pointer;
    int max_stack;
    int max_locals;
    uint8_t isNative;
} Frame;

struct Context;

void initFrame(int ma, int method, struct Context *context);
void excuteClinit(int ma, struct Context *context);
void initFirstFrame(int ma, struct Context *context);
void pushFrame(Frame frame, Frame *stack, int *curr_frame);
void popFrame(Frame* stack, int *curr_frame);

#endif