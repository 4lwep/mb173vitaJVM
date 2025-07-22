#include<init.h>

int initMainClass(ClassFile **c, FILE *r){
    if (!r) return 0;
    
    *c = loadClass(r);
    
    fclose(r);
    return 1;
}

int initThread(){

    return 1;
}

uint16_t initJVM(char* path){
    initHeap();

    FILE *r = fopen(path, "rb");
    ClassFile *parsedMainClass;

    initMainClass(&parsedMainClass, r);

    uint16_t ma = createMethodArea(parsedMainClass);

    free(parsedMainClass);
    
    return ma;
}