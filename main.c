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

    printf("Signature: ");
    printf("%08x", signature);
    printf("\n");

    printf("Version: ");
    printf("%d.%d -> Java %d", majorVersion, minorVersion, majorVersion - 44);
    printf("\n");

    fclose(r);
}