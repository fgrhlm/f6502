#ifndef INSTR_TRANS_H
#define INSTR_TRANS_H

#include "types.h"

void instr_tax(cpu* c, mem* m);
void instr_tay(cpu* c, mem* m);
void instr_tsx(cpu* c, mem* m);
void instr_txa(cpu* c, mem* m);
void instr_txs(cpu* c, mem* m);
void instr_tya(cpu* c, mem* m);

void instr_shs(cpu* c, mem* m);

#endif

