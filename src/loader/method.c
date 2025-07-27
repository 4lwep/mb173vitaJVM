#include<method.h>

int parseMethods(FILE *r, uint16_t methodCount){
    int methods_ptr = heapAlloc(sizeof(method_info) * methodCount);
    method_info *methods = (method_info*)&heap[methods_ptr];

    for (int i = 0; i < methodCount; i++){
        methods[i].access_flags = loadU16(r);
        methods[i].name_index = loadU16(r);
        methods[i].descriptor_index = loadU16(r);
        methods[i].attributes_count = loadU16(r);

        methods[i].attributes_ptr = heapAlloc(sizeof(attribute_info) * methods[i].attributes_count);
        attribute_info *attribute = (attribute_info*)&heap[methods[i].attributes_ptr];

        for(int j = 0; j < methods[i].attributes_count; j++){
            attribute[j].attribute_name_index = loadU16(r);
            attribute[j].attribute_length = loadU32(r);

            attribute[j].info_ptr = heapAlloc(attribute[j].attribute_length);
            uint8_t *info = (uint8_t*)&heap[attribute[j].info_ptr];

            for (int x = 0; x < attribute[j].attribute_length; x++){
                info[x] = loadU8(r);
            }
        }
    }

    return methods_ptr;
}