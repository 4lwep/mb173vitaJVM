#include<fields.h>

unsigned int fieldsCount;
field_info *fields;

void parseFields(FILE *r){
    fieldsCount = loadU16(r);

    fields = malloc(sizeof(field_info) * fieldsCount);

    for (int i = 0; i<fieldsCount; i++){
        fields[i].access_flags = loadU16(r);
        fields[i].name_index = loadU16(r);
        fields[i].descriptor_index = loadU16(r);
        fields[i].attributes_count = loadU16(r);

        fields[i].attributes = malloc(sizeof(attribute_info) * fields[i].attributes_count);
        for(int j = 0; j < fields[i].attributes_count; j++){
            fields[i].attributes[j].attribute_name_index = loadU16(r);
            fields[i].attributes[j].attribute_length = loadU32(r);

            fields[i].attributes[j].info = malloc(sizeof(fields[i].attributes[j].attribute_length));
            for (int x = 0; x < fields[i].attributes[j].attribute_length; x++){
                fields[i].attributes[j].info[x] = loadU8(r);
            }
        }
    }
}