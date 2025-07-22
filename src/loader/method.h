#ifndef METHOD_H
#define METHOD_H

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
	uint16_t attributes_ptr; //ptr attribute_info
}method_info;

uint16_t parseMethods(FILE *r, uint16_t methodCount);

#endif