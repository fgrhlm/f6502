#include <stdint.h>
#include "cpu.h"
#include "utils.h"

uint8_t bcd_add(cpu* c, uint8_t x, uint8_t y){
    uint8_t hi, lo, out_carry, in_carry, sum, temp_sum;

    in_carry = get_flag(c, FLAG_C);
    
    out_carry = 0;
    hi = ((x & 0xF0) + (y & 0xF0)) >> 4;
    lo = (x & 0x0F) + (y & 0x0F) + in_carry;

    temp_sum = ((hi << 4) | lo);

    if(lo >= 10){ 
        lo = ((lo + 6) & 0x0F);
        hi++;
    }

    temp_sum = ((hi << 4) | lo);
    uint8_t v_flag = get_bit((x^temp_sum) & (y^temp_sum), 7);
    
    if(hi >= 10){ hi = ((hi + 6) & 0x0F); out_carry = 1; }

    sum = ((hi << 4) | lo);
  
    set_flag(c, FLAG_C, out_carry);
    set_flag(c, FLAG_N, get_bit(temp_sum, 7));
    set_flag(c, FLAG_Z, sum == 0);
    set_flag(c, FLAG_V, v_flag);
    
    return sum;
}

uint8_t bin_add(cpu* c, uint8_t x, uint8_t y){
    uint8_t i_carry = get_flag(c, FLAG_C);
    uint8_t c1, c2, o_carry;
    uint8_t res;
   
    c1 = __builtin_add_overflow(x, y, &res);
    c2 = __builtin_add_overflow(res, i_carry, &res);
    o_carry = c1 | c2;

    uint8_t v_flag = get_bit((x^res) & (y^res), 7);

    set_flag(c, FLAG_C, o_carry); 
    set_flag(c, FLAG_Z, (res == 0));
    set_flag(c, FLAG_N, get_bit(res, 7));
    set_flag(c, FLAG_V, v_flag);

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

uint8_t bin_sub(cpu* c, uint8_t x, uint8_t y){
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

uint8_t bcd_sub(cpu* c, uint8_t x, uint8_t y){
    uint16_t res, lo;
    uint8_t in_carry = get_flag(c, FLAG_C);

    lo = (x & 0x0F) - (y & 0x0F) + (in_carry - 1);
    res = x - y + (in_carry - 1);
    
    if(res < 0){ res = res - 0x60; }
    if(lo < 0){ res = res - 0x06; }
    
    return (res & 0x00FF);
}

uint8_t sub(cpu*c, uint8_t x, uint8_t y){
    uint8_t dec = get_flag(c, FLAG_D);
    dec ? debug_logf("\tDECIMAL SBC\n") : debug_logf("\tBIN SBC\n");
    uint8_t sum = dec ? bcd_sub(c, x, y) : bin_sub(c, x, y);
    
    return sum;
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
