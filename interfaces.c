#include<stdio.h>
#include<interfaces.h>
#include<util.h>

void parseInterfaces(FILE *r){
    unsigned int interfacesCount = loadU16(r);

    printf("Interfaces: %d\n", interfacesCount);
}