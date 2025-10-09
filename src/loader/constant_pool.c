#include<stdio.h>
#include<constant_pool.h>

int parseConstantPool(FILE *bytecode_file, uint16_t entries){
  int constant_pool_ptr = heapAlloc(sizeof(ConstantPoolEntry) * entries);
  ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[constant_pool_ptr];

  for (int i = 0; i < entries; i++){
    if(!i) continue;
    constant_pool[i].tag = loadU8(bytecode_file);

    switch(constant_pool[i].tag){
      case 7:{ //class
        constant_pool[i].info.CONSTANT_class.name_index = loadU16(bytecode_file);
        break;
      }
      case 9:{ //fieldref
        constant_pool[i].info.CONSTANT_fieldref.class_index = loadU16(bytecode_file);
        constant_pool[i].info.CONSTANT_fieldref.name_and_type_index = loadU16(bytecode_file);
        break;
      }
      case 10:{ //methodref
        constant_pool[i].info.CONSTANT_methodref.class_index = loadU16(bytecode_file);
        constant_pool[i].info.CONSTANT_methodref.name_and_type_index = loadU16(bytecode_file);
        break;
      }
      case 11:{ //interfaceMethodref
        constant_pool[i].info.CONSTANT_interfaceMethodref.class_index = loadU16(bytecode_file);
        constant_pool[i].info.CONSTANT_interfaceMethodref.name_and_type_index = loadU16(bytecode_file);
        break;
      }
      case 8:{ //string
        constant_pool[i].info.CONSTANT_string.string_index = loadU16(bytecode_file);
        break;
      }
      case 3:{ //integer
        constant_pool[i].info.CONSTANT_integer.bytes = loadU32(bytecode_file);
        break;
      }
      case 4:{ //float --- Hay que hacer algunas cosas aún
        constant_pool[i].info.CONSTANT_float.bytes = loadU32(bytecode_file);
        break;
      }
      case 5:{ //long
        constant_pool[i].info.CONSTANT_long.high_bytes = loadU32(bytecode_file);
        constant_pool[i].info.CONSTANT_long.low_bytes = loadU32(bytecode_file);
        i++;
        constant_pool[i].tag = 0; //
        break;
      }
      case 6:{ //double --- Falta especificar algunos casos como con los float
        constant_pool[i].info.CONSTANT_double.high_bytes = loadU32(bytecode_file);
        constant_pool[i].info.CONSTANT_double.low_bytes = loadU32(bytecode_file);
        i++;
        constant_pool[i].tag = 0; //
        break;
      }
      case 12:{ //nameAndType
        constant_pool[i].info.CONSTANT_nameAndType.name_index = loadU16(bytecode_file);
        constant_pool[i].info.CONSTANT_nameAndType.descriptor_index = loadU16(bytecode_file);
        break;
      }
      case 1: { //utf8
        constant_pool[i].info.CONSTANT_utf8.length = loadU16(bytecode_file);

        constant_pool[i].info.CONSTANT_utf8.text_ptr = heapAlloc(constant_pool[i].info.CONSTANT_utf8.length + 1);
        uint8_t *text = (uint8_t*)&heap[constant_pool[i].info.CONSTANT_utf8.text_ptr];

        for (int j = 0; j<constant_pool[i].info.CONSTANT_utf8.length; j++){
          text[j] = loadU8(bytecode_file);
        }
        text[constant_pool[i].info.CONSTANT_utf8.length] = '\0';
        break;
      }
      default:{
        //printf("tag desconocido");
        break;
      } 
    }
  }
  return constant_pool_ptr;
}