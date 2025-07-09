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
            unsigned int name_index;
        } class;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index
        } fieldref;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        } methodref;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        } interfaceMethodref;

        struct{
            unsigned int string_index;
        }string;

        struct{
            unsigned int bytes;
        }integer;

        struct{
            unsigned int bytes;
        }_float;

        struct{
            unsigned int high_bytes;
            unsigned int low_bytes;
        }_long;

        struct{
            unsigned int high_bytes;
            unsigned int low_bytes;
        }_double;

        struct {
            unsigned int name_index;
            unsigned int descriptor_index;
        } nameAndType;

        struct {
            unsigned int length;
            char *text;
        } utf8;
        
        struct{
            unsigned short reference_kind;
            unsigned int reference_index;
        }methodHendle;

        struct{
            unsigned int descriptor_index;
        }methodType;

        struct{
            unsigned int bootstrap_method_attr_index;
            unsigned int name_and_type_index;
        }dynamic;

        struct{
            unsigned int bootstrap_method_attr_index;
            unsigned int name_and_type_index;
        }invokeDynamic;

        struct{
            unsigned int name_index;
        }module;

        struct{
            unsigned int name_index;
        }module;

        struct{
            unsigned int name_index;
        }package;
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