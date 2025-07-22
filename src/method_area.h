#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include<string.h>
#include<loader.h>

typedef struct{
    uint16_t length;
    int code_array_ptr;
    int method_ptr;
} ExecutableCode;

typedef struct{
    //int class_ptr;
    int constant_pool_ptr;
    uint16_t constant_pool_count;
    int fields_ptr;
    uint16_t fields_count;
    int methods_ptr;
    uint16_t methods_count;
    int code_table_ptr;
} MethodArea;

/*typedef struct {
    uint16_t method_area_count;
    uint16_t method_area_entry_array_ptr;
}MethodArea;*/

int createMethodArea(ClassFile *c);

#endif