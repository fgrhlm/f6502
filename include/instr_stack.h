#ifndef INSTR_STACK_H
#define INSTR_STACK_H

#include <stdint.h>

#include "cpu.h"
#include "mem.h"

void stack_reg_push(cpu *c, mem *m, reg r);
void stack_push(cpu *c, mem *m, uint8_t b);
void stack_reg_pop(cpu *c, mem *m, reg r);
uint8_t stack_pop(cpu *c, mem *m);
void instr_pha(cpu *c, mem *m);
void instr_pla(cpu *c, mem *m);
void instr_php(cpu *c, mem *m);
void instr_plp(cpu *c, mem *m);

#endif
