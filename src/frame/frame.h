#ifndef FRAME_H
#define FRAME_H

#include<stdint.h>
#include<method_area.h>
#include<string.h>
#include<stacks.h>
#include<init.h>
#include<runtime.h>

#define MAX_JVM_STACK 256

typedef struct{
    Slot *local_stack_ptr;
    Slot *operand_stack_ptr;
    int current_local_stack_entry;
    int current_operand_stack_entry;
    int *pc_ptr;
    int curr_pc_context;
    int method_ptr;
    int method_area_pointer;
    uint8_t isNative;
} Frame;

void initFrame(int ma, int method);
void excuteClinit(int ma);
void initFirstFrame(int ma);
void pushFrame(Frame frame);
Frame popFrame();

extern Frame jvmStack[MAX_JVM_STACK];
extern int curr_frame;

#endif