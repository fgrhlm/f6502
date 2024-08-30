#include "addr.h"
#include "cpu.h"
#include <stdint.h>

void instr_and(cpu *c, mem *m) {
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    set_flag(c, FLAG_N, get_bit(result, 7));

    inc_pc(c);
}
void instr_bit(cpu *c, mem *m) {
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = (byte & acc);

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(byte, 7));
    set_flag(c, FLAG_V, get_bit(byte, 6));

    inc_pc(c);
}
void instr_eor(cpu *c, mem *m) {
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = (byte ^ acc);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));

    inc_pc(c);
}
void instr_ora(cpu *c, mem *m) {
    uint16_t addr = get_addr(c, m);
    uint8_t byte = mem_read(m, addr);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte | acc;

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));

    inc_pc(c);
}
