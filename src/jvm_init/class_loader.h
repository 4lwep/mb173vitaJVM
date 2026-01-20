#ifndef CLASS_LOADER_H
#define CLASS_LOADER_H

#include "heap.h"
#include "loader.h"
#include "method_area.h"

int prepareApplicationClassLoader(struct Context *context);
int loadClassLoader(struct Context *context);
void executeClassLoaderClinit();

#endif