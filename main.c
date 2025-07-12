#include<stdio.h>
#include<loader.h>

int main(){
    FILE *r = fopen("/home/alfre/miniJvm/Add.class","rb");
    loadClass(r);

    printf("Signature: ");
    printf("%08x", parsedClass->magic);
    printf("\n");

    printf("Version: ");
    printf("%d.%d -> Java %d", parsedClass->major_version, parsedClass->minor_version, parsedClass->major_version - 44);
    printf("\n\n");

    printf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[0].tag, parsedClass->constant_pool[0].info.CONSTANT_methodref.class_index - 1);
    printf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[1].tag, parsedClass->constant_pool[1].info.CONSTANT_class.name_index - 1);
    printf("Tag: %d, text: %s\n\n", parsedClass->constant_pool[3].tag, parsedClass->constant_pool[3].info.CONSTANT_utf8.text);

    printf("Tag: %d, Ref index: %d\n", parsedClass->constant_pool[6].tag, parsedClass->constant_pool[6].info.CONSTANT_class.name_index - 1);
    printf("Tag: %d, text: %s\n\n", parsedClass->constant_pool[7].tag, parsedClass->constant_pool[7].info.CONSTANT_utf8.text);

    printf("Access flag: 0x%x\n", parsedClass->access_flags);
    printf("This class: %d\n", parsedClass->this_class - 1);
    printf("Super class: %d\n", parsedClass->super_class - 1);

    fclose(r);
}
//gcc -o ./output/main main.c loader/constant_pool.c util.c loader/interfaces.c loader/loader.c -I. -I./loader && ./output/main
//Creo que no es mal momento para hacer un makefile