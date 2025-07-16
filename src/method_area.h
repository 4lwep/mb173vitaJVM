#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include<loader.h>
#include<string.h>

typedef struct{
    ConstantPoolEntry *constantPool;
    uint16_t constant_pool_count;
    field_info *fields;
    uint16_t fields_count;
    method_info *methods;
    uint16_t methods_count;
    ExecutableCode *code_table;
} MethodArea;

typedef struct{
    uint16_t length;
    uint8_t *code;
    method_info *method;
} ExecutableCode;

MethodArea *createMethodArea(ClassFile *c);

#endif