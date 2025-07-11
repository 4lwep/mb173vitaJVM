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

    switch(constantPool[i].tag){
      case 7:{
        constantPool[i].info.CONSTANT_class.name_index = loadU16(r);
        break;
      }
      case 9:{
        constantPool[i].info.CONSTANT_fieldref.class_index = loadU16(r);
        constantPool[i].info.CONSTANT_fieldref.name_and_type_index = loadU16(r);
        break;
      }
      case 10:{
        constantPool[i].info.CONSTANT_methodref.class_index = loadU16(r);
        constantPool[i].info.CONSTANT_methodref.name_and_type_index = loadU16(r);
        break;
      }
      default: break;
    }
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