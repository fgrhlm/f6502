#include "addr.h"
#include "cpu.h"
#include "mem.h"

void instr_transfer(cpu *c, mem *m, reg dst, reg src) {
    uint8_t byte = *get_reg(c, src);

    set_reg(c, dst, byte);
    set_flag(c, FLAG_N, get_bit(byte, 7));
    set_flag(c, FLAG_Z, (byte == 0));
    inc_pc(c);
}

void instr_tax(cpu *c, mem *m) { instr_transfer(c, m, REG_X, REG_A); }
void instr_tay(cpu *c, mem *m) { instr_transfer(c, m, REG_Y, REG_A); }
void instr_tsx(cpu *c, mem *m) { instr_transfer(c, m, REG_X, REG_S); }
void instr_txa(cpu *c, mem *m) { instr_transfer(c, m, REG_A, REG_X); }
void instr_txs(cpu *c, mem *m) {
    uint8_t p = *get_reg(c, REG_P);
    instr_transfer(c, m, REG_S, REG_X);
    set_reg(c, REG_P, p);
}
void instr_tya(cpu *c, mem *m) { instr_transfer(c, m, REG_A, REG_Y); }

void instr_shs(cpu *c, mem *m) {
    uint16_t addr = get_addr(c, m);

    uint8_t a = *get_reg(c, REG_A);
    uint8_t x = *get_reg(c, REG_X);
    uint8_t res = (a & x);

    set_reg(c, REG_S, res);
    uint8_t hi = addr >> 8;

    res = (res & hi) + 1;
    mem_set_byte(m, addr, res);
    inc_pc(c);
}
