#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <stdint.h>

typedef struct {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t *info;
} attribute_info;

#endif