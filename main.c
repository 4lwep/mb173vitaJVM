#include<stdio.h>
#include<malloc.h>
#include<util.h>
#include<constant_pool.h>

typedef struct {
    FILE r;
    int err;
} Loader;

int main(){
    FILE *r = fopen("/home/alfre/miniJvm/Add.class","rb");
    unsigned int signature = loadU32(r);
    unsigned int minorVersion = loadU16(r);
    unsigned int majorVersion = loadU16(r);
    
    parseConstantPool(r);

    unsigned int accessFlags = loadU16(r);
    unsigned int thisClass = loadU16(r);
    unsigned int superClass = loadU16(r);

    //Debug
    printf("Signature: ");
    printf("%08x", signature);
    printf("\n");

    printf("Version: ");
    printf("%d.%d -> Java %d", majorVersion, minorVersion, majorVersion - 44);
    printf("\n\n");

    printf("Tag: %d, Ref index: %d\n", constantPool[0].tag, constantPool[0].info.CONSTANT_methodref.class_index - 1);
    printf("Tag: %d, Ref index: %d\n", constantPool[1].tag, constantPool[1].info.CONSTANT_class.name_index - 1);
    printf("Tag: %d, text: %s\n\n", constantPool[3].tag, constantPool[3].info.CONSTANT_utf8.text);

    printf("Tag: %d, Ref index: %d\n", constantPool[6].tag, constantPool[6].info.CONSTANT_class.name_index - 1);
    printf("Tag: %d, text: %s\n", constantPool[7].tag, constantPool[7].info.CONSTANT_utf8.text);

    printf("Access flag: 0x%x\n", accessFlags);
    printf("This class: %d\n", thisClass - 1);
    printf("Super class: %d\n", superClass - 1);
    //////

    fclose(r);
}