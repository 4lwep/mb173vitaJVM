#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include<string.h>
#include<loader.h>

typedef struct{
    uint16_t length;
    uint16_t code_array_ptr; //ptr uint8_t Tal vez pueda ser un array normal []
    uint16_t method_ptr;
} ExecutableCode;

typedef struct{
    //uint16_t class_ptr;
    uint16_t constant_pool_ptr;
    uint16_t constant_pool_count;
    uint16_t fields_ptr;
    uint16_t fields_count;
    uint16_t methods_ptr;
    uint16_t methods_count;
    uint16_t code_table_ptr;
} MethodArea;

/*typedef struct {
    uint16_t method_area_count;
    uint16_t method_area_entry_array_ptr;
}MethodArea;*/

uint16_t createMethodArea(ClassFile *c);

#endif