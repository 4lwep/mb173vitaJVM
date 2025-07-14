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
}method_info;

extern unsigned int methodCount;
extern method_info *methods;

void parseMethods(FILE *r);