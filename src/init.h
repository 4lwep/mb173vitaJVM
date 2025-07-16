#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<thread.h>
#include<loader.h>
#include<method_area.h>

int initMainClass();
int initMethodArea();
int initHeap();
int initThread();
int initJVM();

extern ClassFile *parsedMainClass;
extern MethodArea *MainClassMethodArea;
extern Heap *heap;
extern Thread *thread;

#endif