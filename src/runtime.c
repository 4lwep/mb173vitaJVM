#include<runtime.h>
#include<frame.h>
#include<loader.h>

void executeNative(){
    Frame *curr_frame_data = &jvmStack[curr_frame];
    MethodArea *ma = (MethodArea*)&heap[curr_frame_data->method_area_pointer];
    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma->constant_pool_ptr];
    method_info *method = (method_info*)&heap[curr_frame_data->method_ptr];
    char *methodName = (char*)&heap[cp[method->name_index].info.CONSTANT_utf8.text_ptr];
    printf("Atención: %s no está definido\n", methodName);
    popFrame();
}

void execute(int ma){
    uint8_t exit = 0;
    uint8_t chFrame = 0;
    uint8_t *opcode;

    while(!exit){
        printf("cur frame: %d\n", curr_frame);
        chFrame = 0;

        Frame *curr_frame_data = &jvmStack[curr_frame];

        *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;
        
        if (curr_frame_data->isNative){
            printf("Nativo\n");
            executeNative();
            continue;
        }
        
        opcode = (uint8_t*)&heap[*curr_frame_data->pc_ptr];
        
        printf("op code %d\n", *opcode);
        
        switch(*opcode){
            case 178: {
                uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

                Slot entry;

                MethodArea *ma_data = (MethodArea*)&heap[jvmStack[curr_frame].method_area_pointer];

                ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

                int type_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.name_and_type_index].info.CONSTANT_nameAndType.descriptor_index].info.CONSTANT_utf8.text_ptr;
                char *type = (char*)&heap[type_ptr];

                int name_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr;
                char *name = (char*)&heap[name_ptr];

                int class_name_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr;
                char *class_name = (char*)&heap[class_name_ptr];

                if (get(ma_hashmap, class_name) == -1){
                    char *classQualifiedName = strconcat(class_name, ".class");
                    FILE *newClass = fopen(classQualifiedName, "rb");
                    loadClass(newClass, ma);
                    fclose(newClass);
                    chFrame = 1;
                    break;
                }

                curr_frame_data->curr_pc_context += 2; //Revisar

                int oMaPtr = get(ma_hashmap, class_name);
                MethodArea *oMaData = (MethodArea*)&heap[oMaPtr];
                ConstantPoolEntry *oConstantPool = (ConstantPoolEntry*)&heap[oMaData->constant_pool_ptr];
                field_info *oFields = (field_info*)&heap[oMaData->fields_ptr];

                for (int i = 0; i<oMaData->fields_count; i++){
                    char *oFieldName = (char*)&heap[oConstantPool[oFields[i].name_index].info.CONSTANT_utf8.text_ptr];
                    char *oFieldDesc = (char*)&heap[oConstantPool[oFields[i].descriptor_index].info.CONSTANT_utf8.text_ptr];

                    if ((!strcmp(oFieldName, name)) && (!strcmp(oFieldDesc, type)) && (oFields[i].access_flags & 0x0008)){
                        attribute_info *oAttributes = (attribute_info*)&heap[oFields[i].attributes_ptr];

                        char *oAttributeName = (char*)&heap[oAttributes[0].attribute_name_index];
                        printf("mnbc,vbzxdvnbzxcmvnbxcmnvbxvmcnb: %d\n", oAttributeName);

                        for(int j = 0; j<oFields[i].attributes_count; j++){
                            char *oAttributeName = (char*)&heap[oAttributes[j].attribute_name_index];

                            if (!strcmp(oAttributeName, "ConstantValue")){
                                uint16_t *oAttributeInfo = (uint16_t*)&heap[oAttributes[j].info_ptr];
                                printf("Attr info: %d\n", *oAttributeInfo);
                            }
                        }
                    }
                }
                
                entry.type = VALUE_INT;
                entry.ref_value = args;// Valor provisional

                ++curr_frame_data->current_operand_stack_entry;
                curr_frame_data->operand_stack_ptr[curr_frame_data->current_operand_stack_entry] = entry ;

                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                break;
            }
            /*case 18: {
                break;
            }*/
            case 177: {
                if (curr_frame){ 
                    popFrame();
                } else {
                    exit = 1;
                    popFrame();
                }
                break;
            }
            case 184: {
                uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

                MethodArea *methodArea = (MethodArea*)&heap[curr_frame_data->method_area_pointer];
                ConstantPoolEntry *constantPool = (ConstantPoolEntry*)&heap[methodArea->constant_pool_ptr];

                method_info *methods = (method_info*)&heap[methodArea->methods_ptr];

                char *methodName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr];
                char *methodClassName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr];

                if (get(ma_hashmap, methodClassName) == -1){
                    char *classQualifiedName = strconcat(methodClassName, ".class");
                    FILE *newClass = fopen(classQualifiedName, "rb");
                    loadClass(newClass, ma);
                    fclose(newClass);
                    chFrame = 1;
                    break;
                }

                curr_frame_data->curr_pc_context += 2;
                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                for (int i = 0; i<methodArea->methods_count; i++){
                    char *fMethodName = (char*)&heap[constantPool[methods[i].name_index].info.CONSTANT_utf8.text_ptr];
                    if (!strcmp(methodName, fMethodName)){
                        
                        initFrame(get(ma_hashmap, methodClassName), (methodArea->methods_ptr + (sizeof(method_info) * i)));
                        chFrame = 1;
                        break;
                    }
                }

                break;
            }
            case 191: { //Por hacer, esto es temporal
                if (curr_frame){ 
                    popFrame();
                } else {
                    exit = 1;
                    popFrame();
                }
                break;
            }
            default:{
                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;
                break;
            } 
        }
    }
}