#include<init.h>

//int pc = -1;
MaHashMap *ma_hashmap;
//Frame** jvmStack;

int initJVM(char* path){
    initHeap();
    ma_hashmap = calloc(1, sizeof(MaHashMap));
    struct Context *context = malloc(sizeof(struct Context));
    context->curr_frame = NULL_PTR;
    context->pc = NULL_PTR;
    context->jvmStack = malloc(sizeof(Frame) * MAX_JVM_STACK);

    FILE *r = fopen(path, "rb");
    int ma = loadClass(r, context);

    initFirstFrame(ma, context);
    
    return ma;
}