#include <stdint.h>
#include "types.h"
#include "cpu.h"
#include "instr_stack.h"
#include "addr.h"
#include "utils.h"
#include "mem.h"

void instr_brk(cpu* c, mem* m){
    uint8_t status = *get_reg(c, REG_P);
    set_bit(&status, FLAG_B, 1);
    
    uint16_t pc = get_pc(c) + 2;

    push_byte_stack(c, m, pc >> 8);
    push_byte_stack(c, m, pc & 0x00FF);
    push_byte_stack(c, m, status);

    uint8_t hi = mem_get_byte(m, 0xFFFF);
    uint8_t lo = mem_get_byte(m, 0xFFFE);
    uint16_t new_pc = (hi << 8) | lo;

    set_flag(c, FLAG_I, 1);
    set_pc(c, new_pc-1);
}

void instr_jmp(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr - 1);
}
void instr_jsr(cpu* c, mem* m){
    uint16_t pc = get_pc(c);

    uint8_t hi, lo;

    hi = (pc + 2) >> 8;
    lo = (pc + 2) & 0x00FF;

    push_byte_stack(c, m, hi);
    push_byte_stack(c, m, lo);

    hi = mem_get_byte(m, pc + 2);
    lo = mem_get_byte(m, pc + 1);
    
    set_pc(c, ((hi << 8) | lo) - 1);
}

void instr_rti(cpu* c, mem* m){
    uint8_t p = pull_byte_stack(c, m);
    uint8_t pc_l = pull_byte_stack(c,m);
    uint8_t pc_h = pull_byte_stack(c,m);

    set_bit(&p, 5, 1);
    set_bit(&p, 4, 0);
    set_reg(c, REG_P, p);
    set_pc(c, ((pc_h << 8) | pc_l) - 1);
}

void instr_rts(cpu* c, mem* m){
    bytes addr;

    addr.lo = pull_byte_stack(c, m);
    addr.hi = pull_byte_stack(c, m);

    uint16_t pc = merge_bytes(addr.hi, addr.lo);
    debug_logf("RTS -> %d\n", pc);
    set_pc(c, pc);
}

void instr_nop(cpu* c, mem* m){ }
void instr_jam(cpu* c, mem* m){ cpu_stop(c); };
