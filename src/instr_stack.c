#include "instr_stack.h"
#include "types.h"
#include "cpu.h"
#include "mem.h"
#include "utils.h"

void push_reg_stack(cpu* c, mem* m, reg r){
    uint8_t sp = *get_reg(c, REG_S);
    uint8_t src = *get_reg(c, r);
    
    // P register always gets pushed with bit 4 and 5 set
    if(r == REG_P){
        set_bit(&src, 4, 1);
        set_bit(&src, 5, 1);
    }

    uint16_t addr = merge_bytes(0x01,sp); 
    
    mem_set_byte(m, addr, src);
    set_reg(c, REG_S, sp - 1);
}

void push_byte_stack(cpu* c, mem* m, uint8_t b){
    uint8_t sp = *get_reg(c, REG_S);

    uint16_t addr = merge_bytes(0x01,sp); 
    mem_set_byte(m, addr, b);
    set_reg(c, REG_S, sp - 1);
}

void pull_reg_stack(cpu* c, mem* m, reg r){
    uint8_t sp = *get_reg(c, REG_S);

    uint16_t addr = merge_bytes(0x01, sp+1); 
    uint8_t src = mem_get_byte(m, addr);

    set_reg(c, r, src);
    set_reg(c, REG_S, sp + 1);
}

uint8_t pull_byte_stack(cpu* c, mem* m){
    uint8_t sp = *get_reg(c, REG_S);
    uint16_t addr = merge_bytes(0x01, sp+1); 
    uint8_t byte = mem_get_byte(m, addr);

    set_reg(c, REG_S, sp + 1);
    return byte;
}

void instr_pha(cpu* c, mem* m){ push_reg_stack(c, m, REG_A); }
void instr_pla(cpu* c, mem* m){
    pull_reg_stack(c, m, REG_A);

    uint8_t a = *get_reg(c, REG_A);
    
    set_flag(c, FLAG_N, get_bit(a, 7));
    set_flag(c, FLAG_Z, (a == 0));
}

void instr_php(cpu* c, mem* m){ push_reg_stack(c, m, REG_P); }
void instr_plp(cpu* c, mem* m){ pull_reg_stack(c, m, REG_P); }
