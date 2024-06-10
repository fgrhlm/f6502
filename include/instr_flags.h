#ifndef INSTR_FLAGS_H
#define INSTR_FLAGS_H

void instr_clc(cpu *c, mem *m);
void instr_cld(cpu *c, mem *m);
void instr_cli(cpu *c, mem *m);
void instr_clv(cpu *c, mem *m);
void instr_sec(cpu *c, mem *m);
void instr_sed(cpu *c, mem *m);
void instr_sei(cpu *c, mem *m);

#endif
