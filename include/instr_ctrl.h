#ifndef INSTR_CTRL_H
#define INSTR_CTRL_H

#include "types.h"

void instr_brk(cpu* c, mem* m);
void instr_jmp(cpu* c, mem* m);
void instr_jsr(cpu* c, mem* m);
void instr_rti(cpu* c, mem* m);
void instr_rts(cpu* c, mem* m);
void instr_nop(cpu* c, mem* m);

void instr_jam(cpu* c, mem* m);

#endif
