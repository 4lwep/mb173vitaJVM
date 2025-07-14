#include<stdio.h>
#include<malloc.h>
#include<util.h>
#include<attributes.h>

typedef struct{
    unsigned int access_flags;
	unsigned int name_index;
    unsigned int descriptor_index;
	unsigned int attributes_count;
    attribute_info *attributes;
}field_info;

//Estas variable to las tengo que liberar si las libero desde la structura
extern unsigned int fieldsCount;
extern field_info *fields;

void parseFields(FILE *r);
