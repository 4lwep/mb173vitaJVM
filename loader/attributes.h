#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include<stdint.h>
#include<stdio.h>
#include<util.h>
#include<malloc.h>

typedef struct {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t *info;
} attribute_info;

extern uint16_t attributesCount;
extern attribute_info *attributes;

void parseAttributes(FILE *r);

#endif