#include <stdint.h>
#include <types.h>
#include "cpu.h"
#include "mem.h"
#include "utils.h"

uint16_t immediate_addr(cpu* c){ return inc_pc(c); }

uint16_t absolute_addr(cpu* c, mem* m){
    uint8_t lo, hi;
    
    lo = mem_get_byte(m, inc_pc(c));
    hi = mem_get_byte(m, inc_pc(c));
    
    uint16_t ad = merge_bytes(hi, lo);
    addr_mode am = get_mode(c);

    if(am == AM_ABSOLUTE_X) { return ad + *get_reg(c, REG_X); }
    if(am == AM_ABSOLUTE_Y) { return ad + *get_reg(c, REG_Y); }

    return ad;
}

uint16_t absolute_indirect_addr(cpu* c, mem* m){
    uint8_t lo, hi;
    uint16_t abs_addr = absolute_addr(c,m);

    lo = mem_get_byte(m, abs_addr);
    hi = mem_get_byte(m, abs_addr+1);

    uint16_t ad = merge_bytes(hi, lo);
    return ad;
}

uint16_t relative_addr(cpu* c, mem* m){
    uint8_t offset;
    
    uint16_t pc = inc_pc(c);
    
    offset = mem_get_byte(m, pc) + 1;

    bytes pcs = split_addr(pc);

    uint16_t ad = merge_bytes(pcs.hi, (pcs.lo+offset));
    return ad;
}

uint16_t zero_page_addr(cpu* c, mem* m){
    uint16_t addr = 0; 
    uint8_t byte, reg, lo;

    switch(get_mode(c)){
        case AM_ZERO_PAGE: 
            byte = mem_get_byte(m, inc_pc(c));
            addr = merge_bytes(0, byte); 
            break;
        case AM_ZERO_PAGE_X:
            byte = mem_get_byte(m, inc_pc(c));
            reg = *get_reg(c, REG_X);
            lo = byte + reg;

            addr = merge_bytes(0, lo); 
            break;
        case AM_ZERO_PAGE_Y:
            byte = mem_get_byte(m, inc_pc(c));
            reg = *get_reg(c, REG_Y);
            lo = byte + reg;

            addr = merge_bytes(0, lo); 
            break;
        default:
            break;
    }

    return addr;
}

uint16_t zero_page_indirect_x(cpu* c, mem* m){
    uint8_t hi, lo;
    uint16_t zp_addr, eff_addr;
    uint8_t reg = *get_reg(c, REG_X);
    uint8_t byte = mem_get_byte(m, inc_pc(c));

    zp_addr = reg+byte;
    lo = mem_get_byte(m, merge_bytes(0, zp_addr));
    hi = mem_get_byte(m, merge_bytes(0, zp_addr + 1));
    
    eff_addr = merge_bytes(hi, lo);
    return eff_addr;
}

uint16_t zero_page_indirect_y(cpu* c, mem* m){
    uint8_t byte_addr = mem_get_byte(m, inc_pc(c));
    uint8_t byte = mem_get_byte(m, merge_bytes(0,byte_addr));
    uint8_t reg = *get_reg(c, REG_Y);
    uint8_t lo, hi;

    uint8_t carry = __builtin_add_overflow(byte, reg, &lo);
    

    byte_addr += 1;
    hi = mem_get_byte(m, merge_bytes(0,byte_addr)) + carry;

    return merge_bytes(hi, lo);
}

uint16_t get_addr(cpu* c, mem* m){
    uint16_t addr;
    addr_mode am = get_mode(c);
    
    switch(am){
        case AM_IMMEDIATE: addr = immediate_addr(c); break;
        case AM_ABSOLUTE: addr = absolute_addr(c, m); break; 
        case AM_ABSOLUTE_X: addr = absolute_addr(c, m); break; 
        case AM_ABSOLUTE_Y: addr = absolute_addr(c, m); break;
        case AM_ABSOLUTE_INDIRECT: addr = absolute_indirect_addr(c, m); break;
        case AM_ZERO_PAGE: addr = zero_page_addr(c, m); break; 
        case AM_ZERO_PAGE_X: addr = zero_page_addr(c, m); break; 
        case AM_ZERO_PAGE_Y: addr = zero_page_addr(c, m); break; 
        case AM_ZERO_PAGE_INDIRECT_X: addr = zero_page_indirect_x(c, m); break;
        case AM_ZERO_PAGE_INDIRECT_Y: addr = zero_page_indirect_y(c, m); break;
        case AM_RELATIVE: addr = relative_addr(c,m); break;
        default:
            addr = inc_pc(c); 
            break;
    }

    return addr;
}
