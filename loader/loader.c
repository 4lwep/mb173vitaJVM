#include<stdio.h>
#include<malloc.h>
#include<loader.h>

ClassFile *loadClass(FILE *r){
    ClassFile *parsedClass;
    unsigned int signature = loadU32(r);
    unsigned int minorVersion = loadU16(r);
    unsigned int majorVersion = loadU16(r);
    
    parseConstantPool(r);

    unsigned int accessFlags = loadU16(r);
    unsigned int thisClass = loadU16(r);
    unsigned int superClass = loadU16(r);

    parseInterfaces(r);

    parsedClass = malloc(sizeof(ClassFile));
    parsedClass->constant_pool = malloc(sizeof(ConstantPoolEntry) * constantPoolCount);

    parsedClass->magic = signature;
    parsedClass->minor_version = minorVersion;
    parsedClass->major_version = majorVersion;
    parsedClass->constant_pool_count = constantPoolCount;
    parsedClass->constant_pool = constantPool;
    parsedClass->access_flags = accessFlags;
    parsedClass->this_class = thisClass;
    parsedClass->super_class = superClass;
    parsedClass->interfaces_count = interfaceCount;

    return parsedClass;
}