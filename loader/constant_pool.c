#include<stdio.h>
#include<malloc.h>
#include<constant_pool.h>

unsigned int constantPoolCount;
ConstantPoolEntry *constantPool;

void parseConstantPool(FILE *r){
  unsigned int constantPoolCount = loadU16(r);

  printf("Constant pool count: ");
  printf("%d", constantPoolCount);
  printf("\n");

  constantPool = malloc(sizeof(ConstantPoolEntry) * (constantPoolCount - 1));

  for (int i = 0; i < constantPoolCount; i++){
    if(!i) continue;
    unsigned int tag = loadU8(r);
    //Debug
    printf("%d ", i);
    printf("Tag: %d\n", tag);
    ///////
    constantPool[i].tag = tag;

    switch(constantPool[i].tag){
      case 7:{ //class
        constantPool[i].info.CONSTANT_class.name_index = loadU16(r);
        break;
      }
      case 9:{ //fieldref
        constantPool[i].info.CONSTANT_fieldref.class_index = loadU16(r);
        constantPool[i].info.CONSTANT_fieldref.name_and_type_index = loadU16(r);
        break;
      }
      case 10:{ //methodref
        constantPool[i].info.CONSTANT_methodref.class_index = loadU16(r);
        constantPool[i].info.CONSTANT_methodref.name_and_type_index = loadU16(r);
        break;
      }
      case 11:{ //interfaceMethodref
        constantPool[i].info.CONSTANT_interfaceMethodref.class_index = loadU16(r);
        constantPool[i].info.CONSTANT_interfaceMethodref.name_and_type_index = loadU16(r);
        break;
      }
      case 8:{ //string
        constantPool[i].info.CONSTANT_string.string_index = loadU16(r);
        break;
      }
      case 3:{ //integer
        constantPool[i].info.CONSTANT_integer.bytes = loadU32(r);
        break;
      }
      case 4:{ //float --- Hay que hacer algunas cosas aún
        constantPool[i].info.CONSTANT_float.bytes = loadU32(r);
        break;
      }
      case 5:{ //long
        constantPool[i].info.CONSTANT_long.high_bytes = loadU32(r);
        constantPool[i].info.CONSTANT_long.low_bytes = loadU32(r);
        i++;
        break;
      }
      case 6:{ //double --- Falta especificar algunos casos como con los float
        constantPool[i].info.CONSTANT_double.high_bytes = loadU32(r);
        constantPool[i].info.CONSTANT_double.low_bytes = loadU32(r);
        i++;
        break;
      }
      case 12:{ //nameAndType
        constantPool[i].info.CONSTANT_nameAndType.name_index = loadU16(r);
        constantPool[i].info.CONSTANT_nameAndType.descriptor_index = loadU16(r);
        break;
      }
      case 1: { //utf8
        constantPool[i].info.CONSTANT_utf8.length = loadU16(r);
        constantPool[i].info.CONSTANT_utf8.text = malloc(sizeof(char) * (constantPool[i].info.CONSTANT_utf8.length + 1));
        for (int j = 0; j<constantPool[i].info.CONSTANT_utf8.length; j++){
          constantPool[i].info.CONSTANT_utf8.text[j] = loadU8(r);
        }
        break;
      }
      default: break;
    }
  }
}