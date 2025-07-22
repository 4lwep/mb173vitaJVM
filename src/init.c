#include<init.h>

int initMainClass(ClassFile **c){
    //For minecraft, the main class was libraries/com/mojang/minecraft/b1.7.3/net/minecraft/client/Minecraft.class maybe
    FILE *r = fopen("app0:/Add.class","rb");
    if (!r) return 0;
    
    *c = loadClass(r);
    
    fclose(r);
    return 1;
}

int initThread(){

    return 1;
}

uint16_t initJVM(){
    initHeap();

    ClassFile *parsedMainClass;

    initMainClass(&parsedMainClass);

    uint16_t ma = createMethodArea(parsedMainClass);

    free(parsedMainClass);
    
    return ma;
}