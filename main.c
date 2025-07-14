#include<stdio.h>
#include<loader.h>

int main(){
    FILE *r = fopen("./test/Add.class","rb");
    ClassFile *parsedClass = loadClass(r);

    printf("Signature: ");
    printf("%08x", parsedClass->magic);
    printf("\n");

    printf("Version: ");
    printf("%d.%d -> Java %d", parsedClass->major_version, parsedClass->minor_version, parsedClass->major_version - 44);
    printf("\n\n");

    printf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[0].tag, parsedClass->constant_pool[0].info.CONSTANT_methodref.class_index);
    printf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[1].tag, parsedClass->constant_pool[1].info.CONSTANT_class.name_index);
    printf("Tag: %d, text: %s\n\n", parsedClass->constant_pool[3].tag, parsedClass->constant_pool[3].info.CONSTANT_utf8.text);

    printf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[6].tag, parsedClass->constant_pool[6].info.CONSTANT_class.name_index);
    printf("Tag: %d, text: %s\n\n", parsedClass->constant_pool[7].tag, parsedClass->constant_pool[7].info.CONSTANT_utf8.text);

    printf("Access flag: 0x%04x\n", parsedClass->access_flags);
    printf("This class: %d\n", parsedClass->this_class);
    printf("Super class: %d\n", parsedClass->super_class);

    printf("Number of interfaces: %d\n", parsedClass->interfaces_count);
    printf("First interface index: %d\n\n", parsedClass->interfaces[0]);

    printf("Number of fields: %d\n", parsedClass->fields_count);
    printf("Number of attr in field 0: %d\n\n", parsedClass->fields[0].attributes_count);
    //printf("Field 0 attr name index: %d\n\n", parsedClass->fields[0].attributes[0].attribute_name_index);

    printf("Method count: %d\n", parsedClass->methods_count);
    printf("Second method index: %d\n", parsedClass->methods[1].name_index);
    printf("Second method name: %s\n\n", parsedClass->constant_pool[17].info.CONSTANT_utf8.text);

    printf("Attrb count: %d\n", parsedClass->attributes_count);
    printf("First attrb: %d\n", parsedClass->attributes[0].attribute_name_index);
    printf("First attribute name: %s\n", parsedClass->constant_pool[21].info.CONSTANT_utf8.text);
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