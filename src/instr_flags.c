#include "cpu.h"

void instr_clc(cpu* c, mem* m){ set_flag(c, FLAG_C, 0); }
void instr_cld(cpu* c, mem* m){ set_flag(c, FLAG_D, 0); }
void instr_cli(cpu* c, mem* m){ set_flag(c, FLAG_I, 0); }
void instr_clv(cpu* c, mem* m){ set_flag(c, FLAG_V, 0); }
void instr_sec(cpu* c, mem* m){ set_flag(c, FLAG_C, 1); }
void instr_sed(cpu* c, mem* m){ set_flag(c, FLAG_D, 1); }
void instr_sei(cpu* c, mem* m){ set_flag(c, FLAG_I, 1); }
