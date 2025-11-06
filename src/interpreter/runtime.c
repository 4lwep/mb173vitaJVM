#include<runtime.h>
#include<init.h>

#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>

#include "debugScreen_custom.h"

void nextOpCode(Frame *frame, uint8_t number_of_opcodes){
    frame->curr_pc_context += number_of_opcodes;
    *frame->pc_ptr = frame->curr_pc_context;
}

long JNICurrentTimeMilis(){
    return 1716437;
}

void executeNative(struct Context *context){
    Frame *current_frame_data = &context->jvm_stack[context->curr_frame];
    MethodArea *method_area = (MethodArea*)&heap[current_frame_data->method_area_pointer];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[method_area->constant_pool_ptr];
    method_info *method = (method_info*)&heap[current_frame_data->method_ptr];
    char *methodName = (char*)&heap[constant_pool[method->name_index].info.CONSTANT_utf8.text_ptr];
    
    if (!strcmp(methodName, "registerNatives")){

    } else if (!strcmp(methodName, "currentTimeMillis")){
        Slot entry;
        entry.type = VALUE_LONG;
        entry.long_value = JNICurrentTimeMilis();
        popFrame(context->jvm_stack, &context->curr_frame);
        current_frame_data = &context->jvm_stack[context->curr_frame];
        stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
        return;
    } else if (!strcmp(methodName, "println")) {
        Slot text_slot = stackPop(current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry);
        
        MethodArea *frame_method_area = (MethodArea*)&heap[current_frame_data->method_area_pointer];
        ConstantPoolEntry* frame_constant_pool = (ConstantPoolEntry*)&heap[frame_method_area->constant_pool_ptr];
        char *text = (char*)&heap[frame_constant_pool[text_slot.ref_value].info.CONSTANT_utf8.text_ptr];
        fprintf(log_file, "%s\n", text);
        psvDebugScreenPrintf("%s\n", text);
    } else {
        fprintf(log_file, "Atención: %s no está definido\n", methodName);
    }
    
    popFrame(context->jvm_stack, &context->curr_frame);
}

void nop(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    nextOpCode(current_frame_data, 1);
}

void aconst_null(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    Slot entry;
    entry.type = VALUE_REF;
    entry.ref_value = JVM_NULL_PTR;

    stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
    
    nextOpCode(current_frame_data, 1);
}

void lconst_0(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    Slot entry;
    entry.type = VALUE_LONG;
    entry.long_value = 0;

    stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);

    nextOpCode(current_frame_data, 1);
}

void lconst_1(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    Slot entry;
    entry.type = VALUE_LONG;
    entry.long_value = 1;

    stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);

    nextOpCode(current_frame_data, 1);
}

