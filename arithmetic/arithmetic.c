#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum { REG_A, REG_X, REG_Y, REG_PL, REG_PH, REG_S, REG_P } reg;
typedef enum { FLAG_C, FLAG_Z, FLAG_I, FLAG_D, FLAG_B, FLAG_X, FLAG_V, FLAG_N } flag;

typedef struct { uint8_t* regs; } cpu;

char* utobstr(uint8_t n){
    unsigned int len = 8;
    char* str = calloc(len,sizeof(char));
    
    for(int i=len-1; i>=0; i--){
        char bit = n % 2 == 0 ? '0' : '1';
        n = n/2;
        str[i] = bit;
    }

    return str;
}

uint8_t get_bit(uint8_t b, uint8_t i){ return (b >> i) & 1; }
void set_bit(uint8_t* b, uint8_t i, uint8_t n){ *b = n ? (*b | (1 << i)) : (*b & (~(1 << i))); }

uint8_t* get_reg(cpu* c, reg r){ return &c->regs[r]; }
void set_reg(cpu* c, reg r, uint8_t b){ c->regs[r] = b; }

uint8_t* get_flags(cpu* c){ return &c->regs[REG_P]; }
uint8_t get_flag(cpu* c, flag f) { return get_bit(c->regs[REG_P], f); }
void set_flag(cpu* c, flag f, uint8_t n){ set_bit(&c->regs[REG_P], f, n); }

uint8_t add(cpu* c, uint8_t x, uint8_t y){
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

    return res;
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

int main(int argc, char** argv){
    cpu* c = malloc(sizeof(cpu)); 
    c->regs = calloc(7, sizeof(uint8_t));

    printf("42 -> %s | 58 -> %s\n", utobstr(42), utobstr(58));
    free(c->regs);
    free(c);
}
