#include<frame.h>

Frame jvmStack[MAX_JVM_STACK];
int curr_frame = -1;

void excuteClinit(int ma){

}

void initFrame(int ma, int method){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];

    Frame frame;

    for (int i = 0; i<ma_data->methods_count; i++){
        if (exCode[i].method_ptr == method){
            frame.local_stack_ptr = createStack(exCode[i].max_locals);
            frame.current_local_stack_entry = -1;
            frame.curr_pc_context = exCode[i].code_array_ptr;
            frame.operand_stack_ptr = createStack(exCode[i].max_stack);
            frame.current_operand_stack_entry = -1;
            frame.pc_ptr = &pc;
        }
    }

    pushFrame(frame);
}

void initFirstFrame(int ma){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

    Frame firstFrame;

    for (int i = 0; i<ma_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];

        if(!strcmp(met_name, "main")){
            initFrame(ma, exCode[i].method_ptr);
        }
    }
    
    pushFrame(firstFrame);
}

void pushFrame(Frame frame){
    curr_frame += 1;
    jvmStack[curr_frame] = frame;
}

void popFrame(){
    curr_frame -= 1;
}