#include<loader.h>

ClassFile *loadClass(FILE *r){
    ClassFile *parsedClass;
    uint32_t signature = loadU32(r);
    uint16_t minorVersion = loadU16(r);
    uint16_t majorVersion = loadU16(r);
    
    parseConstantPool(r);

    uint16_t accessFlags = loadU16(r);
    uint16_t thisClass = loadU16(r);
    uint16_t superClass = loadU16(r);

    parseInterfaces(r);
    parseFields(r);
    parseMethods(r);
    parseAttributes(r);

    parsedClass = malloc(sizeof(ClassFile));
    parsedClass->constant_pool = malloc(sizeof(ConstantPoolEntry) * constantPoolCount);
    parsedClass->interfaces = malloc(sizeof(uint16_t) * interfaceCount);
    parsedClass->fields = malloc(sizeof(field_info) * fieldsCount);
    parsedClass->methods = malloc(sizeof(method_info) * methodCount);

    parsedClass->magic = signature;
    parsedClass->minor_version = minorVersion;
    parsedClass->major_version = majorVersion;
    parsedClass->constant_pool_count = constantPoolCount;
    parsedClass->constant_pool = constantPool;
    parsedClass->access_flags = accessFlags;
    parsedClass->this_class = thisClass;
    parsedClass->super_class = superClass;
    parsedClass->interfaces_count = interfaceCount;
    parsedClass->interfaces = interface;
    parsedClass->fields_count = fieldsCount;
    parsedClass->fields = fields;
    parsedClass->methods_count = methodCount;
    parsedClass->methods = methods;
    parsedClass->attributes_count = attributesCount;
    parsedClass->attributes = attributes;

    return parsedClass;
}

int freeClassFile(ClassFile *c){
    free(c->constant_pool);
    free(c->interfaces);
    free(c->fields);
    free(c->methods);
    free(c);

    return 1;
}