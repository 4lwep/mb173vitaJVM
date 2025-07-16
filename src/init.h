#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<thread.h>

int initMainClass();
int initHeap();
int initThread();
int initJVM();

extern Thread *thread;
extern Heap *heap;
extern ClassFile *parsedMainClass;


#endif