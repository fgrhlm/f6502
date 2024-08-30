#include "instr_stack.h"
#include "cpu.h"
#include "mem.h"

void stack_reg_push(cpu *c, mem *m, reg r) {
    uint8_t sp = *get_reg(c, REG_S);
    uint8_t src = *get_reg(c, r);

    // P register always gets pushed with bit 4 and 5 set
    if (r == REG_P) {
        set_bit(&src, 4, 1);
        set_bit(&src, 5, 1);
    }

    uint16_t addr = (0x01 << 8) | sp;

    mem_write(m, addr, src);
    set_reg(c, REG_S, sp - 1);
}

void stack_push(cpu *c, mem *m, uint8_t b) {
    uint8_t sp = *get_reg(c, REG_S);

    uint16_t addr = (0x01 << 8) | sp;
    mem_write(m, addr, b);
    set_reg(c, REG_S, sp - 1);
}

void stack_reg_pop(cpu *c, mem *m, reg r) {
    uint8_t sp = *get_reg(c, REG_S);

    uint16_t addr = (0x01 << 8) | (sp + 1);
    uint8_t src = mem_read(m, addr);

    set_reg(c, r, src);
    set_reg(c, REG_S, sp + 1);
}

uint8_t stack_pop(cpu *c, mem *m) {
    uint8_t sp = *get_reg(c, REG_S);
    uint16_t addr = (0x01 << 8) | (sp + 1);
    uint8_t byte = mem_read(m, addr);

    set_reg(c, REG_S, sp + 1);
    return byte;
}

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
