#ifndef INSTR_INC_H
#define INSTR_INC_H

#include "types.h"

void instr_dec(cpu* c, mem* m);
void instr_dex(cpu* c, mem* m);
void instr_dey(cpu* c, mem* m);
void instr_inc(cpu* c, mem* m);
void instr_inx(cpu* c, mem* m);
void instr_iny(cpu* c, mem* m);

#endif

