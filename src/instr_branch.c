#include "cpu.h"
#include "addr.h"

void instr_branch(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr); 
}

void instr_bcc(cpu* c, mem* m){ if(!get_flag(c, FLAG_C)){ instr_branch(c, m); } }
void instr_bcs(cpu* c, mem* m){ if(get_flag(c, FLAG_C)){  instr_branch(c, m); } }
void instr_beq(cpu* c, mem* m){ if(get_flag(c, FLAG_Z)){  instr_branch(c, m); } }
void instr_bmi(cpu* c, mem* m){ if(get_flag(c, FLAG_N)){  instr_branch(c, m); } }
void instr_bne(cpu* c, mem* m){ if(!get_flag(c, FLAG_Z)){ instr_branch(c, m); } }
void instr_bpl(cpu* c, mem* m){ if(!get_flag(c, FLAG_N)){ instr_branch(c, m); } }
void instr_bvc(cpu* c, mem* m){ if(!get_flag(c, FLAG_V)){ instr_branch(c, m); } }
void instr_bvs(cpu* c, mem* m){ if(get_flag(c, FLAG_V)){  instr_branch(c, m); } }
