#include<stdio.h>
#include<malloc.h>
#include<util.h>

//Estas variable to las tengo que liberar si las libero desde la structura
extern unsigned int fieldsCount;
extern unsigned int *fields;

void parseFields(FILE *r);
