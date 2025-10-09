#include<loader.h>
#include<method_area.h>
#include<frame.h>
#include<init.h>

ClassFile *parseClass(FILE *bytecode_file){
    ClassFile *parsed_class;
    uint32_t signature = loadU32(bytecode_file);
    uint16_t minor_version = loadU16(bytecode_file);
    uint16_t major_version = loadU16(bytecode_file);
    
    uint16_t constant_pool_count = loadU16(bytecode_file);
    int constant_pool_array_ptr = parseConstantPool(bytecode_file, constant_pool_count);

    uint16_t access_flags = loadU16(bytecode_file);
    uint16_t this_class = loadU16(bytecode_file);
    uint16_t super_class = loadU16(bytecode_file);
    
    uint16_t interface_count = loadU16(bytecode_file);
    int interface_array_ptr = parseInterfaces(bytecode_file, interface_count);

    uint16_t fields_count = loadU16(bytecode_file);
    int fields_array_ptr = parseFields(bytecode_file, fields_count);

    uint16_t method_count = loadU16(bytecode_file);
    int methods_array_ptr = parseMethods(bytecode_file, method_count);

    uint16_t attributes_count = loadU16(bytecode_file);
    int attributes_array_ptr = parseAttributes(bytecode_file, attributes_count);

    parsed_class = malloc(sizeof(ClassFile));

    parsed_class->magic = signature;
    parsed_class->minor_version = minor_version;
    parsed_class->major_version = major_version;
    parsed_class->constant_pool_count = constant_pool_count;
    parsed_class->cp_array_ptr = constant_pool_array_ptr;
    parsed_class->access_flags = access_flags;
    parsed_class->this_class = this_class;
    parsed_class->super_class = super_class;
    parsed_class->interfaces_count = interface_count;
    parsed_class->interface_array_ptr = interface_array_ptr;
    parsed_class->fields_count = fields_count;
    parsed_class->fields_array_ptr = fields_array_ptr;
    parsed_class->methods_count = method_count;
    parsed_class->methods_array_ptr = methods_array_ptr;
    parsed_class->attributes_count = attributes_count;
    parsed_class->attributes_array_ptr = attributes_array_ptr;

    return parsed_class;
}

int loadClass(FILE *bytecode_file, struct Context *context){
    ClassFile *parsed_class;

    parsed_class = parseClass(bytecode_file);

    int method_area = createMethodArea(parsed_class);

    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[parsed_class->cp_array_ptr]  ;
    char *className = (char*)&heap[cp[cp[parsed_class->this_class].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr];
    insert(method_area_hashmap, className, method_area);

    free(parsed_class);

    excuteClinit(method_area, context);
    return method_area;
}