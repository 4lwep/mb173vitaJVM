#include<init.h>

//int pc = -1;
MaHashMap *method_area_hashmap;
//Frame** jvmStack;

int initJVM(char* bytecode_path){
    initHeap();
    method_area_hashmap = calloc(1, sizeof(MaHashMap));
    struct Context *context = malloc(sizeof(struct Context)); //Funcion para crear el contexto
    context->curr_frame = NULL_PTR;
    context->pc = NULL_PTR;
    context->exit = FALSE;
    context->jvm_stack = malloc(sizeof(Frame) * MAX_JVM_STACK);

    FILE *bytecode_file = fopen(bytecode_path, "rb");
    int method_area = loadClass(bytecode_file, context);

    initFirstFrame(method_area, context);
    
    return method_area;
}