#include<attributes.h>

uint16_t attributesCount;
attribute_info *attributes;

void parseAttributes(FILE *r){
    attributesCount = loadU16(r);

    attributes = malloc(sizeof(attribute_info) * attributesCount);
    for (int i = 0; i < attributesCount; i++){
        attributes[i].attribute_name_index = loadU16(r);
        attributes[i].attribute_length = loadU32(r);

        attributes[i].info = malloc(attributes[i].attribute_length);
        for (int j = 0; j < attributes[i].attribute_length; j++){
            attributes[i].info[j] = loadU8(r);
        }
    }
}