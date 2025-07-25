#ifndef INIT_H
#define INIT_H

#include<heap.h>
#include<loader.h>
#include<method_area.h>
#include<frame.h>

int initJVM(char* path);

extern int pc;

#endif