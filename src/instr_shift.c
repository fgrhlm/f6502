#include <stdint.h>
#include "types.h"
#include "cpu.h"
#include "mem.h"
#include "addr.h"


void instr_asl(cpu* c, mem* m){
    uint8_t operand;
    uint8_t result;

    addr_mode am = get_mode(c);
    uint16_t addr = get_addr(c, m);
    
    if(am == AM_ACCUMULATOR){ 
        operand = *get_reg(c, REG_A); 
    }else{
        operand = mem_get_byte(m, addr);
    }
    
    uint8_t o_carry = get_bit(operand, 7);
    result = operand << 1;
    set_bit(&result, 0, 0);
    
    set_flag(c, FLAG_C, o_carry);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_Z, result == 0);

    if(am == AM_ACCUMULATOR){
        set_reg(c, REG_A, result);
    }else{
        mem_set_byte(m, addr, result);
    }
}

void instr_lsr(cpu* c, mem* m){
    uint8_t operand;
    uint8_t result;

    addr_mode am = get_mode(c);
    
    if(am == AM_ACCUMULATOR){ 
        operand = *get_reg(c, REG_A); 
    }else{
        operand = next_byte(c, m);
    }
    
    result = operand >> 1;
    
    set_flag(c, FLAG_C, get_bit(operand, 1));
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_Z, result == 0);

    if(am == AM_ACCUMULATOR){
        set_reg(c, REG_A, result);
    }else{
        mem_set_byte(m, get_addr(c, m), result);
    }
}

void instr_rol(cpu* c, mem* m){
    addr_mode am = get_mode(c);
    uint16_t addr = get_addr(c, m);

    uint8_t operand = am == AM_ACCUMULATOR ? *get_reg(c, REG_A) : next_byte(c, m);
    uint8_t result = operand << 1;

    uint8_t carry = get_flag(c, FLAG_C);
    set_bit(&result, 0, carry);

    am == AM_ACCUMULATOR ? set_reg(c, REG_A, result) : mem_set_byte(m, addr, result); 

    set_flag(c, FLAG_C,get_bit(result, 7));
    set_flag(c, FLAG_N,get_bit(operand, 6));
    set_flag(c, FLAG_Z, result == 0);
}
void instr_ror(cpu* c, mem* m){
    addr_mode am = get_mode(c);
    uint16_t addr = get_addr(c, m);

    uint8_t operand = am == AM_ACCUMULATOR ? *get_reg(c, REG_A) : next_byte(c, m);
    uint8_t result = operand >> 1;
    uint8_t carry = get_flag(c, FLAG_C);

    set_bit(&result, 7, carry);

    am == AM_ACCUMULATOR ? set_reg(c, REG_A, result) : mem_set_byte(m, addr, result); 
    
    set_flag(c, FLAG_C, get_bit(operand, 0));
    set_flag(c, FLAG_N, get_bit(operand, 7));
    set_flag(c, FLAG_Z, (result == 0));
}
