#include<stdio.h>
#include<constant_pool.h>
#include<interfaces.h>
#include<fields.h>
#include<util.h>
#include<method.h>
#include<malloc.h>
#include<attributes.h>
#include<stdint.h>

typedef struct {
    FILE r;
    int err;
} Loader;

typedef struct {
    uint32_t magic;
    uint16_t minor_version;
	uint16_t major_version;
    uint16_t constant_pool_count;
	ConstantPoolEntry *constant_pool;
    uint16_t access_flags;
	uint16_t this_class;
    uint16_t super_class;
	uint16_t interfaces_count;
    uint16_t *interfaces;
	uint16_t fields_count;
    field_info *fields;
	uint16_t methods_count;
    method_info *methods;
	uint16_t attributes_count;
    attribute_info *attributes;
}ClassFile;

ClassFile *loadClass(FILE *r);