#include<stdio.h>
#include<malloc.h>
#include<interfaces.h>

int parseInterfaces(FILE *r, uint16_t interfaceCount){
    int interface_ptr = heapAlloc(sizeof(uint16_t) * interfaceCount);
    uint16_t *interface = (uint16_t*)&heap[interface_ptr];

    for (int i = 0; i<interfaceCount; i++){
        interface[i] = loadU16(r);
    }

    return interface_ptr;
}