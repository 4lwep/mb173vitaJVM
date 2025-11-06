#include "init.h"
#include "opcodes_utils.h"

void jumpOpCode(Frame *frame, uint8_t number_of_opcodes){
    frame->curr_pc_context += number_of_opcodes;
    *frame->pc_ptr = frame->curr_pc_context;
}

void nextOpCode(Frame *frame){
    jumpOpCode(frame, 1);
}

Slot createNewSlot(ValueType type, void* value){
    Slot entry;
    entry.type = type;
    
    switch(type) {
        case VALUE_INT:
            entry.ref_value = *(uint16_t*)value;
            break;
        case VALUE_FLOAT:
            entry.float_value = *(float*)value;
            break;
        case VALUE_REF:
            entry.ref_value = *(uint16_t*)value;
            break;
        case VALUE_DOUBLE:
            entry.double_value = *(double*)value;
            break;
        case VALUE_LONG:
            entry.long_value = *(long*)value;
            break;
        case VALUE_NONE:
            break;
    }
    
    return entry;
}

uint16_t isClassInitialized(char* class_name){
    if (get(method_area_hashmap, class_name) == NOT_FOUND) return FALSE; else return TRUE;
}

void initializeNewClass(char* class_name, struct Context *context){
    char *classQualifiedName = strconcat("ux0:data/", strconcat(class_name, ".class"));
    FILE *newClass = fopen(classQualifiedName, "rb");
    loadClass(newClass, context);
    fclose(newClass);
    return;
}

void initializeIfNot(char* class_name, struct Context *context){
    if(!isClassInitialized(class_name)) initializeNewClass(class_name, context);
    return;
}