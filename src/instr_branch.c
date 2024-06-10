#include "addr.h"
#include "cpu.h"

void instr_branch(cpu *c, mem *m, uint8_t flag_state) {
  uint16_t pc;

  if (flag_state) {
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr);
  }

  pc = get_pc(c);
  set_pc(c, pc + 2);
}

void instr_bcc(cpu *c, mem *m) { instr_branch(c, m, !get_flag(c, FLAG_C)); }
void instr_bcs(cpu *c, mem *m) { instr_branch(c, m, get_flag(c, FLAG_C)); }
void instr_beq(cpu *c, mem *m) { instr_branch(c, m, get_flag(c, FLAG_Z)); }
void instr_bmi(cpu *c, mem *m) { instr_branch(c, m, get_flag(c, FLAG_N)); }
void instr_bne(cpu *c, mem *m) { instr_branch(c, m, !get_flag(c, FLAG_Z)); }
void instr_bpl(cpu *c, mem *m) { instr_branch(c, m, !get_flag(c, FLAG_N)); }
void instr_bvc(cpu *c, mem *m) { instr_branch(c, m, !get_flag(c, FLAG_V)); }
void instr_bvs(cpu *c, mem *m) { instr_branch(c, m, get_flag(c, FLAG_V)); }
