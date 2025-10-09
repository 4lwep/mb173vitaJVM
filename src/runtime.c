#include<runtime.h>
#include<init.h>

#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>

#include "debugScreen_custom.h"

long JNICurrentTimeMilis(){
    return 1716437;
}

void executeNative(struct Context *context){
    Frame *curr_frame_data = &context->jvmStack[context->curr_frame];
    MethodArea *ma = (MethodArea*)&heap[curr_frame_data->method_area_pointer];
    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma->constant_pool_ptr];
    method_info *method = (method_info*)&heap[curr_frame_data->method_ptr];
    char *methodName = (char*)&heap[cp[method->name_index].info.CONSTANT_utf8.text_ptr];
    if (!strcmp(methodName, "registerNatives")){

    } else if (!strcmp(methodName, "currentTimeMillis")){
        Slot entry;
        entry.type = VALUE_LONG;
        entry.long_value = JNICurrentTimeMilis();
        popFrame(context->jvmStack, &context->curr_frame);
        curr_frame_data = &context->jvmStack[context->curr_frame];
        stackPush(entry, curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry, curr_frame_data->max_stack);
        return;
    } else {
        fprintf(log_file, "Atención: %s no está definido\n", methodName);
    }
    
    popFrame(context->jvmStack, &context->curr_frame);
}

