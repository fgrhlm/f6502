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

uint8_t next_byte(cpu *c, mem *m) {
    uint16_t addr = get_addr(c, m);
    uint8_t byte = mem_read(m, addr);

    return byte;
}

void service_irq(cpu *c, mem *m){
    uint8_t irq_vec_hi, irq_vec_lo;
    uint16_t irq_vec;

    stack_reg_push(c,m,REG_PH);
    stack_reg_push(c,m,REG_PL);
    stack_reg_push(c,m,REG_P);

    irq_vec_lo = mem_read(m, 0xFFFE);
    irq_vec_hi = mem_read(m, 0xFFFF);
    irq_vec = (irq_vec_hi << 8) | irq_vec_lo;

    set_pc(c, irq_vec);
}

void service_nmi(cpu *c, mem *m){
    uint8_t nmi_vec_hi, nmi_vec_lo;
    uint16_t nmi_vec;

    stack_reg_push(c,m,REG_PH);
    stack_reg_push(c,m,REG_PL);
    stack_reg_push(c,m,REG_P);

    nmi_vec_lo = mem_read(m, 0xFFFA);
    nmi_vec_hi = mem_read(m, 0xFFFB);
    nmi_vec = (nmi_vec_hi << 8) | nmi_vec_lo;

    set_pc(c, nmi_vec);
}

void service_interrupts(cpu *c, mem *m){
    uint8_t pin_irq, pin_nmi;

    pin_nmi = get_pin(c, PIN_NMI);
    if(pin_nmi == PIN_LO){
        service_nmi(c,m);
    }
    
    pin_irq = get_pin(c, PIN_IRQ);
    if(pin_irq == PIN_LO){
        service_irq(c,m);
    }
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
    uint8_t opcode = mem_read(m, pc);
    
    service_interrupts(c,m);
    instr_parse(c, m, opcode);

    return 1;
}
