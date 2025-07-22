#ifndef FIELDS_H
#define FIELDS_H

#include<stdio.h>
#include<malloc.h>
#include<util.h>
#include<attributes.h>
#include<stdint.h>
#include<heap.h>

typedef struct{
    uint16_t access_flags;
	uint16_t name_index;
    uint16_t descriptor_index;
	uint16_t attributes_count;
    int attributes_ptr; //ptr attribute_info
}field_info;

int parseFields(FILE *r, uint16_t fieldsCount);

#endif