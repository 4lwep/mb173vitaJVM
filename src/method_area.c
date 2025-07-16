#include<method_area.h>

MethodArea *createMethodArea(
    ClassFile *c,
    ConstantPoolEntry *constantPool, 
    uint16_t constant_pool_count, 
    field_info *fields, 
    uint16_t fields_count,
    method_info *methods, 
    uint16_t methods_count
){
    MethodArea *method_area = malloc(sizeof(MethodArea));
    ExecutableCode *code = malloc(sizeof(ExecutableCode) * c->methods_count);

    method_area->constantPool = c->constant_pool;
    method_area->constant_pool_count = c->constant_pool_count;
    method_area->fields = c->fields;
    method_area->fields_count = c->fields_count;
    method_area->methods = c->methods;
    method_area->methods_count = c->methods_count;

    for (int i = 0; i < c->methods_count; i++){
        for (int j = 0; j < c->methods[i].attributes_count; j++){
            if (!strcmp(c->constant_pool[c->methods[i].attributes[j].attribute_name_index].info.CONSTANT_utf8.text, "Code")){
                code[i].code = malloc(c->methods[i].attributes[j].attribute_length);
                memcpy(code[i].code, c->methods[i].attributes[j].info, c->methods[i].attributes[j].attribute_length);
                code[i].length = c->methods[i].attributes[j].attribute_length;
                code[i].method = &c->methods[i];
            }
        }
    }

    method_area->code_table = code;

    return method_area;
}