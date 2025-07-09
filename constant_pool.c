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