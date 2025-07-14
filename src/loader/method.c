#include<method.h>

uint16_t methodCount;
method_info *methods;

void parseMethods(FILE *r){
    methodCount = loadU16(r);

    methods = malloc(sizeof(method_info) * methodCount);
    for (int i = 0; i < methodCount; i++){
        methods[i].access_flags = loadU16(r);
        methods[i].name_index = loadU16(r);
        methods[i].descriptor_index = loadU16(r);
        methods[i].attributes_count = loadU16(r);

        methods[i].attributes = malloc(sizeof(attribute_info) * methods[i].attributes_count);
        for (int j = 0; j < methods[i].attributes_count; j++){
            methods[i].attributes[j].attribute_name_index = loadU16(r);
            methods[i].attributes[j].attribute_length = loadU32(r);

            methods[i].attributes[j].info = malloc(methods[i].attributes[j].attribute_length);
            for (int x = 0; x < methods[i].attributes[j].attribute_length; x++){
                methods[i].attributes[j].info[x] = loadU8(r);
            }
        }
    }
}