#include <stdint.h>
#include "cpu.h"
#include "addr.h"
#include "mem.h"
#include "types.h"

void instr_dec_reg(cpu* c, reg r){
    uint8_t n = *get_reg(c, r);
    n = n - 1;
    set_reg(c, r, n);

    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}
void instr_dec(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint8_t n = mem_get_byte(m, addr);

    n = n - 1;

    mem_set_byte(m, addr, n);
    
    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}

void instr_dex(cpu* c, mem* m){ instr_dec_reg(c, REG_X); }
void instr_dey(cpu* c, mem* m){ instr_dec_reg(c, REG_Y); }

void instr_inc_reg(cpu* c, reg r){
    uint8_t n = *get_reg(c, r);
    n = n + 1;
    set_reg(c, r, n);

    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}

void instr_inc(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint8_t n = mem_get_byte(m, addr);

    n = n + 1;

    mem_set_byte(m, addr, n);
    
    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}

void instr_inx(cpu* c, mem* m){ instr_inc_reg(c, REG_X); }
void instr_iny(cpu* c, mem* m){ instr_inc_reg(c, REG_Y); }
