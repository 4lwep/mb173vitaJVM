#include<stdio.h>
#include<malloc.h>
#include<constant_pool.h>
#include<util.h>

ConstantPoolEntry *constantPool;

void parseConstantPool(FILE *r){
  unsigned int constantPoolCount = loadU16(r);

  printf("Constant pool count: ");
  printf("%d", constantPoolCount);
  printf("\n");

  constantPool = malloc(sizeof(ConstantPoolEntry) * constantPoolCount - 1);

  for (int i = 0; i < constantPoolCount; i++){
    unsigned int tag = loadU8(r);
    constantPool[i].tag = tag;
  }
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