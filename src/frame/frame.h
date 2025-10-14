#ifndef FRAME_H
#define FRAME_H

#include<stdint.h>
#include<string.h>
#include<stacks.h>

#define MAX_JVM_STACK 256

#define STACK_DEFAULT_SIZE 1

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
    uint8_t is_native;
} Frame;

struct Context;

void initFrame(int maframe_method_area, int frame_method, struct Context *frame_context);
void excuteClinit(int method_area, struct Context *context);
void initFirstFrame(int method_area, struct Context *context);
void pushFrame(Frame frame, Frame *stack, int *current_frame);
void popFrame(Frame* stack, int *current_frame);

#endif