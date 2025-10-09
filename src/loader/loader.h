#ifndef LOADER_H
#define LOADER_H

#include<stdio.h>
#include<constant_pool.h>
#include<interfaces.h>
#include<fields.h>
#include<util.h>
#include<method.h>
#include<malloc.h>
#include<attributes.h>
#include<stdint.h>
#include<runtime.h>

typedef struct {
    uint32_t magic;
    uint16_t minor_version;
	uint16_t major_version;
    uint16_t constant_pool_count;
	int cp_array_ptr; //ptr constantPoolEntry
    uint16_t access_flags;
	uint16_t this_class;
    uint16_t super_class;
	uint16_t interfaces_count;
    int interface_array_ptr; //ptr uint16_t
	uint16_t fields_count;
    int fields_array_ptr; //ptr field_info
	uint16_t methods_count;
    int methods_array_ptr; //ptr method_info
	uint16_t attributes_count;
    int attributes_array_ptr; //ptr attribute_info
}ClassFile;

ClassFile *parseClass(FILE *bytecode_file);
int loadClass(FILE *bytecode_file, struct Context *context);

#endif