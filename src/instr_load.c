#include <stdio.h>
#include <stdlib.h>

#include "instr_load.h"
#include "types.h"
#include "cpu.h"
#include "mem.h"
#include "utils.h"
#include "addr.h"

void instr_load(cpu* c, mem* m, reg r){
    uint8_t operand = next_byte(c, m);

    set_reg(c, r, operand);
    set_flag(c, FLAG_Z, (operand == 0));
    set_flag(c, FLAG_N, get_bit(operand, 7));
}

void instr_lda(cpu* c, mem* m){ instr_load(c, m, REG_A); }
void instr_ldx(cpu* c, mem* m){ instr_load(c, m, REG_X); }
void instr_ldy(cpu* c, mem* m){ instr_load(c, m, REG_Y); }

void instr_store(cpu* c, mem* m, reg r){
    uint16_t addr = get_addr(c, m);
    uint8_t reg = *get_reg(c, r);
    debug_logf("\tstore addr: %x -> %x\n", addr, reg);

    mem_set_byte(m, addr, reg);
}

void instr_lax(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);

    set_reg(c, REG_A, byte);
    set_reg(c, REG_X, byte);

    set_flag(c, FLAG_Z, byte == 0);
    set_flag(c, FLAG_N, get_bit(byte, 7));
};

void instr_sta(cpu* c, mem* m){ instr_store(c, m, REG_A); }
void instr_stx(cpu* c, mem* m){ instr_store(c, m, REG_X); }
void instr_sty(cpu* c, mem* m){ instr_store(c, m, REG_Y); }

void instr_las(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint8_t byte = mem_get_byte(m, addr);

    uint8_t sp = *get_reg(c, REG_S);
    uint8_t res = sp & byte;

    set_reg(c, REG_A, res);
    set_reg(c, REG_X, res);
    set_reg(c, REG_S, res);

    set_flag(c, FLAG_N, get_bit(res, 7));
    set_flag(c, FLAG_Z, res == 0);
};

void instr_shx(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint16_t pc = get_pc(c);

    uint8_t reg_x = *get_reg(c, REG_X);
    uint8_t hi = (addr+1) >> 8;
    uint8_t res = reg_x & hi;
    
    if((pc >> 8) != (addr >> 8)){
        addr = (res << 8) | (addr & 0xFF);
    }

    mem_set_byte(m, addr, res);
};

void instr_shy(cpu* c, mem* m){

};

void instr_sha(cpu* c, mem* m){

};

void instr_sax(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    
    uint8_t a = *get_reg(c, REG_A);
    uint8_t x = *get_reg(c, REG_X);
    uint8_t res = (a & x);

    mem_set_byte(m, addr, res);
};
