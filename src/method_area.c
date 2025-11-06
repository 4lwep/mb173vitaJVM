#include "method_area.h"

int createMethodArea(ClassFile *class_file){
    MethodArea *last_ma_data;

    int cur_method_area = heapAlloc(sizeof(MethodArea));
    MethodArea *curr_ma_data = (MethodArea*)&heap[cur_method_area];

    curr_ma_data->constant_pool_ptr = class_file->cp_array_ptr;
    curr_ma_data->constant_pool_count = class_file->constant_pool_count;
    curr_ma_data->fields_ptr = class_file->fields_array_ptr;
    curr_ma_data->fields_count = class_file->fields_count;
    curr_ma_data->methods_count = class_file->methods_count;
    curr_ma_data->methods_ptr = class_file->methods_array_ptr;
    
    int code = heapAlloc(sizeof(ExecutableCode) * class_file->methods_count);
    curr_ma_data->code_table_ptr = code;
    ExecutableCode *exCode = (ExecutableCode*)&heap[curr_ma_data->code_table_ptr];
    method_info *methods = (method_info*)&heap[class_file->methods_array_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[curr_ma_data->constant_pool_ptr];
    
    for (int i = 0; i < class_file->methods_count; i++){
        attribute_info *method_attributes = (attribute_info*)&heap[methods[i].attributes_ptr];
        
        if (methods[i].access_flags & ACC_NATIVE){
            exCode[i].method_ptr = class_file->methods_array_ptr + (sizeof(method_info) * i);
            continue;
        }

        for (int j = 0; j < methods[i].attributes_count; j++){
            char *attribute_name = (char*)&heap[constant_pool[method_attributes[j].attribute_name_index].info.CONSTANT_utf8.text_ptr];

            if (!strcmp(attribute_name, "Code")){
                uint8_t *attribute_info = (uint8_t*)&heap[method_attributes[j].info_ptr];

                exCode[i].max_stack = ((uint16_t)attribute_info[0] << 8) | (uint16_t)attribute_info[1];
                exCode[i].max_locals = ((uint16_t)attribute_info[2] << 8) | (uint16_t)attribute_info[3];
                uint32_t codeLen = ((uint32_t)attribute_info[4] << 24) | ((uint32_t)attribute_info[5] << 16) | ((uint32_t)attribute_info[6] << 8)  |  (uint32_t)attribute_info[7];

                exCode[i].code_array_ptr = heapAlloc(codeLen);
                uint8_t *codeStream = (uint8_t*)&heap[exCode[i].code_array_ptr];

                for (int x = 0; x<codeLen; x++){
                    codeStream[x] = attribute_info[x+8];
                }
                exCode[i].length = codeLen;
                exCode[i].method_ptr = class_file->methods_array_ptr + (sizeof(method_info) * i);
            }
        }
    }

    return cur_method_area;
}

//Chat gpt de aquí para abajo (Esto debería de ir a util o algo pero no creo que aquí esté bien)
unsigned int hash(char* key) {
    unsigned int h = 0;
    while (*key) {
        h = (h * 31) + *key++; // Multiplica por un primo y suma el char
    }
    return h % TABLE_SIZE;
}

void insert(MaHashMap* map, char* key, int value) {
    unsigned int index = hash(key);
    MaHashMapEntry* current = map->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Actualiza si ya existe
            return;
        }
        current = current->next;
    }

    // Si no existe, crea nueva entrada
    MaHashMapEntry* newEntry = malloc(sizeof(MaHashMapEntry));
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->next = map->buckets[index];
    map->buckets[index] = newEntry;
}

int get(MaHashMap* map, char* key) {
    unsigned int index = hash(key);
    MaHashMapEntry* current = map->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    // Si no se encuentra
    return NOT_FOUND; // O algún valor que indique "no encontrado"
}