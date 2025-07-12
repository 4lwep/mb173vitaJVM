#include<stdio.h>
#include<malloc.h>
#include<interfaces.h>

unsigned int interfaceCount;
unsigned int *interface;

void parseInterfaces(FILE *r){
    interfaceCount = loadU16(r);
    interface = malloc(sizeof(unsigned int) * interfaceCount);

    for (int i = 0; i<interfaceCount; i++){
        interface[i] = loadU16(r);
    }
}