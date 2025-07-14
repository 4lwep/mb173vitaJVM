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
    unsigned int magic;
    unsigned int minor_version;
	unsigned int major_version;
    unsigned int constant_pool_count;
	ConstantPoolEntry *constant_pool;
    unsigned int access_flags;
	unsigned int this_class;
    unsigned int super_class;
	unsigned int interfaces_count;
    unsigned int *interfaces;
	unsigned int fields_count;
    field_info *fields;
	unsigned int methods_count;
    method_info *methods;
	unsigned int attributes_count;
    attribute_info *attributes;
}ClassFile;

ClassFile *loadClass(FILE *r);