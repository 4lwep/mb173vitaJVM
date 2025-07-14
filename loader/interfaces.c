#include<stdio.h>
#include<malloc.h>
#include<interfaces.h>

uint16_t interfaceCount;
uint16_t *interface;

void parseInterfaces(FILE *r){
    interfaceCount = loadU16(r);
    interface = malloc(sizeof(uint16_t) * interfaceCount);

    for (int i = 0; i<interfaceCount; i++){
        interface[i] = loadU16(r);
    }
}