#include<attributes.h>

int parseAttributes(FILE *bytecode_file, uint16_t attributes_count){
    int attributes_ptr = heapAlloc(sizeof(attribute_info) * attributes_count);
    attribute_info *attributes = (attribute_info*)&heap[attributes_ptr];

    for (int i = 0; i < attributes_count; i++){
        attributes[i].attribute_name_index = loadU16(bytecode_file);
        attributes[i].attribute_length = loadU32(bytecode_file);

        attributes[i].info_ptr = heapAlloc(attributes[i].attribute_length);
        uint8_t *info = (uint8_t*)&heap[attributes[i].info_ptr];
        for (int j = 0; j < attributes[i].attribute_length; j++){
            info[j] = loadU8(bytecode_file);
        }
    }

    return attributes_ptr;
}