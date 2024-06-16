#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include "addr.h"
#include "cpu.h"
#include "instr.h"
#include "mem.h"

uint8_t get_bit(uint8_t b, uint8_t i) { return (b >> i) & 1; }
void set_bit(uint8_t *b, uint8_t i, uint8_t n) {
    *b = n ? (*b | (1 << i)) : (*b & (~(1 << i)));
}

uint8_t *get_reg(cpu *c, reg r) { return &c->regs[r]; }
void set_reg(cpu *c, reg r, uint8_t b) { c->regs[r] = b; }

uint16_t get_pc(cpu *c) {
    return (*get_reg(c, REG_PH) << 8) | (*get_reg(c, REG_PL) & 0xFF);
}
void set_pc(cpu *c, uint16_t v) {
    set_reg(c, REG_PH, (v >> 8));
    set_reg(c, REG_PL, (v & 0x00FF));
}
uint16_t inc_pc(cpu *c) {
    uint16_t pc = get_pc(c);
    pc += 1;

    set_pc(c, pc);
    return pc;
}

uint8_t *get_flags(cpu *c) { return &c->regs[REG_P]; }
uint8_t get_flag(cpu *c, flag f) { return get_bit(c->regs[REG_P], f); }
void set_flag(cpu *c, flag f, uint8_t n) { set_bit(&c->regs[REG_P], f, n); }

pin_state get_pin(cpu *c, pin p){ return get_bit(c->pins, p) ? PIN_HI : PIN_LO; }
void set_pin(cpu *c, pin p, pin_state ps){ set_bit(&c->pins, p, ps); }

void set_addr_mode(cpu *c, addr_mode am){ c->addr_mode = am; }
addr_mode get_addr_mode(cpu *c){ return c->addr_mode; }

uint8_t next_byte(cpu *c, mem *m) {
    uint16_t addr = get_addr(c, m);
    uint8_t byte = mem_get_byte(m, addr);

    return byte;
}

void reset_cpu(cpu *c) {
    c->addr_mode = AM_NULL;
    c->pins = 0;

    for(int i=0; i<7; i++){
        c->regs[i] = 0;
    }
}

uint8_t cpu_tick(cpu *c, mem *m) {
    uint16_t pc = get_pc(c);
    uint8_t opcode = mem_get_byte(m, pc);

    instr_parse(c, m, opcode);

    return 1;
}
