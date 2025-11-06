#include<runtime.h>
#include<init.h>

#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>

#include "debugScreen_custom.h"

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