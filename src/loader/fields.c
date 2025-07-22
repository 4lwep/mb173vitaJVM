#include<fields.h>

uint16_t parseFields(FILE *r, uint16_t fieldsCount){
    uint16_t fields_ptr = heapAlloc(sizeof(field_info) * fieldsCount);
    field_info *fields = (field_info*)&heap[fields_ptr];

    for (int i = 0; i<fieldsCount; i++){
        fields[i].access_flags = loadU16(r);
        fields[i].name_index = loadU16(r);
        fields[i].descriptor_index = loadU16(r);
        fields[i].attributes_count = loadU16(r);

        fields[i].attributes_ptr = heapAlloc(sizeof(attribute_info) * fields[i].attributes_count);
        attribute_info *attribute = (attribute_info*)&heap[fields[i].attributes_ptr];

        for(int j = 0; j < fields[i].attributes_count; j++){
            attribute[j].attribute_name_index = loadU16(r);
            attribute[j].attribute_length = loadU32(r);

            attribute[j].info_ptr = heapAlloc(attribute[j].attribute_length);
            uint8_t *info = (uint8_t*)&heap[attribute[j].info_ptr];
            for (int x = 0; x < attribute[j].attribute_length; x++){
                info[x] = loadU8(r);
            }
        }
    }

    return fields_ptr;
}