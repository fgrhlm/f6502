#include "instr_stack.h"
#include "cpu.h"
#include "mem.h"

void instr_pha(cpu *c, mem *m) {
    stack_reg_push(c, m, REG_A);
    inc_pc(c);
}
void instr_pla(cpu *c, mem *m) {
    stack_reg_pop(c, m, REG_A);

    uint8_t a = *get_reg(c, REG_A);

    set_flag(c, FLAG_N, get_bit(a, 7));
    set_flag(c, FLAG_Z, (a == 0));
    inc_pc(c);
}

void instr_php(cpu *c, mem *m) {
    stack_reg_push(c, m, REG_P);
    inc_pc(c);
}
void instr_plp(cpu *c, mem *m) {
    uint8_t p = stack_pop(c, m);
    set_bit(&p, 5, 1);
    set_bit(&p, 4, 0);
    set_reg(c, REG_P, p);
    inc_pc(c);
}
