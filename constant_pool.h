typedef struct {
    unsigned short tag;
    union {
        struct {
            unsigned int name_index;
        }_class;

        struct {
            unsigned int class_index;
            unsigned int name_and_type_index;
        }fieldref;

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
        }package;
    } info;
} ConstantPoolEntry;

extern ConstantPoolEntry *constantPool;

void parseConstantPool(FILE *r);