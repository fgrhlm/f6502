#ifndef INSTR_ARITH_H
#define INSTR_ARITH_H

#include "types.h"

void instr_adc(cpu* c, mem* m);
void instr_cmp(cpu* c, mem* m);
void instr_cpx(cpu* c, mem* m);
void instr_cpy(cpu* c, mem* m);
void instr_sbc(cpu* c, mem* m);


void instr_anc(cpu* c, mem* m);
void instr_arr(cpu* c, mem* m);
void instr_asr(cpu* c, mem* m);
void instr_sbx(cpu* c, mem* m);
void instr_xaa(cpu* c, mem* m);
void instr_dcp(cpu* c, mem* m);
void instr_isc(cpu* c, mem* m);
void instr_rla(cpu* c, mem* m);
void instr_rra(cpu* c, mem* m);
void instr_slo(cpu* c, mem* m);
void instr_sre(cpu* c, mem* m);

#endif

