#include<frame.h>
#include<init.h>
#include<runtime.h>

void initFrame(int frame_method_area, int frame_method, struct Context *frame_context){
    MethodArea *method_area_data = (MethodArea*)&heap[frame_method_area];
    method_info *method_data = (method_info*)&heap[frame_method];

    Frame frame;

    if (method_data->access_flags & ACC_NATIVE){
        frame.local_stack = createStack(STACK_DEFAULT_SIZE);
        frame.current_local_stack_entry = JVM_NULL_PTR;
        frame.curr_pc_context = JVM_NULL_PTR;
        frame.operand_stack = createStack(STACK_DEFAULT_SIZE);
        frame.current_operand_stack_entry = JVM_NULL_PTR;
        frame.pc_ptr = &frame_context->pc;
        frame.method_ptr = frame_method;
        frame.method_area_pointer = frame_method_area;
        frame.is_native = TRUE;
        frame.max_locals = STACK_DEFAULT_SIZE;
        frame.max_stack = STACK_DEFAULT_SIZE;

        *frame.pc_ptr = frame.curr_pc_context;
        goto finish;
    }

    ExecutableCode *executableCode = (ExecutableCode*)&heap[method_area_data->code_table_ptr];

    for (int i = 0; i<method_area_data->methods_count; i++){
        if (executableCode[i].method_ptr == frame_method){
            uint8_t *c = (uint8_t*)&heap[executableCode[i].code_array_ptr];
            for (int j = 0; j < executableCode[i].length; j++){
                fprintf(log_file, "%d ", c[j]);
            }
            fprintf(log_file, "\n");

            frame.local_stack = createStack(executableCode[i].max_locals);
            frame.current_local_stack_entry = JVM_NULL_PTR;
            frame.curr_pc_context = executableCode[i].code_array_ptr;
            frame.operand_stack = createStack(executableCode[i].max_stack);
            frame.current_operand_stack_entry = JVM_NULL_PTR;
            frame.pc_ptr = &frame_context->pc;
            frame.method_ptr = frame_method;
            frame.method_area_pointer = frame_method_area;
            frame.is_native = FALSE;
            frame.max_locals = executableCode[i].max_locals;
            frame.max_stack = executableCode[i].max_stack;

            *frame.pc_ptr = frame.curr_pc_context;

            goto finish;
        }
    }

    finish:
        pushFrame(frame, frame_context->jvm_stack, &frame_context->curr_frame);
}

void excuteClinit(int method_area, struct Context *context){
    MethodArea *method_area_data = (MethodArea*)&heap[method_area];
    ExecutableCode *exCode = (ExecutableCode*)&heap[method_area_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[method_area_data->constant_pool_ptr];

    for (int i = 0; i<method_area_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];
        
        if(!strcmp(met_name, "<clinit>")){
            initFrame(method_area, exCode[i].method_ptr, context);
            break;
        }
    }
}

void initFirstFrame(int method_area, struct Context *context){
    MethodArea *method_area_data = (MethodArea*)&heap[method_area];
    ExecutableCode *exCode = (ExecutableCode*)&heap[method_area_data->code_table_ptr];
    ConstantPoolEntry *constant_pool = (ConstantPoolEntry*)&heap[method_area_data->constant_pool_ptr];

    for (int i = 0; i<method_area_data->methods_count; i++){
        method_info *met = (method_info*)&heap[exCode[i].method_ptr];
        char* met_name = (char*)&heap[constant_pool[met->name_index].info.CONSTANT_utf8.text_ptr];
        
        if(!strcmp(met_name, "main")){
            initFrame(method_area, exCode[i].method_ptr, context);
            break;
        }
    }
    execute(context);
}

void pushFrame(Frame frame, Frame *stack, int *current_frame){
    *current_frame += 1;
    stack[*current_frame] = frame;
}

void popFrame(Frame* stack, int *current_frame){
    Frame *popFrame = &stack[*current_frame];
    if (popFrame->max_locals) free(popFrame->local_stack);
    if (popFrame->max_stack) free(popFrame->operand_stack);

    *current_frame -= 1;
}