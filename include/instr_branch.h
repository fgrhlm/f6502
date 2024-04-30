#ifndef INSTR_BRANCH_H
#define INSTR_BRANCH_H

#include "types.h"

void instr_bcc(cpu* c, mem* m);
void instr_bcs(cpu* c, mem* m);
void instr_beq(cpu* c, mem* m);
void instr_bmi(cpu* c, mem* m);
void instr_bne(cpu* c, mem* m);
void instr_bpl(cpu* c, mem* m);
void instr_bvc(cpu* c, mem* m);
void instr_bvs(cpu* c, mem* m);

#endif

