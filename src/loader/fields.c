#include<fields.h>

int parseFields(FILE *bytecode_file, uint16_t fields_count){
    int fields_ptr = heapAlloc(sizeof(field_info) * fields_count);
    field_info *fields = (field_info*)&heap[fields_ptr];

    for (int i = 0; i<fields_count; i++){
        fields[i].access_flags = loadU16(bytecode_file);
        fields[i].name_index = loadU16(bytecode_file);
        fields[i].descriptor_index = loadU16(bytecode_file);
        fields[i].attributes_count = loadU16(bytecode_file);

        fields[i].attributes_ptr = heapAlloc(sizeof(attribute_info) * fields[i].attributes_count);
        attribute_info *attribute = (attribute_info*)&heap[fields[i].attributes_ptr];

        for(int j = 0; j < fields[i].attributes_count; j++){
            attribute[j].attribute_name_index = loadU16(bytecode_file);
            attribute[j].attribute_length = loadU32(bytecode_file);

            attribute[j].info_ptr = heapAlloc(attribute[j].attribute_length);
            uint8_t *info = (uint8_t*)&heap[attribute[j].info_ptr];
            for (int x = 0; x < attribute[j].attribute_length; x++){
                info[x] = loadU8(bytecode_file);
            }
        }
    }

    return fields_ptr;
}