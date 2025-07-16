#ifndef THREAD_H
#define THREAD_H

#include<frame.h>
#include<heap.h>

typedef struct{
    int* pc;
    Frame *frame_stack;
    int *heap;
} Thread;

#endif