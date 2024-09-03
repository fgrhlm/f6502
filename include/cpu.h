#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include "mem.h"

typedef enum { PIN_LO, PIN_HI } pin_state;

typedef enum { REG_A, REG_X, REG_Y, REG_PL, REG_PH, REG_S, REG_P } reg;

typedef enum {
    FLAG_C,
    FLAG_Z,
    FLAG_I,
    FLAG_D,
    FLAG_B,
    FLAG_X,
    FLAG_V,
    FLAG_N
} flag;

typedef enum { CYCLE_R, CYCLE_W } cpu_cycle_type;

typedef enum {
    AM_ACCUMULATOR,
    AM_IMMEDIATE,
    AM_ZERO_PAGE,
    AM_ZERO_PAGE_X,
    AM_ZERO_PAGE_Y,
    AM_RELATIVE,
    AM_ABSOLUTE,
    AM_ABSOLUTE_X,
    AM_ABSOLUTE_Y,
    AM_ABSOLUTE_INDIRECT,
    AM_ZERO_PAGE_INDIRECT_X,
    AM_ZERO_PAGE_INDIRECT_Y,
    AM_IMPLIED,
    AM_NULL
} addr_mode;

typedef enum {
    PIN_RDY,
    PIN_RST,
    PIN_IRQ,
    PIN_NMI,
    PIN_CLK_I,
    PIN_CLK_O,
    PIN_CLK_INV_O
} pin;

typedef struct {
    cpu_cycle_type type;
    mem_byte payload;
} cpu_cycle;

typedef struct {
    uint8_t regs[7], pins;
    addr_mode addr_mode;
} cpu;

// Bits
uint8_t get_bit(uint8_t b, uint8_t i);
void set_bit(uint8_t *b, uint8_t i, uint8_t n);

// Registers
uint8_t *get_reg(cpu *c, reg r);
void set_reg(cpu *c, reg r, uint8_t b);

uint16_t get_pc(cpu *c);
void set_pc(cpu *c, uint16_t v);
uint16_t inc_pc(cpu *c);

uint8_t *get_flags(cpu *c);
uint8_t get_flag(cpu *c, flag f);
void set_flag(cpu *c, flag f, uint8_t n);

// Pins
pin_state get_pin(cpu *c, pin p);
void set_pin(cpu *c, pin p, pin_state ps);

// Addressing
void set_addr_mode(cpu *c, addr_mode am);
addr_mode get_addr_mode(cpu *c);

// Stack
void stack_reg_push(cpu *c, mem *m, reg r);
void stack_push(cpu *c, mem *m, uint8_t b);
void stack_reg_pop(cpu *c, mem *m, reg r);
uint8_t stack_pop(cpu *c, mem *m);

// Mem
void mem_to_reg(reg dst, uint16_t src);
void reg_to_mem(uint16_t dst, reg src);
void reg_to_reg(reg dst, reg src);
void free_cpu(cpu *cpu);

uint8_t next_byte(cpu *c, mem *m);

// Interrupts
void service_irq(cpu *c, mem *m);
void service_nmi(cpu *c, mem *m);
void service_interrupts(cpu *c, mem *m);

// CPU API
void reset_cpu(cpu *c);

uint8_t cpu_tick(cpu *c, mem *m);

#endif