void execute(struct Context *context){
    uint8_t exit = 0;
    uint8_t *opcode;

    while(!exit){
        fprintf(log_file, "cur frame: %d\n", context->curr_frame);

        Frame *curr_frame_data = &context->jvmStack[context->curr_frame];

        *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;
        
        if (curr_frame_data->isNative){
            fprintf(log_file, "Nativo\n");
            executeNative(context);
            continue;
        }
        
        opcode = (uint8_t*)&heap[*curr_frame_data->pc_ptr];
        
        fprintf(log_file, "op code %d\n", *opcode);
        
        switch(*opcode){
            case 1:{
                if (curr_frame_data->current_operand_stack_entry < curr_frame_data->max_stack){ //Temporal para no asignar más valores de los permitidos (sigue haciendo falta?)
                Slot entry;
                entry.type = VALUE_REF;
                entry.ref_value = NULL_PTR;

                stackPush(entry, curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry, curr_frame_data->max_stack);
                }
                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;
                break;
            }
            case 9:{
                Slot entry;
                entry.type = VALUE_LONG;
                entry.long_value = 0;

                stackPush(entry, curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry, curr_frame_data->max_stack);
                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                break;
            }
            /*case 18: {
                break;
            }*/
            case 148: {
                Slot entry;
                entry.type = VALUE_INT;

                Slot slot1 = stackPop(curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry);
                fprintf(log_file, "Valor primero %d\n", slot1.long_value);
                Slot slot2 = stackPop(curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry);
                fprintf(log_file, "Valor segundo %d\n", slot2.long_value);

                if (slot1.long_value < slot2.long_value) {
                    entry.int_value = 1;
                    stackPush(entry, curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry, curr_frame_data->max_stack);
                } else {
                    entry.int_value = 0;
                    stackPush(entry, curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry, curr_frame_data->max_stack);
                }

                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                break;
            }
            case 158: {
                int16_t offset = ((int16_t)opcode[1] << 8) | ((int16_t)opcode[2]);
                
                Slot slot1 = stackPop(curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry);

                if (slot1.int_value <= 0){
                    curr_frame_data->curr_pc_context += offset;
                } else {
                    curr_frame_data->curr_pc_context += 3;
                }

                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                break;
            }
            case 176:{
                method_info *method = (method_info*)&heap[curr_frame_data->method_ptr];
                MethodArea *ma = (MethodArea*)&heap[curr_frame_data->method_area_pointer];
                ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma->constant_pool_ptr];
                char *descriptor = (char*)&heap[cp[method->descriptor_index].info.CONSTANT_utf8.text_ptr];
                //TODO: Esto es para comparar el retorno de la función con el tipo del descriptor

                Slot ret = stackPop(curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry);
                
                popFrame(context->jvmStack, &context->curr_frame);
                curr_frame_data = &context->jvmStack[context->curr_frame]; //Podría asignar esto al hacer pop para no hacerlo en cada iteración innecesariamente

                stackPush(ret, curr_frame_data->operand_stack, &curr_frame_data->current_operand_stack_entry, curr_frame_data->max_stack);
                break;
            }
            case 177: {
                if (context->curr_frame){
                    popFrame(context->jvmStack, &context->curr_frame);
                } else {
                    exit = 1;
                    popFrame(context->jvmStack, &context->curr_frame);
                }
                break;
            }
            case 178: {
                uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

                Slot entry;

                MethodArea *ma_data = (MethodArea*)&heap[context->jvmStack[context->curr_frame].method_area_pointer];

                ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

                int type_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.name_and_type_index].info.CONSTANT_nameAndType.descriptor_index].info.CONSTANT_utf8.text_ptr;
                char *type = (char*)&heap[type_ptr];

                int name_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr;
                char *name = (char*)&heap[name_ptr];

                int class_name_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr;
                char *class_name = (char*)&heap[class_name_ptr];

                if (get(ma_hashmap, class_name) == NOT_FOUND){
                    char *classQualifiedName = strconcat("ux0:data/", strconcat(class_name, ".class"));
                    FILE *newClass = fopen(classQualifiedName, "rb");
                    loadClass(newClass, context);
                    fclose(newClass);
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

                        for(int j = 0; j<oFields[i].attributes_count; j++){
                            char *oAttributeName = (char*)&heap[oConstantPool[oAttributes[j].attribute_name_index].info.CONSTANT_utf8.text_ptr];

                            if (!strcmp(oAttributeName, "ConstantValue")){
                                uint16_t *oAttributeInfo = (uint16_t*)&heap[oAttributes[j].info_ptr];
                            }
                        }
                    }
                }
                
                entry.type = VALUE_INT;
                entry.ref_value = args;// Valor provisional

                ++curr_frame_data->current_operand_stack_entry;
                curr_frame_data->operand_stack[curr_frame_data->current_operand_stack_entry] = entry ;

                curr_frame_data->curr_pc_context += 1;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                break;
            }
            case 179: {
                curr_frame_data->curr_pc_context += 3;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;
                break;
            }
            case 184: {
                uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

                MethodArea *methodArea = (MethodArea*)&heap[curr_frame_data->method_area_pointer];
                ConstantPoolEntry *constantPool = (ConstantPoolEntry*)&heap[methodArea->constant_pool_ptr];

                method_info *methods = (method_info*)&heap[methodArea->methods_ptr];

                char *methodName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr];
                char *methodClassName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr];

                if (get(ma_hashmap, methodClassName) == NOT_FOUND){
                    char *classQualifiedName = strconcat("ux0:/data/", strconcat(methodClassName, ".class"));
                    FILE *newClass = fopen(classQualifiedName, "rb");
                    loadClass(newClass, context);
                    fclose(newClass);
                    break;
                }

                curr_frame_data->curr_pc_context += 3;
                *curr_frame_data->pc_ptr = curr_frame_data->curr_pc_context;

                for (int i = 0; i<methodArea->methods_count; i++){
                    char *fMethodName = (char*)&heap[constantPool[methods[i].name_index].info.CONSTANT_utf8.text_ptr];
                    if (!strcmp(methodName, fMethodName)){
                        initFrame(get(ma_hashmap, methodClassName), (methodArea->methods_ptr + (sizeof(method_info) * i)), context);
                    }
                }

                break;
            }
            case 191: { //Por hacer, esto es temporal
                if (context->curr_frame){
                    popFrame(context->jvmStack, &context->curr_frame);
                } else {
                    exit = 1;
                    popFrame(context->jvmStack, &context->curr_frame);
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

    fflush(log_file);
    fclose(log_file);
}