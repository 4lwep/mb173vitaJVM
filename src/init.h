#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<thread.h>
#include<loader.h>
#include<method_area.h>

int initMainClass(ClassFile *c);
int initThread();
int initJVM();

extern Thread *thread;

#endif