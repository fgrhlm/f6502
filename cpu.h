#ifndef CPU_H 
#define CPU_H 

#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include "types.h"

uint8_t get_bit(uint8_t b, uint8_t i);
void set_bit(uint8_t* b, uint8_t i, uint8_t n);

uint8_t* get_reg(cpu* c, reg r);
void set_reg(cpu* c, reg r, uint8_t b);

uint16_t get_pc(cpu* c);
void set_pc(cpu* c, uint16_t v);
uint16_t inc_pc(cpu* c);

addr_mode get_mode(cpu* c);
void set_mode(cpu* c, addr_mode am);

uint8_t* get_flags(cpu* c);
uint8_t get_flag(cpu* c, flag f);
void set_flag(cpu* c, flag f, uint8_t n);

void mem_to_reg(reg dst, uint16_t src);
void reg_to_mem(uint16_t dst, reg src);
void reg_to_reg(reg dst, reg src);
cpu* create_cpu();
void free_cpu(cpu* cpu);

uint8_t next_byte(cpu* c, mem* m);

void cpu_stop(cpu* c);

uint8_t cpu_op(cpu* c, mem* m);

#endif
