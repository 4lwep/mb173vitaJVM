#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<loader.h>
#include<method_area.h>
#include<runtime.h>

int initJVM(char* path);

//extern int pc;
extern MaHashMap *ma_hashmap;
//extern Frame** jvmStack;

#endif