void ldc(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    uint8_t index = ((uint8_t)opcode[1]);

    MethodArea *frame_method_area = (MethodArea*)&heap[current_frame_data->method_area_pointer];
    ConstantPoolEntry* frame_constant_pool = (ConstantPoolEntry*)&heap[frame_method_area->constant_pool_ptr];
    uint8_t tag = frame_constant_pool[index].tag;

    //fprintf(log_file, "Tag: %d\n", frame_constant_pool[index].tag);

    if(tag == 3){ //Integer
        
    } else if(tag == 4){ //Float

    } else if(tag == 8){ //String
        Slot slot;
        slot.type = VALUE_REF;
        slot.ref_value = frame_constant_pool[index].info.CONSTANT_string.string_index;

        stackPush(slot, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
    } else if (tag == 7){ //Class

    }

    nextOpCode(current_frame_data, 2);
}

void dup(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    nextOpCode(current_frame_data, 1);
}

void lcmp(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    Slot entry;
    entry.type = VALUE_INT;

    Slot slot2 = stackPop(current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry);
    Slot slot1 = stackPop(current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry);

    /*fprintf(log_file, "Valor primero %d\n", slot1.long_value);
    fprintf(log_file, "Valor segundo %d\n", slot2.long_value);*/

    if (slot1.long_value > slot2.long_value) {
        entry.int_value = 1;
        stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
    } else if (slot1.long_value == slot2.long_value){
        entry.int_value = 0;
        stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
    } else {
        entry.int_value = -1;
        stackPush(entry, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
    }

    nextOpCode(current_frame_data, 1);
}

void ifle(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    int16_t offset = ((int16_t)opcode[1] << 8) | ((int16_t)opcode[2]);
                
    Slot slot1 = stackPop(current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry);

    if (slot1.int_value <= 0){
        nextOpCode(current_frame_data, offset);
    } else {
        nextOpCode(current_frame_data, 3);
    }
}

void areturn(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    method_info *method = (method_info*)&heap[current_frame_data->method_ptr];
    MethodArea *ma = (MethodArea*)&heap[current_frame_data->method_area_pointer];
    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma->constant_pool_ptr];
    char *descriptor = (char*)&heap[cp[method->descriptor_index].info.CONSTANT_utf8.text_ptr];
    //TODO: Esto es para comparar el retorno del método con el tipo del descriptor del mismo método

    Slot ret = stackPop(current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry);
                
    popFrame(context->jvm_stack, &context->curr_frame);
    current_frame_data = &context->jvm_stack[context->curr_frame]; //Podría asignar esto al hacer pop para no hacerlo en cada iteración innecesariamente

    stackPush(ret, current_frame_data->operand_stack, &current_frame_data->current_operand_stack_entry, current_frame_data->max_stack);
}

void op_return(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    if (context->curr_frame){
        popFrame(context->jvm_stack, &context->curr_frame);
    } else {
        context->exit = TRUE;
        popFrame(context->jvm_stack, &context->curr_frame);
    }
}

void getstatic(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

    Slot entry;

    MethodArea *ma_data = (MethodArea*)&heap[context->jvm_stack[context->curr_frame].method_area_pointer];

    ConstantPoolEntry *cp = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

    int type_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.name_and_type_index].info.CONSTANT_nameAndType.descriptor_index].info.CONSTANT_utf8.text_ptr;
    char *type = (char*)&heap[type_ptr];

    int name_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr;
    char *name = (char*)&heap[name_ptr];

    int class_name_ptr = cp[cp[cp[args].info.CONSTANT_fieldref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr;
    char *class_name = (char*)&heap[class_name_ptr];

    if (get(method_area_hashmap, class_name) == NOT_FOUND){
        char *classQualifiedName = strconcat("ux0:data/", strconcat(class_name, ".class"));
        FILE *newClass = fopen(classQualifiedName, "rb");
        loadClass(newClass, context);
        fclose(newClass);
        return;
    }

    int oMaPtr = get(method_area_hashmap, class_name);
    MethodArea *oMaData = (MethodArea*)&heap[oMaPtr];
    ConstantPoolEntry *oConstantPool = (ConstantPoolEntry*)&heap[oMaData->constant_pool_ptr];
    field_info *oFields = (field_info*)&heap[oMaData->fields_ptr];

    for (int i = 0; i<oMaData->fields_count; i++){
        char *oFieldName = (char*)&heap[oConstantPool[oFields[i].name_index].info.CONSTANT_utf8.text_ptr];
        char *oFieldDesc = (char*)&heap[oConstantPool[oFields[i].descriptor_index].info.CONSTANT_utf8.text_ptr];

        if ((!strcmp(oFieldName, name)) && (!strcmp(oFieldDesc, type)) && (oFields[i].access_flags & ACC_STATIC)){
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

    ++current_frame_data->current_operand_stack_entry;
    current_frame_data->operand_stack[current_frame_data->current_operand_stack_entry] = entry ;

    nextOpCode(current_frame_data, 3);
}

void putstatic(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    nextOpCode(current_frame_data, 3);
}

void invokevirtual(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    //Obtener la información del método a invocar 
    //Obtener el objectref del operand stack
    //obtener la clase de objectref
    //Obtener las superclases de las clases
    uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

    MethodArea *methodArea = (MethodArea*)&heap[current_frame_data->method_area_pointer];
    ConstantPoolEntry *constantPool = (ConstantPoolEntry*)&heap[methodArea->constant_pool_ptr];

    method_info *methods = (method_info*)&heap[methodArea->methods_ptr];

    char *methodName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr];
    char *methodDescriptor = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.name_and_type_index].info.CONSTANT_nameAndType.descriptor_index].info.CONSTANT_utf8.text_ptr];
    char *methodClassName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr];

    if (get(method_area_hashmap, methodClassName) == NOT_FOUND){
        char *classQualifiedName = strconcat("ux0:/data/", strconcat(methodClassName, ".class"));
        FILE *newClass = fopen(classQualifiedName, "rb");
        loadClass(newClass, context);
        fclose(newClass);
        return;
    }

    nextOpCode(current_frame_data, 3);

    int oMaPtr = get(method_area_hashmap, methodClassName);
    MethodArea *oMethodArea = (MethodArea*)&heap[oMaPtr];
    ConstantPoolEntry *oConstantPool = (ConstantPoolEntry*)&heap[oMethodArea->constant_pool_ptr];
    method_info *oMethods = (method_info*)&heap[oMethodArea->methods_ptr];

    for (int i = 0; i<oMethodArea->methods_count; i++){ //Además del nombre necesito comparar los argumentos para manejar las sobrecargas
        char *fMethodName = (char*)&heap[oConstantPool[oMethods[i].name_index].info.CONSTANT_utf8.text_ptr];
        char *fMethodDescriptor = (char*)&heap[oConstantPool[oMethods[i].descriptor_index].info.CONSTANT_utf8.text_ptr];

        if (!strcmp(methodName, fMethodName) && !strcmp(methodDescriptor, fMethodDescriptor)){
            /*if (oMethods[i].access_flags & ACC_PRIVATE){
                initFrame(get(method_area_hashmap, methodClassName), (oMethodArea->methods_ptr + (sizeof(method_info) * i)), context);
                return;
            }*/
           
            initFrame(get(method_area_hashmap, methodClassName), (oMethodArea->methods_ptr + (sizeof(method_info) * i)), context);
            return;
        }
    }
}

