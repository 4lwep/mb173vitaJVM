#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include<stdint.h>
#include<stdio.h>
#include<malloc.h>

#include "util.h"
#include "heap.h"

typedef struct { // Hay varios tipos de atributos predefinidos. Tal vez tenga que implementarlos en algún lado
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    int info_ptr; //ptr u8
} attribute_info;

int parseAttributes(FILE *bytecode_file, uint16_t attributes_count);

#endif