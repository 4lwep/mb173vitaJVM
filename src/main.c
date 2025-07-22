#include<stdio.h>
#include<loader.h>
#include<string.h>
#include<init.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>

#include "debugScreen_custom.h"

int main(){
  uint16_t ma = initJVM();

  MethodArea *data = (MethodArea*)&heap[ma];
  ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[data->constant_pool_ptr];
  psvDebugScreenPrintf("Number inside heap %d\n", cp[1].tag);

  psvDebugScreenPrintf("Tamaño de heap ocupado %d\n", heapAlloc(200));

  method_info *me = (method_info*)&heap[data->methods_ptr];
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