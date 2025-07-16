#ifndef FRAME_H
#define FRAME_H

typedef struct{
    int *local_var;
    int *operand_stack;
    int pc;
} Frame;

#endif