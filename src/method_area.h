#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include "string.h"
#include "loader.h"

typedef struct{
    uint16_t length;
    int code_array_ptr;
    int method_ptr;
    uint16_t max_stack;
    uint16_t max_locals;
} ExecutableCode;

typedef struct{
    int constant_pool_ptr;
    uint16_t constant_pool_count;
    int fields_ptr;
    uint16_t fields_count;
    int methods_ptr;
    uint16_t methods_count;
    int executable_code_ptr;
    int class_loader_ptr;
} MethodAreaData;

#define TABLE_SIZE 1000

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next; // Para manejar colisiones (encadenamiento)
} MaHashMapEntry;

typedef struct {
    MaHashMapEntry* buckets[TABLE_SIZE]; // Array de listas
} MaHashMap;

int getMethodAreaData(ClassFile *class_file);
unsigned int hash(char* key);
void insert(MaHashMap* map, char* key, int value);
int get(MaHashMap* map, char* key);

#endif