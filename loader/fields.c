#include<fields.h>

unsigned int fieldsCount;
unsigned int *fields;

void parseFields(FILE *r){
    fieldsCount = loadU16(r);

    fields = malloc(sizeof(unsigned int) * fieldsCount);
}