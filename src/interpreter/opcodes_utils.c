#include<opcodes_utils.h>

void nextOpCode(Frame *frame, uint8_t number_of_opcodes){
    frame->curr_pc_context += number_of_opcodes;
    *frame->pc_ptr = frame->curr_pc_context;
}