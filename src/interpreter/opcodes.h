#ifndef OPCODES_H
#define OPCODES_H

#include<frame.h>

void nop(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void aconst_null(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void lconst_0(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void lconst_1(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void ldc(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void dup(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void lcmp(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void ifle(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void areturn(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void op_return(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void getstatic(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void putstatic(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void invokevirtual(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void invokestatic(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

void athrow(Frame *current_frame_data, struct Context *context, uint8_t *opcode);

#endif
