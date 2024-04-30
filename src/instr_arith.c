#include <stdint.h>
#include "cpu.h"
#include "utils.h"

bytes bcd_convert(uint8_t x){
    uint8_t hi = ((x >> 4) & 0xF);
    uint8_t lo = ((x >> 0) & 0xF);
    uint8_t carry = (lo > 9);    

    hi = (hi > 9 ? hi - 10 : hi) + carry;
    lo = carry ? lo-10 : lo;

    bytes num = {.hi = hi, .lo = lo};
    return num;
}

uint8_t bcd_add(cpu* c, uint8_t x, uint8_t y){
    debug_logf("\tBCD START -> %x + %x\n", x, y);
    uint8_t o_carry, i_carry;
    uint8_t sum, sum_hi, sum_lo, sum_carry;
    i_carry = get_flag(c, FLAG_C);

    bytes d_x = bcd_convert(x);
    bytes d_y = bcd_convert(y);

    debug_logf("\tBCD CONVERT -> %x + %x\n", (d_x.hi << 4) | d_x.lo, (d_y.hi << 4) | d_y.lo);
    
    sum_lo = (d_x.lo + d_y.lo);
    if(sum_lo > 9){
        sum_carry = 1;
        sum_lo = sum_lo - 10;
    }else{
        sum_carry = 0;
    }

    sum_hi = (d_x.hi + d_y.hi) + sum_carry;
    if(sum_hi > 9){
        o_carry = 1;
        sum_hi = sum_hi - 10;
    }else{
        o_carry = 0;
    }

    sum = ((sum_hi << 4) | sum_lo) + i_carry;
    debug_logf("\tBCD SUM -> %x\n", sum);
    uint8_t x_sign = get_bit(y, 7);
    uint8_t sum_sign = get_bit(sum,7);
    
    set_flag(c, FLAG_C, o_carry);
    set_flag(c, FLAG_Z, (sum == 0));
    set_flag(c, FLAG_N, get_bit(sum, 7));
    set_flag(c, FLAG_V, x_sign != sum_sign);
   
    return sum;
}

uint8_t bin_add(cpu* c, uint8_t x, uint8_t y){
    uint8_t i_carry = get_flag(c, FLAG_C);
    uint8_t c1, c2, o_carry;
    uint8_t res;
   
    c1 = __builtin_add_overflow(x, y, &res);
    c2 = __builtin_add_overflow(res, i_carry, &res);
    o_carry = c1 | c2;

    uint8_t x_sign = get_bit(x, 7);
    uint8_t res_sign = get_bit(res,7);
    
    set_flag(c, FLAG_C, o_carry); 
    set_flag(c, FLAG_Z, (res == 0));
    set_flag(c, FLAG_N, get_bit(res, 7));
    set_flag(c, FLAG_V, x_sign != res_sign);

    debug_logf("\tBINADC: %x + %x = %x", x, y, res);
    return res;
}

uint8_t add(cpu*c, uint8_t x, uint8_t y){
    uint8_t dec = get_flag(c, FLAG_D);
    uint8_t sum = dec ? bcd_add(c, x, y) : bin_add(c, x, y);
    
    return sum;
}

void instr_adc(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t res = add(c, acc, byte);

    set_reg(c, REG_A, res);
}
void instr_cmp(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = acc - byte;

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_C, byte <= acc);
}
void instr_cpx(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t reg = *get_reg(c, REG_X);
    uint8_t result = reg - byte;

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_C, byte <= reg);
}
void instr_cpy(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t reg = *get_reg(c, REG_Y);
    uint8_t result = reg - byte;

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_C, byte <= reg);
}

uint8_t sub(cpu* c, uint8_t x, uint8_t y){
    uint8_t i_carry = !get_flag(c, FLAG_C);
    uint8_t c1, c2, o_carry;
    uint8_t res;
   
    c1 = __builtin_sub_overflow(x, y, &res);
    c2 = __builtin_sub_overflow(res, i_carry, &res);
    o_carry = c1 | c2;

    uint8_t x_sign = get_bit(x, 7);
    uint8_t res_sign = get_bit(res,7);
    
    set_flag(c, FLAG_C, o_carry); 
    set_flag(c, FLAG_Z, (res == 0));
    set_flag(c, FLAG_N, get_bit(res, 7));
    set_flag(c, FLAG_V, x_sign != res_sign);

    return res;
}

void instr_sbc(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t res = sub(c, byte, acc);

    set_reg(c, REG_A, res);
}

void instr_anc(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    uint8_t v_bit = get_bit(result, 7);
    set_flag(c, FLAG_N, v_bit);
    set_flag(c, FLAG_C, v_bit);
}

void instr_arr(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;
    
    uint8_t i_carry = get_flag(c, FLAG_C);
    //uint8_t o_carry = get_bit(result, 0);
    
    result = result >> 1;
    set_bit(&result, 7, i_carry);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    
    // FIX DECIMAL MODE
    uint8_t v_bit = get_bit(result, 7);
    set_flag(c, FLAG_N, v_bit);
};

void instr_asr(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;
    
    //uint8_t i_carry = get_flag(c, FLAG_C);
    uint8_t o_carry = get_bit(result, 0);
    
    result = result >> 1;
    set_bit(&result, 7, 0);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    set_flag(c, FLAG_N, 0);
    set_flag(c, FLAG_C, o_carry);   
};

void instr_sbx(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t a = *get_reg(c, REG_A);
    uint8_t x = *get_reg(c, REG_X);

    uint8_t res = sub(c, byte, (a & x));

    set_reg(c, REG_X, res);
};

void instr_xaa(cpu* c, mem* m){};
void instr_dcp(cpu* c, mem* m){};
void instr_isc(cpu* c, mem* m){};
void instr_rla(cpu* c, mem* m){};
void instr_rra(cpu* c, mem* m){};
void instr_slo(cpu* c, mem* m){};
void instr_sre(cpu* c, mem* m){};
