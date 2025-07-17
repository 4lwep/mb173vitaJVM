#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include<loader.h>
#include<string.h>
#include<heap.h>

typedef struct{
    uint16_t length;
    uint16_t code_array_ptr;
    uint16_t method_ptr;
} ExecutableCode;

typedef struct{
    uint16_t constant_pool_ptr;
    uint16_t constant_pool_count;
    uint16_t fields_ptr;
    uint16_t fields_count;
    uint16_t methods_ptr;
    uint16_t methods_count;
    uint16_t code_table_ptr;
} MethodArea;

int createMethodArea(ClassFile *c);

#endif