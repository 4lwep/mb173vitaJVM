#include<stdio.h>
#include<interfaces.h>

unsigned int interfaceCount;

void parseInterfaces(FILE *r){
    unsigned int interfacesCount = loadU16(r);

    printf("Interfaces: %d\n", interfacesCount);
}