#include "jvm_preparation.h"

MaHashMap *method_area_hashmap;

struct Context* prepareJVMInit(){
    initHeap();
    method_area_hashmap = calloc(1, sizeof(MaHashMap));
    struct Context *context = malloc(sizeof(struct Context)); //Funcion para crear el contexto
    context->curr_frame = JVM_NULL_PTR;
    context->pc = JVM_NULL_PTR;
    context->exit = FALSE;
    context->jvm_stack = malloc(sizeof(Frame) * MAX_JVM_STACK);

    return context;
}