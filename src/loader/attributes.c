#include<attributes.h>

uint16_t parseAttributes(FILE *r, uint16_t attributesCount){
    uint16_t attributes_ptr = heapAlloc(sizeof(attribute_info) * attributesCount);
    attribute_info *attributes = (attribute_info*)&heap[attributes_ptr];

    for (int i = 0; i < attributesCount; i++){
        attributes[i].attribute_name_index = loadU16(r);
        attributes[i].attribute_length = loadU32(r);

        attributes[i].info_ptr = heapAlloc(attributes[i].attribute_length);
        uint8_t *info = (uint8_t*)&heap[attributes[i].info_ptr];
        for (int j = 0; j < attributes[i].attribute_length; j++){
            info[j] = loadU8(r);
        }
    }

    return attributes_ptr;
}