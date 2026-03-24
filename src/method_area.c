#include "method_area.h"

static inline void assignMethodToCode(ExecutableCode *exCode, int method_ptr){
    exCode->method_ptr = method_ptr;
}

static void createExecutableCodeEntry(ExecutableCode *executableCodeEntry, uint8_t *attribute_info){
    executableCodeEntry->max_stack = ((uint16_t)attribute_info[0] << 8) | (uint16_t)attribute_info[1];
    executableCodeEntry->max_locals = ((uint16_t)attribute_info[2] << 8) | (uint16_t)attribute_info[3];
        uint32_t codeLen = ((uint32_t)attribute_info[4] << 24) | ((uint32_t)attribute_info[5] << 16) | ((uint32_t)attribute_info[6] << 8)  |  (uint32_t)attribute_info[7];

    executableCodeEntry->code_array_ptr = heapAlloc(codeLen);
    uint8_t *codeStream = (uint8_t*)getFromHeap(executableCodeEntry->code_array_ptr);

    for (int x = 0; x<codeLen; x++){
        codeStream[x] = attribute_info[x+8];
    }
    executableCodeEntry->length = codeLen;
}

static void getCodeAttribute(method_info method, ConstantPoolEntry *constant_pool, ExecutableCode *executableCodeEntry){
    attribute_info *method_attributes = (attribute_info*)&heap[method.attributes_ptr];

    for (int j = 0; j < method.attributes_count; j++){
        char *attribute_name = (char*)getFromHeap(constant_pool[method_attributes[j].attribute_name_index].info.CONSTANT_utf8.text_ptr);

        if (!strcmp(attribute_name, "Code")){
            uint8_t *attribute_info = (uint8_t*)&heap[method_attributes[j].info_ptr];
            createExecutableCodeEntry(executableCodeEntry, attribute_info);
            break;
        }
    }
}

static void getCodeFromMethodAreaMethods(int methods_ptr, int methods_count, ConstantPoolEntry *constant_pool, ExecutableCode *exCode){
    method_info *methods = (method_info*)getFromHeap(methods_ptr);

    for (int i = 0; i < methods_count; i++){
        if (methods[i].access_flags & ACC_NATIVE){
            assignMethodToCode(&exCode[i], methods_ptr + (sizeof(method_info) * i));
            continue;
        }

        getCodeAttribute(methods[i], constant_pool, &exCode[i]);
        assignMethodToCode(&exCode[i], methods_ptr + (sizeof(method_info) * i));
    }
}

int getMethodAreaPtr(ClassFile *class_file){
    int new_method_area_ptr = heapAlloc(sizeof(MethodAreaData));
    MethodAreaData *method_area_data = (MethodAreaData*)getFromHeap(new_method_area_ptr);

    method_area_data->constant_pool_ptr = class_file->cp_array_ptr;
    method_area_data->constant_pool_count = class_file->constant_pool_count;
    method_area_data->fields_ptr = class_file->fields_array_ptr; //En lugar de crear un puntero a los campos de la clase, puedo usar fields_ptr para crear el ClassInstance nada más. esto de todas formas lo podría dejar 
    method_area_data->fields_count = class_file->fields_count;
    method_area_data->methods_count = class_file->methods_count;
    method_area_data->methods_ptr = class_file->methods_array_ptr;

    method_area_data->executable_code_ptr = heapAlloc(sizeof(ExecutableCode) * class_file->methods_count);

    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)getFromHeap(method_area_data->constant_pool_ptr);
    ExecutableCode *exCode = (ExecutableCode*)getFromHeap(method_area_data->executable_code_ptr);
    getCodeFromMethodAreaMethods(method_area_data->methods_ptr, method_area_data->methods_count, constant_pool, exCode);
    
    return new_method_area_ptr;
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