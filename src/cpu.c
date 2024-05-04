#include <stdint.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "cpu.h"
#include "mem.h"
#include "instr.h"
#include "utils.h"
#include "addr.h"

uint8_t get_bit(uint8_t b, uint8_t i){ return (b >> i) & 1; }
void set_bit(uint8_t* b, uint8_t i, uint8_t n){ *b = n ? (*b | (1 << i)) : (*b & (~(1 << i))); }

uint8_t* get_reg(cpu* c, reg r){ return &c->regs[r]; }
void set_reg(cpu* c, reg r, uint8_t b){ c->regs[r] = b; }

uint16_t get_pc(cpu* c){ return (*get_reg(c, REG_PH) << 8) | (*get_reg(c, REG_PL) & 0xFF); }
void set_pc(cpu* c, uint16_t v){
    set_reg(c, REG_PH, (v >> 8));
    set_reg(c, REG_PL, (v & 0x00FF));
}
uint16_t inc_pc(cpu* c){ 
    uint16_t pc = get_pc(c);
    pc += 1;

    set_pc(c, pc);
    return pc;
}

addr_mode get_mode(cpu* c){ return c->addr_mode; }
void set_mode(cpu* c, addr_mode am){ c->addr_mode = am; }

uint8_t* get_flags(cpu* c){ return &c->regs[REG_P]; }
uint8_t get_flag(cpu* c, flag f) { return get_bit(c->regs[REG_P], f); }
void set_flag(cpu* c, flag f, uint8_t n){ set_bit(&c->regs[REG_P], f, n); }

uint8_t next_byte(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint8_t byte = mem_get_byte(m, addr);
    
    return byte;
}

void cpu_stop(cpu* c){ c->stop = 1; }

cpu* create_cpu(){
    cpu* c = malloc(sizeof(cpu));

    c->regs = calloc(7, sizeof(uint8_t));
    c->stop = 0;
    return c;
}

void free_cpu(cpu* cpu){
    free(cpu->regs);
    free(cpu);
}

uint8_t cpu_op(cpu* c, mem* m){
    uint16_t pc = get_pc(c);
    uint8_t opcode = mem_get_byte(m, pc);
    
    debug_logf("[OP START %d -> 0x%02x -> %s]\n", pc, opcode, opcode_to_str(opcode));
    log_regs(c,m);

    instr_parse(c, m, opcode);
   
    inc_pc(c);
    return 1;
}
