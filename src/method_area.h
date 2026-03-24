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
    int class_instance_ptr;
} MethodAreaData;

typedef struct {
    char* name;
    union{
        int i; 
        float f; 
        long l; 
        double d; 
        void *ref; 
    };
} StaticValue;

typedef enum {
    BOOTSTRAP,
    APPLICATION
} ClassLoaderType;

typedef struct{
    char *name;
    ClassLoaderType class_loader; //En principio esto debe ser un puntero a una clase de java que represente el classloader, pero ya que es emulado, de momento será un enum
    MethodAreaData *super_class; 
    MethodAreaData **interfaces; 
    int interface_count; 
    //int initialized; //Teniendo el hashmap no se si esto es del todo necesario pero de momento lo dejo. Además se supone que todo va a estar inicializado nada más arrancar así que siempre debería estar todo inicializado
    int instance_size; //Esto será para facilitar ver cuanto ocupa una clase para implementar métodos nativos (supongo)
    StaticValue *static_values;

    // Monitor para synchronized 
    //void *monitor; // puedes usar un mutex, spinlock o lo que quieras <- sugerencia del chatgpt (no se de qué habla)

    MethodAreaData *method_area_entry; //No se qué tan necesario sea pero se supone que me da acceso rápido a la entrada del method area. De momento lo dejaré
} ClassInstance;

#define TABLE_SIZE 1000

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next; // Para manejar colisiones (encadenamiento)
} MaHashMapEntry;

typedef struct {
    MaHashMapEntry* buckets[TABLE_SIZE]; // Array de listas
} MaHashMap;

int getMethodAreaPtr(ClassFile *class_file);
int createClassInstance(char* class_name, ClassLoaderType class_loader, MethodAreaData *super_class, MethodAreaData **interfaces, StaticValue *static_values);

unsigned int hash(char* key);
void insert(MaHashMap* map, char* key, int value);
int get(MaHashMap* map, char* key);

#endif