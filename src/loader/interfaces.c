#include<stdio.h>
#include<malloc.h>

#include "interfaces.h"

int parseInterfaces(FILE *bytecode_file, uint16_t interface_count){
    int interface_ptr = heapAlloc(sizeof(uint16_t) * interface_count);
    uint16_t *interface = (uint16_t*)&heap[interface_ptr];

    for (int i = 0; i<interface_count; i++){
        interface[i] = loadU16(bytecode_file);
    }

    return interface_ptr;
}