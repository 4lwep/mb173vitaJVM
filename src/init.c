#include<init.h>

ClassFile *parsedMainClass;
MethodArea *MainClassMethodArea;

int initMainClass(){
    //For minecraft, the main class was libraries/com/mojang/minecraft/b1.7.3/net/minecraft/client/Minecraft.class maybe
    FILE *r = fopen("app0:/Add.class","rb");
    if (!r) return 0;
    
    parsedMainClass = loadClass(r);
    
    fclose(r);
    return 1;
}

int initMethodArea(){
    MainClassMethodArea = createMethodArea(parsedMainClass);
    return 1;
}

int initThread(){

    return 1;
}

int initJVM(){
    initHeap();

    return 1;
}