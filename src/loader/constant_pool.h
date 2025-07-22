#ifndef CONSTANT_POOL_H
#define CONSTANT_POOL_H

#include<util.h>
#include<stdint.h>
#include<heap.h>

typedef struct {
    uint8_t tag;
    union {
        struct {
            uint16_t name_index;
        }CONSTANT_class;

        struct {
            uint16_t class_index;
            uint16_t name_and_type_index;
        }CONSTANT_fieldref;

        struct {
            uint16_t class_index;
            uint16_t name_and_type_index;
        }CONSTANT_methodref;

        struct {
            uint16_t class_index;
            uint16_t name_and_type_index;
        }CONSTANT_interfaceMethodref;

        struct{
            uint16_t string_index;
        }CONSTANT_string;

        struct{
            uint32_t bytes;
        }CONSTANT_integer;

        struct{
            uint32_t bytes;
        }CONSTANT_float;

        struct{
            uint32_t high_bytes;
            uint32_t low_bytes;
        }CONSTANT_long;

        struct{
            uint32_t high_bytes;
            uint32_t low_bytes;
        }CONSTANT_double;

        struct {
            uint16_t name_index;
            uint16_t descriptor_index;
        }CONSTANT_nameAndType;

        struct {
            uint16_t length;
            uint16_t text_ptr; //puntero
        }CONSTANT_utf8;
    } info;
} ConstantPoolEntry;

uint16_t parseConstantPool(FILE *r, uint16_t entries);

#endif