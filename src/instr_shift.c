#include "addr.h"
#include "cpu.h"
#include "mem.h"
#include <stdint.h>

void instr_asl(cpu *c, mem *m) {
    addr_mode am = get_addr_mode(c);
    uint16_t addr;
    uint8_t byte;
    if (am == AM_ACCUMULATOR) {
        byte = *get_reg(c, REG_A);
    } else {
        addr = get_addr(c, m);
        byte = mem_get_byte(m, addr);
    };

    set_flag(c, FLAG_C, get_bit(byte, 7));

    uint8_t result = byte << 1;
    set_bit(&result, 0, 0);

    (am == AM_ACCUMULATOR) ? set_reg(c, REG_A, result)
                           : mem_set_byte(m, addr, result);

    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_Z, (result == 0));
    inc_pc(c);
}

void instr_lsr(cpu *c, mem *m) {
    addr_mode am = get_addr_mode(c);
    uint16_t addr;
    uint8_t byte;
    if (am == AM_ACCUMULATOR) {
        byte = *get_reg(c, REG_A);
    } else {
        addr = get_addr(c, m);
        byte = mem_get_byte(m, addr);
    };

    set_flag(c, FLAG_C, get_bit(byte, 0));

    uint8_t result = byte >> 1;
    set_bit(&result, 7, 0);

    (am == AM_ACCUMULATOR) ? set_reg(c, REG_A, result)
                           : mem_set_byte(m, addr, result);

    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_Z, (result == 0));
    inc_pc(c);
}

void instr_rol(cpu *c, mem *m) {
    addr_mode am = get_addr_mode(c);
    uint8_t carry = get_flag(c, FLAG_C);

    uint16_t addr;
    uint8_t byte, result;
    if (am == AM_ACCUMULATOR) {
        byte = *get_reg(c, REG_A);
    } else {
        addr = get_addr(c, m);
        byte = mem_get_byte(m, addr);
    };

    set_flag(c, FLAG_C, get_bit(byte, 7));
    result = (byte << 1);

    set_bit(&result, 0, carry);

    (am == AM_ACCUMULATOR) ? set_reg(c, REG_A, result)
                           : mem_set_byte(m, addr, result);

    set_flag(c, FLAG_N, get_bit(byte, 6));
    set_flag(c, FLAG_Z, result == 0);
    inc_pc(c);
}

void instr_ror(cpu *c, mem *m) {
    addr_mode am = get_addr_mode(c);
    uint8_t carry = get_flag(c, FLAG_C);

    uint16_t addr;
    uint8_t byte, result;
    if (am == AM_ACCUMULATOR) {
        byte = *get_reg(c, REG_A);
    } else {
        addr = get_addr(c, m);
        byte = mem_get_byte(m, addr);
    };

    set_flag(c, FLAG_C, get_bit(byte, 0));
    result = (byte >> 1);

    set_bit(&result, 7, carry);

    (am == AM_ACCUMULATOR) ? set_reg(c, REG_A, result)
                           : mem_set_byte(m, addr, result);

    set_flag(c, FLAG_N, carry);
    set_flag(c, FLAG_Z, result == 0);
    inc_pc(c);
}
