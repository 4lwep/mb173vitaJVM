#include<util.h>
//#include<loader.h>

typedef struct {
    unsigned short tag;
    union {
        struct {
            unsigned int name_index;
        }CONSTANT_class;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        }CONSTANT_fieldref;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        }CONSTANT_methodref;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        }CONSTANT_interfaceMethodref;

        struct{
            unsigned int string_index;
        }CONSTANT_string;

        struct{
            unsigned int bytes;
        }CONSTANT_integer;

        struct{
            unsigned int bytes;
        }CONSTANT_float;

        struct{
            unsigned int high_bytes;
            unsigned int low_bytes;
        }CONSTANT_long;

        struct{
            unsigned int high_bytes;
            unsigned int low_bytes;
        }CONSTANT_double;

        struct {
            unsigned int name_index;
            unsigned int descriptor_index;
        }CONSTANT_nameAndType;

        struct {
            unsigned int length;
            char *text;
        }CONSTANT_utf8;
    } info;
} ConstantPoolEntry;

extern unsigned int constantPoolCount;
extern ConstantPoolEntry *constantPool;

void parseConstantPool(FILE *r);