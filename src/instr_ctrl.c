#include "addr.h"
#include "cpu.h"
#include "instr_stack.h"
#include "mem.h"
#include <stdint.h>

void instr_brk(cpu *c, mem *m) {
    uint8_t status = *get_reg(c, REG_P);
    set_bit(&status, FLAG_B, 1);

    uint16_t pc = get_pc(c) + 2;

    stack_push(c, m, pc >> 8);
    stack_push(c, m, pc & 0x00FF);
    stack_push(c, m, status);

    uint8_t hi = mem_read(m, 0xFFFF);
    uint8_t lo = mem_read(m, 0xFFFE);
    uint16_t new_pc = (hi << 8) | lo;

    set_flag(c, FLAG_I, 1);
    set_pc(c, new_pc);
}

void instr_jmp(cpu *c, mem *m) {
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr);
}

void instr_jsr(cpu *c, mem *m) {
    uint16_t pc = get_pc(c);

    uint8_t hi, lo;

    hi = (pc + 2) >> 8;
    lo = (pc + 2) & 0xFF;

    stack_push(c, m, hi);
    stack_push(c, m, lo);

    lo = mem_read(m, pc + 1);
    hi = mem_read(m, pc + 2);

    set_pc(c, ((hi << 8) | lo));
}

void instr_rti(cpu *c, mem *m) {
    uint8_t p = stack_pop(c, m);
    uint8_t pc_l = stack_pop(c, m);
    uint8_t pc_h = stack_pop(c, m);

    set_bit(&p, 5, 1);
    set_bit(&p, 4, 0);
    set_reg(c, REG_P, p);
    set_pc(c, ((pc_h << 8) | pc_l));
}

void instr_rts(cpu *c, mem *m) {
    uint8_t hi, lo;

    lo = stack_pop(c, m);
    hi = stack_pop(c, m);

    uint16_t pc = (hi << 8) | lo;
    set_pc(c, pc);
    inc_pc(c);
}

void instr_nop(cpu *c, mem *m) {
    addr_mode am = get_addr_mode(c);
    uint16_t pc = get_pc(c);
    switch (am) {
    case AM_IMPLIED:
        set_pc(c, pc);
        break;
    case AM_IMMEDIATE:
    case AM_ZERO_PAGE:
    case AM_ZERO_PAGE_X:
        set_pc(c, pc + 1);
        break;
    case AM_ABSOLUTE:
    case AM_ABSOLUTE_X:
        set_pc(c, pc + 2);
        break;
    default:
        break;
    }

    inc_pc(c);
}
void instr_jam(cpu *c, mem *m) {}
