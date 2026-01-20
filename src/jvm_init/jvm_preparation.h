#ifndef JVM_PREPARATION_H
#define JVM_PREPARATION_H

#include "class_loader.h"

extern MaHashMap *method_area_hashmap;

struct Context* prepareJVMInit();

#endif