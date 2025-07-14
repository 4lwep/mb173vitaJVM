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
}method_info;

extern uint16_t methodCount;
extern method_info *methods;

void parseMethods(FILE *r);