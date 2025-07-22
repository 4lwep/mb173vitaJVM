#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<thread.h>
#include<loader.h>
#include<method_area.h>

int initMainClass(ClassFile **c, FILE *r);
int initThread();
uint16_t initJVM(char* path);

extern Thread *thread;

#endif