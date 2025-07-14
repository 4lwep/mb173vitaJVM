#include<stdio.h>
#include<malloc.h>
#include<util.h>
#include<attributes.h>
#include<stdint.h>

typedef struct{
    uint16_t access_flags;
	uint16_t name_index;
    uint16_t descriptor_index;
	uint16_t attributes_count;
    attribute_info *attributes;
}field_info;

//Estas variable to las tengo que liberar si las libero desde la structura
extern uint16_t fieldsCount;
extern field_info *fields;

void parseFields(FILE *r);
