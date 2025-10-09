#ifndef RUNTIME_H
#define RUNTIME_H

#include<frame.h>

struct Context{
    int curr_frame;
    int pc; 
    Frame *jvm_stack; //Podría colocar el method area ya que lo uso tanto
};

void execute(struct Context *context);
void executeNative(struct Context *context);

#endif