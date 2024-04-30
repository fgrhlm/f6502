#ifndef INSTR_LOGIC_H
#define INSTR_LOGIC_H

#include "types.h"

void instr_and(cpu* c, mem* m);
void instr_bit(cpu* c, mem* m);
void instr_eor(cpu* c, mem* m);
void instr_ora(cpu* c, mem* m);

#endif

