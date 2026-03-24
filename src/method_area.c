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
    fprintf(log_file, "getCodeAttribute\n");
    attribute_info *method_attributes = (attribute_info*)&heap[method.attributes_ptr];
    fprintf(log_file, "jiji\n");
    fprintf(log_file, "%d\n", method.attributes_count);

    for (int j = 0; j < method.attributes_count; j++){
        fprintf(log_file, "pre get from heap\n");
        char *attribute_name = (char*)getFromHeap(constant_pool[method_attributes[j].attribute_name_index].info.CONSTANT_utf8.text_ptr);
        fprintf(log_file, "tras get from heap\n");

        if (!strcmp(attribute_name, "Code")){
            fprintf(log_file, "entra al if\n");
            uint8_t *attribute_info = (uint8_t*)&heap[method_attributes[j].info_ptr];
            fprintf(log_file, "otra function\n");
            createExecutableCodeEntry(executableCodeEntry, attribute_info);
            fprintf(log_file, "fin function\n");
            break;
        }
    }
}

static void getCodeFromMethodAreaMethods(int methods_ptr, int methods_count, ConstantPoolEntry *constant_pool, ExecutableCode *exCode){
    fprintf(log_file, "getCodeFromMethodAreaMethods\n");
    method_info *methods = (method_info*)getFromHeap(methods_ptr);
    fprintf(log_file, "get from heap\n");

    for (int i = 0; i < methods_count; i++){
        if (methods[i].access_flags & ACC_NATIVE){
            assignMethodToCode(&exCode[i], methods_ptr + (sizeof(method_info) * i));
            continue;
        }
        
        fprintf(log_file, "%d\n", (uintptr_t)&methods[i] % sizeof(int));
        fprintf(log_file, "%d\n", sizeof(int));
        fprintf(log_file, "%d\n", sizeof(method_info));
        getCodeAttribute(methods[i], constant_pool, &exCode[i]);
        fprintf(log_file, "dos\n");
        assignMethodToCode(&exCode[i], methods_ptr + (sizeof(method_info) * i));
        fprintf(log_file, "tres\n");
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
    fprintf(log_file, "supongo que aquí peta\n");
    getCodeFromMethodAreaMethods(method_area_data->methods_ptr, method_area_data->methods_count, constant_pool, exCode);
    fprintf(log_file, "supongo que esto no lo veo\n");
    
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