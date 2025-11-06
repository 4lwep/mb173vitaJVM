#ifndef METHOD_H
#define METHOD_H

#include<stdio.h>
#include<malloc.h>
#include<stdint.h>

#include "util.h"
#include "attributes.h"
#include "heap.h"

#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL 0x0010
#define ACC_SYNCHRONIZED 0x0020
#define ACC_NATIVE 0x0100
#define ACC_ABSTRACT 0x0400
#define ACC_STRICT 0x0800

typedef struct{
    uint16_t access_flags;
	uint16_t name_index;
    uint16_t descriptor_index;
	uint16_t attributes_count;
	int attributes_ptr; //ptr attribute_info
}method_info;

int parseMethods(FILE *bytecode_file, uint16_t method_count);

#endif