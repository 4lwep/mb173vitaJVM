#ifndef INTERFACES_H
#define INTERFACES_H

#include<util.h>
#include<stdint.h>

//Estas variables no las tengo que liberar si las libero desde la structura
extern uint16_t interfaceCount;
extern uint16_t *interface;

void parseInterfaces(FILE *r);

#endif