#include<stdio.h>
#include<loader.h>
#include<string.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>

#include "debugScreen_custom.h"

int main(){
    FILE *r = fopen("app0:/Add.class","rb");
    ClassFile *parsedClass = loadClass(r);

    psvDebugScreenInit();

    psvDebugScreenPrintf("Signature: ");
    psvDebugScreenPrintf("%08x", parsedClass->magic);
    psvDebugScreenPrintf("\n");

    psvDebugScreenPrintf("Version: ");
    psvDebugScreenPrintf("%d.%d -> Java %d", parsedClass->major_version, parsedClass->minor_version, parsedClass->major_version - 44);
    psvDebugScreenPrintf("\n\n");

    psvDebugScreenPrintf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[1].tag, parsedClass->constant_pool[1].info.CONSTANT_methodref.class_index);
    psvDebugScreenPrintf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[2].tag, parsedClass->constant_pool[2].info.CONSTANT_class.name_index);
    psvDebugScreenPrintf("Tag: %d, text: %s\n\n", parsedClass->constant_pool[4].tag, parsedClass->constant_pool[4].info.CONSTANT_utf8.text);

    psvDebugScreenPrintf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[8].tag, parsedClass->constant_pool[8].info.CONSTANT_class.name_index);
    psvDebugScreenPrintf("Tag: %d, text: %s\n\n", parsedClass->constant_pool[10].tag, parsedClass->constant_pool[10].info.CONSTANT_utf8.text);

    psvDebugScreenPrintf("Access flag: 0x%04x\n", parsedClass->access_flags);
    psvDebugScreenPrintf("This class: %d\n", parsedClass->this_class);
    psvDebugScreenPrintf("Super class: %d\n", parsedClass->super_class);

    psvDebugScreenPrintf("Number of interfaces: %d\n", parsedClass->interfaces_count);
    psvDebugScreenPrintf("First interface index: %d\n\n", parsedClass->interfaces[0]);

    psvDebugScreenPrintf("Number of fields: %d\n", parsedClass->fields_count);
    psvDebugScreenPrintf("Number of attr in field 0: %d\n\n", parsedClass->fields[0].attributes_count);
    //printf("Field 0 attr name index: %d\n\n", parsedClass->fields[0].attributes[0].attribute_name_index);

    psvDebugScreenPrintf("Method count: %d\n", parsedClass->methods_count);
    psvDebugScreenPrintf("Second method index: %d\n", parsedClass->methods[1].name_index);
    psvDebugScreenPrintf("Second method name: %s\n\n", parsedClass->constant_pool[17].info.CONSTANT_utf8.text);

    psvDebugScreenPrintf("Attrb count: %d\n", parsedClass->attributes_count);
    psvDebugScreenPrintf("First attrb: %d\n", parsedClass->attributes[0].attribute_name_index);
    psvDebugScreenPrintf("First attribute name: %s\n", parsedClass->constant_pool[21].info.CONSTANT_utf8.text);

    sceKernelDelayThread(10*1000000); // Wait for 3 seconds
    fclose(r);
}
//gcc -o ./output/main main.c loader/constant_pool.c util.c loader/interfaces.c loader/loader.c loader/fields.c loader/method.c loader/attributes.c -I. -I./loader && ./output/main
//Creo que no es mal momento para hacer un makefile

/*
java \    
  -Dorg.lwjgl.librarypath=/home/alfre/Downloads/lwjgl-2.9.3/native/linux \
  -cp "/home/alfre/Games/PrismLauncher/libraries/com/mojang/minecraft/b1.7.3/minecraft-b1.7.3-client.jar:\
/home/alfre/Downloads/lwjgl-2.9.3/jar/lwjgl.jar:\
/home/alfre/Downloads/lwjgl-2.9.3/jar/lwjgl_util.jar:\
/home/alfre/Downloads/lwjgl-2.9.3/jar/jinput.jar" \
  net.minecraft.client.Minecraft

*/