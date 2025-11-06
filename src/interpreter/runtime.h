#ifndef RUNTIME_H
#define RUNTIME_H

#include<opcodes.h>

struct Context{
    int curr_frame;
    int pc; 
    int exit;
    Frame *jvm_stack; //Podría colocar el method area ya que lo uso tanto
};

void execute(struct Context *context);
void executeNative(struct Context *context);

#endif