#ifndef INSTR_LOAD_H
#define INSTR_LOAD_H

#include "types.h"

void instr_lda(cpu* c, mem* m);
void instr_ldx(cpu* c, mem* m);
void instr_ldy(cpu* c, mem* m);
void instr_sta(cpu* c, mem* m);
void instr_stx(cpu* c, mem* m);
void instr_sty(cpu* c, mem* m);

void instr_lax(cpu* c, mem* m);
void instr_shx(cpu* c, mem* m);
void instr_shy(cpu* c, mem* m);
void instr_sha(cpu* c, mem* m);
void instr_sax(cpu* c, mem* m);
void instr_las(cpu* c, mem* m);

#endif

