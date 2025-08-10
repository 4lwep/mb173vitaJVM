#include<frame.h>
#include<init.h>
#include<runtime.h>

void initFrame(int ma, int method, struct Context *context){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    method_info *methodData = (method_info*)&heap[method];

    Frame frame;

    if (methodData->access_flags & 0x0100){
        frame.local_stack_ptr = createStack(1);
        frame.current_local_stack_entry = -1;
        frame.curr_pc_context = -1;
        frame.operand_stack_ptr = createStack(1);
        frame.current_operand_stack_entry = -1;
        frame.pc_ptr = &context->pc;
        frame.method_ptr = method;
        frame.method_area_pointer = ma;
        frame.isNative = 1;
        frame.max_locals = 1;
        frame.max_stack = 1;

        *frame.pc_ptr = frame.curr_pc_context;
        goto finish;
    }

    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];

    for (int i = 0; i<ma_data->methods_count; i++){
        if (exCode[i].method_ptr == method){
            uint8_t *c = (uint8_t*)&heap[exCode[i].code_array_ptr];
            for (int j = 0; j < exCode[i].length; j++){
                fprintf(log_file, "%d ", c[j]);
            }
            fprintf(log_file, "\n");

            frame.local_stack_ptr = createStack(exCode[i].max_locals);
            frame.current_local_stack_entry = -1;
            frame.curr_pc_context = exCode[i].code_array_ptr;
            frame.operand_stack_ptr = createStack(exCode[i].max_stack);
            frame.current_operand_stack_entry = -1;
            frame.pc_ptr = &context->pc;
            frame.method_ptr = method;
            frame.method_area_pointer = ma;
            frame.isNative = 0;
            frame.max_locals = exCode[i].max_locals;
            frame.max_stack = exCode[i].max_stack;

            *frame.pc_ptr = frame.curr_pc_context;

            goto finish;
        }
    }

    finish:
        pushFrame(frame, context->jvmStack, &context->curr_frame);
}

void excuteClinit(int ma, struct Context *context){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

    for (int i = 0; i<ma_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];
        
        if(!strcmp(met_name, "<clinit>")){
            initFrame(ma, exCode[i].method_ptr, context);
            break;
        }
    }
}

void initFirstFrame(int ma, struct Context *context){
    MethodArea *ma_data = (MethodArea*)&heap[ma];
    ExecutableCode *exCode = (ExecutableCode*)&heap[ma_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[ma_data->constant_pool_ptr];

    for (int i = 0; i<ma_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];
        
        if(!strcmp(met_name, "main")){
            initFrame(ma, exCode[i].method_ptr, context);
            break;
        }
    }
    execute(context);
}

void pushFrame(Frame frame, Frame *stack, int *curr_frame){
    *curr_frame += 1;
    stack[*curr_frame] = frame;
}

void popFrame(Frame* stack, int *curr_frame){
    Frame *popFrame = &stack[*curr_frame];
    if (popFrame->max_locals) free(popFrame->local_stack_ptr);
    if (popFrame->max_stack) free(popFrame->operand_stack_ptr);

    *curr_frame -= 1;
}