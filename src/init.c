#include<init.h>

int initMainClass(ClassFile *c){
    //For minecraft, the main class was libraries/com/mojang/minecraft/b1.7.3/net/minecraft/client/Minecraft.class maybe
    FILE *r = fopen("./test/Add.class","rb");
    if (!r) return 0;
    
    c = loadClass(r);
    
    fclose(r);
    return 1;
}

int initThread(){

    return 1;
}

int initJVM(){
    initHeap();

    ClassFile *parsedMainClass = malloc(sizeof(ClassFile));
    initMainClass(parsedMainClass);

    createMethodArea(parsedMainClass);

    freeClassFile(parsedMainClass);

    return 1;
}