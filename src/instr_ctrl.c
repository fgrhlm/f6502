#include <stdint.h>
#include "types.h"
#include "cpu.h"
#include "instr_stack.h"
#include "addr.h"
#include "utils.h"
#include "mem.h"

void instr_brk(cpu* c, mem* m){
    uint16_t pc = get_pc(c);

    bytes addr_bytes = split_addr(pc);

    push_byte_stack(c, m, addr_bytes.lo);
    push_byte_stack(c, m, addr_bytes.hi);
    push_reg_stack(c, m, REG_P);

    pull_reg_stack(c, m, REG_P);
    uint8_t hi = pull_byte_stack(c, m);
    uint8_t lo = pull_byte_stack(c, m);

    set_pc(c, merge_bytes(hi, lo));
    set_flag(c, FLAG_I, 1);
}

void instr_jmp(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr);
}
void instr_jsr(cpu* c, mem* m){
    bytes addr;
    addr.lo = next_byte(c, m);
    addr.hi = next_byte(c, m);

    bytes pc = split_addr(get_pc(c));
    push_byte_stack(c, m, pc.hi);
    push_byte_stack(c, m, pc.lo);

    set_pc(c, merge_bytes(addr.hi, addr.lo));
}

void instr_rti(cpu* c, mem* m){
    pull_reg_stack(c, m, REG_P);
    
    bytes pc;
    pc.lo = next_byte(c, m);
    pc.hi = next_byte(c, m);

    set_pc(c, merge_bytes(pc.hi, pc.lo));
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
