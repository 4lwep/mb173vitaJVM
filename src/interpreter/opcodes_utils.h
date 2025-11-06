#ifndef OPCODES_UTILS_H
#define OPCODES_UTILS_H

#include "frame.h"
#include "runtime.h"

void jumpOpCode(Frame *frame, uint8_t number_of_opcodes);

void nextOpCode(Frame *frame);

Slot createNewSlot(ValueType type, void* value); //Podría estar en el archivo stacks

uint16_t isClassInitialized(char* class_name);

void initializeNewClass(char* class_name, struct Context *context);

void initializeIfNot(char* class_name, struct Context *context);

#endif