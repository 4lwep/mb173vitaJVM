#ifndef INTERFACES_H
#define INTERFACES_H

#include<util.h>
#include<stdint.h>
#include<heap.h>

int parseInterfaces(FILE *bytecode_file, uint16_t interface_count);

#endif