void invokestatic(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    uint16_t args = ((uint16_t)opcode[1] << 8) | ((uint16_t)opcode[2]);

    MethodArea *methodArea = (MethodArea*)&heap[current_frame_data->method_area_pointer];
    ConstantPoolEntry *constantPool = (ConstantPoolEntry*)&heap[methodArea->constant_pool_ptr];

    method_info *methods = (method_info*)&heap[methodArea->methods_ptr]; //Esto da información del método pero no el método, gracias a esto se puede buscar pero esto no debe usarse porque puede que el método se encuentre en otra clase, es decir, otro method area

    char *methodName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.name_and_type_index].info.CONSTANT_nameAndType.name_index].info.CONSTANT_utf8.text_ptr];
    char *methodClassName = (char*)&heap[constantPool[constantPool[constantPool[args].info.CONSTANT_methodref.class_index].info.CONSTANT_class.name_index].info.CONSTANT_utf8.text_ptr];

    if (get(method_area_hashmap, methodClassName) == NOT_FOUND){
        char *classQualifiedName = strconcat("ux0:/data/", strconcat(methodClassName, ".class"));
        FILE *newClass = fopen(classQualifiedName, "rb");
        loadClass(newClass, context);
        fclose(newClass);
        return;
    } //En el hello world parecen estar los métodos dentro de las mismas clases, pero esto en teoría no puede resolver métodos de otras clases (comprobar)

    nextOpCode(current_frame_data, 3);

    for (int i = 0; i<methodArea->methods_count; i++){
    char *fMethodName = (char*)&heap[constantPool[methods[i].name_index].info.CONSTANT_utf8.text_ptr];
        if (!strcmp(methodName, fMethodName)){
            initFrame(get(method_area_hashmap, methodClassName), (methodArea->methods_ptr + (sizeof(method_info) * i)), context);
        }
    }
}

void athrow(Frame *current_frame_data, struct Context *context, uint8_t *opcode){
    if (context->curr_frame){
        popFrame(context->jvm_stack, &context->curr_frame);
    } else {
        context->exit = TRUE;
        popFrame(context->jvm_stack, &context->curr_frame);
    }
}

void execute(struct Context *context){
    uint8_t *opcode;

    void **opcodes = malloc(255 * sizeof(void *)); // Para colocar las funciones de los opcodes aquí
    opcodes[0] = &nop;
    opcodes[1] = &aconst_null;
    opcodes[9] = &lconst_0;
    opcodes[10] = &lconst_1;
    opcodes[18] = &ldc;
    opcodes[89] = &dup;
    opcodes[148] = &lcmp;
    opcodes[158] = &ifle;
    opcodes[176] = &areturn;
    opcodes[177] = &op_return;
    opcodes[178] = &getstatic;
    opcodes[179] = &putstatic;
    opcodes[182] = &invokevirtual;
    opcodes[184] = &invokestatic;
    opcodes[191] = &athrow;

    while(!context->exit){
        Frame *current_frame_data = &context->jvm_stack[context->curr_frame];

        *current_frame_data->pc_ptr = current_frame_data->curr_pc_context;
        
        if (current_frame_data->is_native){
            fprintf(log_file, "Nativo\n");
            executeNative(context);
            continue;
        }
        
        opcode = (uint8_t*)&heap[*current_frame_data->pc_ptr];

        if ((void (*)())opcodes[*opcode]){
            fprintf(log_file, "Op code implementado           op code %d  frame %d\n", *opcode, context->curr_frame);
            ((void (*)())opcodes[*opcode])(current_frame_data, context, opcode);
        } else {
            fprintf(log_file, "Op code no implementado        op code %d  frame %d\n", *opcode, context->curr_frame);
            nextOpCode(current_frame_data, 1);
        }
    }

    fflush(log_file);
    fclose(log_file);
}