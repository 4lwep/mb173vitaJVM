#include<loader.h>
#include<method_area.h>
#include<frame.h>
#include<init.h>

ClassFile *parseClass(FILE *r){
    ClassFile *parsedClass;
    uint32_t signature = loadU32(r);
    uint16_t minorVersion = loadU16(r);
    uint16_t majorVersion = loadU16(r);
    
    uint16_t constantPoolCount = loadU16(r);
    int cp_array_ptr = parseConstantPool(r, constantPoolCount);

    uint16_t accessFlags = loadU16(r);
    uint16_t thisClass = loadU16(r);
    uint16_t superClass = loadU16(r);
    
    uint16_t interfaceCount = loadU16(r);
    int interface_array_ptr = parseInterfaces(r, interfaceCount);

    uint16_t fieldsCount = loadU16(r);
    int fields_array_ptr = parseFields(r, fieldsCount);

    uint16_t methodCount = loadU16(r);
    int methods_array_ptr = parseMethods(r, methodCount);

    uint16_t attributesCount = loadU16(r);
    int attributes_array_ptr = parseAttributes(r, attributesCount);

    parsedClass = malloc(sizeof(ClassFile));

    parsedClass->magic = signature;
    parsedClass->minor_version = minorVersion;
    parsedClass->major_version = majorVersion;
    parsedClass->constant_pool_count = constantPoolCount;
    parsedClass->cp_array_ptr = cp_array_ptr;
    parsedClass->access_flags = accessFlags;
    parsedClass->this_class = thisClass;
    parsedClass->super_class = superClass;
    parsedClass->interfaces_count = interfaceCount;
    parsedClass->interface_array_ptr = interface_array_ptr;
    parsedClass->fields_count = fieldsCount;
    parsedClass->fields_array_ptr = fields_array_ptr;
    parsedClass->methods_count = methodCount;
    parsedClass->methods_array_ptr = methods_array_ptr;
    parsedClass->attributes_count = attributesCount;
    parsedClass->attributes_array_ptr = attributes_array_ptr;

    return parsedClass;
}

int loadClass(FILE *r, struct Context *context){
    ClassFile *parsedClass;

    parsedClass = parseClass(r);

    int ma = createMethodArea(parsedClass);

    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[parsedClass->cp_array_ptr]  ;
    char *className = (char*)&heap[cp[cp[parsedClass->this_class].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr];
    insert(ma_hashmap, className, ma);

    free(parsedClass);

    excuteClinit(ma, context);
    return ma;
}