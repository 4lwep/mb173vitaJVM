#ifndef RUNTIME_H
#define RUNTIME_H

#include<frame.h>

struct Context{
    int curr_frame;
    int pc; 
    Frame *jvmStack;
};

void execute(struct Context *context);
void executeNative(struct Context *context);

#endif