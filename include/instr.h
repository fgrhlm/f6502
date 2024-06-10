#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"
#include "mem.h"

void instr_exec(cpu *c, mem *m, addr_mode am, void (*instr_ptr)(cpu *, mem *));
void instr_parse(cpu *c, mem *m, uint8_t opcode);

#endif
