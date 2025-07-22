#include<method_area.h>

int createMethodArea(ClassFile *c){
    int method_area = heapAlloc(sizeof(MethodArea));

    MethodArea *data = (MethodArea*)&heap[method_area];

    data->constant_pool_ptr = c->cp_array_ptr;
    data->constant_pool_count = c->constant_pool_count;
    data->fields_ptr = c->fields_array_ptr;
    data->fields_count = c->fields_count;
    data->methods_count = c->methods_count;
    data->methods_ptr = c->methods_array_ptr;
    
    int code = heapAlloc(sizeof(ExecutableCode) * c->methods_count);
    data->code_table_ptr = code;
    ExecutableCode *exCode = (ExecutableCode*)&heap[data->code_table_ptr];
    method_info *methods = (method_info*)&heap[c->methods_array_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[data->constant_pool_ptr];
   
    for (int i = 0; i < c->methods_count; i++){
        attribute_info *method_attributes = (attribute_info*)&heap[methods[i].attributes_ptr];
        for (int j = 0; j < methods[i].attributes_count; j++){
            char *attribute_name = (char*)&heap[constant_pool[method_attributes[j].attribute_name_index].info.CONSTANT_utf8.text_ptr];
            
            if (!strcmp(attribute_name, "Code")){
                uint8_t *attribute_info = (uint8_t*)&heap[method_attributes[j].info_ptr];

                uint16_t codeLen = ((uint32_t)attribute_info[4] << 24) | ((uint32_t)attribute_info[5] << 16) | ((uint32_t)attribute_info[6] << 8)  |  (uint32_t)attribute_info[7];

                exCode[i].code_array_ptr = heapAlloc(codeLen);
                uint8_t *codeStream = (uint8_t*)&heap[exCode[i].code_array_ptr];

                for (int x = 0; x<codeLen; x++){
                    codeStream[x] = attribute_info[x+8];
                }
                exCode[i].length = codeLen;
                exCode[i].method_ptr = c->methods_array_ptr * i + 1;
            }
        }
    }

    return method_area;
}