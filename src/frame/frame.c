#include<frame.h>

Frame jvmStack[MAX_JVM_STACK];
int curr_frame = -1;

void initFrame(int ma, int method){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    method_info *methodData = (method_info*)&heap[method];

    Frame frame;

    if (methodData->access_flags & 0x0100){
        frame.local_stack_ptr = createStack(0);
        frame.current_local_stack_entry = -1;
        frame.curr_pc_context = -1;
        frame.operand_stack_ptr = createStack(0);
        frame.current_operand_stack_entry = -1;
        frame.pc_ptr = &pc;
        frame.method_ptr = method;
        frame.method_area_pointer = ma;
        frame.isNative = 1;

        *frame.pc_ptr = frame.curr_pc_context;
        goto finish;
    }

    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];

    for (int i = 0; i<ma_data->methods_count; i++){
        if (exCode[i].method_ptr == method){
            frame.local_stack_ptr = createStack(exCode[i].max_locals);
            frame.current_local_stack_entry = -1;
            frame.curr_pc_context = exCode[i].code_array_ptr;
            frame.operand_stack_ptr = createStack(exCode[i].max_stack);
            frame.current_operand_stack_entry = -1;
            frame.pc_ptr = &pc;
            frame.method_ptr = method;
            frame.method_area_pointer = ma;
            frame.isNative = 0;

            *frame.pc_ptr = frame.curr_pc_context;

            goto finish;
        }
    }

    finish:
        pushFrame(frame);
}

void excuteClinit(int ma){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

    for (int i = 0; i<ma_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];
        
        if(!strcmp(met_name, "<clinit>")){
            initFrame(ma, exCode[i].method_ptr);
            break;
        }
    }
}

void initFirstFrame(int ma){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

    for (int i = 0; i<ma_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];
        
        if(!strcmp(met_name, "main")){
            initFrame(ma, exCode[i].method_ptr);
            break;
        }
    }
    execute(ma);
}

void pushFrame(Frame frame){
    curr_frame += 1;
    jvmStack[curr_frame] = frame;
}

Frame popFrame(){
    curr_frame -= 1;

    return jvmStack[curr_frame + 1];
}