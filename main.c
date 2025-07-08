#include <stdio.h>
#include<malloc.h>

typedef struct {
    FILE r;
    int err;
} Loader;

typedef struct {
    unsigned short tag;
    union {
        struct {
            unsigned int length;
            char *text;
        } utf8;

        struct {
            unsigned int name_index;
        } class;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        } methodref;

        struct {
            unsigned int name_index;
            unsigned int descriptor_index;
        } nameAndType;

        // Agregar más tags
    } info;
} ConstantPoolEntry;

unsigned int loadU8(FILE *r){
    unsigned char *bytes = malloc(1);
    
    while(!fread(bytes, 1, 1, r));
    
    return bytes[0];
}

unsigned int loadU16(FILE *r){
    unsigned char *bytes = malloc(2);
    
    while(!fread(bytes, 2, 1, r));
    
    return bytes[0] << 8 | bytes[1];
}

unsigned int loadU32(FILE *r){
    unsigned char bytes[4];
    
    while(!fread(bytes, 1, 4, r));
    
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8)  |  bytes[3];
}

unsigned int loadU64(FILE *r){
    unsigned char *bytes = malloc(8);
    
    while(!fread(bytes, 8, 1, r));
    
    return (bytes[0] << 56) | (bytes[1] << 48) |
           (bytes[2] << 40) | (bytes[3] << 32) |
           (bytes[4] << 24) | (bytes[5] << 16) |
           (bytes[6] << 8)  |  bytes[7];
}

int main(){
    FILE *r = fopen("/home/alfre/miniJvm/Add.class","rb");
    unsigned int signature = loadU32(r);
    unsigned int minorVersion = loadU16(r);
    unsigned int majorVersion = loadU16(r);
    unsigned int constantPoolCount = loadU16(r);
    unsigned int firstTag = loadU8(r);

    printf("Signature: ");
    printf("%08x", signature);
    printf("\n");

    printf("Version: ");
    printf("%d.%d", majorVersion, minorVersion);
    printf("\n");

    printf("Constant pool count: ");
    printf("%d", constantPoolCount);
    printf("\n");

    ConstantPoolEntry *constantPool = malloc(sizeof(ConstantPoolEntry) * constantPoolCount - 1);
    /*for (int i = 0; i < constantPoolCount; i++){

    }*/

    printf("First tag: ");
    printf("%d", firstTag);
    printf("\n");

    fclose(r);
}