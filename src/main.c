#include<stdio.h>
#include<loader.h>
#include<string.h>
#include<init.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>

#include "debugScreen_custom.h"

int main(){
    psvDebugScreenInit();

    int ma = initJVM("app0:/Add.class"); //Estoy usando el primer method area para el nodo raíz pero si implemento gabage collection tal vez no sea la mejor idea

    MethodArea *data = (MethodArea*)&heap[ma];
    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[data->constant_pool_ptr];

    ExecutableCode *exCode = (ExecutableCode*)&heap[data->code_table_ptr];
    psvDebugScreenPrintf("max locals %d\n", exCode[0].max_locals);
    psvDebugScreenPrintf("max stack %d\n", exCode[0].max_stack);

    int a = 50 * 1024 *1024;
    psvDebugScreenPrintf("Tamaño de heap ocupado %d/%d\n", heapAlloc(200), a);

    sceKernelDelayThread(10*1000000);

    return 0;
}

/*
java \    
  -Dorg.lwjgl.librarypath=/home/alfre/Downloads/lwjgl-2.9.3/native/linux \
  -cp "/home/alfre/Games/PrismLauncher/libraries/com/mojang/minecraft/b1.7.3/minecraft-b1.7.3-client.jar:\
/home/alfre/Downloads/lwjgl-2.9.3/jar/lwjgl.jar:\
/home/alfre/Downloads/lwjgl-2.9.3/jar/lwjgl_util.jar:\
/home/alfre/Downloads/lwjgl-2.9.3/jar/jinput.jar" \
  net.minecraft.client.Minecraft

*/