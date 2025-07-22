#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<thread.h>
#include<loader.h>
#include<method_area.h>
#include<loader.h>

int initThread();
int initJVM(char* path);

extern Thread *thread;

#endif