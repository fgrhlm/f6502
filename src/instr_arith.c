#include "addr.h"
#include "cpu.h"
#include "mem.h"
#include <stdint.h>
#include <stdio.h>

uint8_t bcd_add(cpu *c, uint8_t x, uint8_t y) {
  uint8_t hi, lo, out_carry, in_carry, sum, temp_sum, z_flag;

  in_carry = get_flag(c, FLAG_C);
  out_carry = 0;

  z_flag = (x + y + in_carry) & 255;
  set_flag(c, FLAG_Z, z_flag == 0);

  hi = ((x & 0xF0) + (y & 0xF0)) >> 4;
  lo = (x & 0x0F) + (y & 0x0F) + in_carry;

  temp_sum = ((hi << 4) | lo);

  if (lo >= 10) {
    lo = ((lo + 6) & 0x0F);
    hi++;
  }

  temp_sum = ((hi << 4) | lo);

  uint8_t v_flag = get_bit((x ^ temp_sum) & (y ^ temp_sum), 7);

  if (hi >= 10) {
    hi = ((hi + 6) & 0x0F);
    out_carry = 1;
  }

  sum = ((hi << 4) | lo);

  set_flag(c, FLAG_C, out_carry);
  set_flag(c, FLAG_N, get_bit(temp_sum, 7));
  set_flag(c, FLAG_V, v_flag);

  return sum;
}

uint8_t bin_add(cpu *c, uint8_t x, uint8_t y) {
  uint8_t i_carry = get_flag(c, FLAG_C);
  uint8_t c1, c2, o_carry;
  uint8_t res;

  c1 = __builtin_add_overflow(x, y, &res);
  c2 = __builtin_add_overflow(res, i_carry, &res);
  o_carry = c1 | c2;

  uint8_t v_flag = get_bit((x ^ res) & (y ^ res), 7);

  set_flag(c, FLAG_C, o_carry);
  set_flag(c, FLAG_Z, (res == 0));
  set_flag(c, FLAG_N, get_bit(res, 7));
  set_flag(c, FLAG_V, v_flag);

  return res;
}

uint8_t add(cpu *c, uint8_t x, uint8_t y) {
  uint8_t dec = get_flag(c, FLAG_D);
  uint8_t sum = dec ? bcd_add(c, x, y) : bin_add(c, x, y);
  return sum;
}

void instr_adc(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t res = add(c, acc, byte);

  set_reg(c, REG_A, res);
  inc_pc(c);
}

void instr_cmp(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t result = acc - byte;

  set_flag(c, FLAG_Z, result == 0);
  set_flag(c, FLAG_N, get_bit(result, 7));
  set_flag(c, FLAG_C, byte <= acc);
  inc_pc(c);
}
void instr_cpx(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t reg = *get_reg(c, REG_X);
  uint8_t result = reg - byte;

  set_flag(c, FLAG_Z, result == 0);
  set_flag(c, FLAG_N, get_bit(result, 7));
  set_flag(c, FLAG_C, byte <= reg);
  inc_pc(c);
}
void instr_cpy(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t reg = *get_reg(c, REG_Y);
  uint8_t result = reg - byte;

  set_flag(c, FLAG_Z, result == 0);
  set_flag(c, FLAG_N, get_bit(result, 7));
  set_flag(c, FLAG_C, byte <= reg);
  inc_pc(c);
}

uint8_t sub(cpu *c, uint8_t x, uint8_t y) {
  uint8_t dec, carry_in, carry_out;
  int16_t res, t_res;

  dec = get_flag(c, FLAG_D);
  carry_in = get_flag(c, FLAG_C);

  __builtin_sub_overflow(x, y, &res);
  __builtin_sub_overflow(res, !carry_in, &res);

  set_flag(c, FLAG_N, get_bit(res, 7));
  set_flag(c, FLAG_Z, !(res & 0xFF));
  uint8_t v_flag = get_bit((x ^ res), 7) && get_bit((x ^ y), 7);
  set_flag(c, FLAG_V, v_flag);

  if (dec) {
    t_res = (uint16_t)(x & 0x0F) - (uint16_t)(y & 0x0F) - !carry_in;
    if (t_res < 0) {
      t_res = ((t_res - 6) & 0x0F) - 16;
    }
    res = (uint16_t)(x & 0xF0) - (uint16_t)(y & 0xF0) + t_res;
    if (res < 0) {
      res = res - 0x60;
    }
  }

  carry_out = !(res < 0);
  set_flag(c, FLAG_C, carry_out);

  res = res & 0x00FF;

  return res;
}

void instr_sbc(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t res = sub(c, acc, byte);

  set_reg(c, REG_A, res);
  inc_pc(c);
}

void instr_anc(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t result = byte & acc;

  set_reg(c, REG_A, result);
  set_flag(c, FLAG_Z, (result == 0));
  uint8_t v_bit = get_bit(result, 7);
  set_flag(c, FLAG_N, v_bit);
  set_flag(c, FLAG_C, v_bit);
  inc_pc(c);
}

void instr_arr(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t result = byte & acc;

  uint8_t i_carry = get_flag(c, FLAG_C);
  // uint8_t o_carry = get_bit(result, 0);

  result = result >> 1;
  set_bit(&result, 7, i_carry);

  set_reg(c, REG_A, result);
  set_flag(c, FLAG_Z, (result == 0));

  // FIX DECIMAL MODE
  uint8_t v_bit = get_bit(result, 7);
  set_flag(c, FLAG_N, v_bit);
  inc_pc(c);
}

void instr_asr(cpu *c, mem *m) {
  uint8_t byte = next_byte(c, m);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t result = byte & acc;

  // uint8_t i_carry = get_flag(c, FLAG_C);
  uint8_t o_carry = get_bit(result, 0);

  result = result >> 1;
  set_bit(&result, 7, 0);

  set_reg(c, REG_A, result);
  set_flag(c, FLAG_Z, (result == 0));
  set_flag(c, FLAG_N, 0);
  set_flag(c, FLAG_C, o_carry);
  inc_pc(c);
}

void instr_sbx(cpu *c, mem *m) {
  uint16_t addr = get_addr(c, m);
  int8_t byte = (int8_t)mem_get_byte(m, addr);

  int8_t a = (int8_t)*get_reg(c, REG_A);
  int8_t x = (int8_t)*get_reg(c, REG_X);

  int8_t res = ((a & x) - byte);

  set_reg(c, REG_X, (uint8_t)res);

  // set_flag(c, FLAG_C, );
  set_flag(c, FLAG_N, get_bit(res, 7));
  set_flag(c, FLAG_Z, res == 0);
  inc_pc(c);
}

void instr_xaa(cpu *c, mem *m) {
  // TODO
}

void instr_dcp(cpu *c, mem *m) {
  uint16_t addr = get_addr(c, m);
  uint8_t byte = mem_get_byte(m, addr);
  uint8_t acc = *get_reg(c, REG_A);

  byte = byte - 1;
  mem_set_byte(m, addr, byte);

  uint8_t res = acc - byte;
  set_flag(c, FLAG_Z, res == 0);
  set_flag(c, FLAG_N, get_bit(res, 7));
  set_flag(c, FLAG_C, byte <= acc);
  inc_pc(c);
}

void instr_isc(cpu *c, mem *m) {
  uint8_t res, byte, acc;
  uint16_t addr = get_addr(c, m);
  acc = *get_reg(c, REG_A);
  byte = mem_get_byte(m, addr);

  byte++;
  mem_set_byte(m, addr, byte);

  res = sub(c, acc, byte);
  set_reg(c, REG_A, res);

  inc_pc(c);
}

void instr_rla(cpu *c, mem *m) {
  uint16_t addr = get_addr(c, m);
  uint8_t byte = mem_get_byte(m, addr);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t carry_in = get_flag(c, FLAG_C);

  set_flag(c, FLAG_C, get_bit(byte, 7));

  byte = (byte << 1);
  set_bit(&byte, 0, carry_in);
  mem_set_byte(m, addr, byte);

  uint8_t result = byte & acc;
  set_reg(c, REG_A, result);

  set_flag(c, FLAG_N, get_bit(result, 7));
  set_flag(c, FLAG_Z, result == 0);
  inc_pc(c);
}

void instr_rra(cpu *c, mem *m) {
  uint16_t addr = get_addr(c, m);
  uint8_t byte = mem_get_byte(m, addr);
  uint8_t acc = *get_reg(c, REG_A);
  uint8_t carry_in = get_flag(c, FLAG_C);

  set_flag(c, FLAG_C, get_bit(byte, 0));

  byte = (byte >> 1);
  set_bit(&byte, 7, carry_in);
  mem_set_byte(m, addr, byte);

  uint8_t res = add(c, acc, byte);
  set_reg(c, REG_A, res);
  inc_pc(c);
}

void instr_slo(cpu *c, mem *m) {
  uint16_t addr = get_addr(c, m);
  uint8_t byte = mem_get_byte(m, addr);
  uint8_t acc = *get_reg(c, REG_A);

  set_flag(c, FLAG_C, get_bit(byte, 7));

  byte = (byte << 1);
  set_bit(&byte, 0, 0);
  mem_set_byte(m, addr, byte);

  uint8_t result = byte | acc;
  set_reg(c, REG_A, result);

  set_flag(c, FLAG_N, get_bit(result, 7));
  set_flag(c, FLAG_Z, result == 0);
  inc_pc(c);
}

void instr_sre(cpu *c, mem *m) {
  uint16_t addr = get_addr(c, m);
  uint8_t byte = mem_get_byte(m, addr);
  uint8_t acc = *get_reg(c, REG_A);

  set_flag(c, FLAG_C, get_bit(byte, 0));

  byte = (byte >> 1);
  set_bit(&byte, 7, 0);
  mem_set_byte(m, addr, byte);

  uint8_t result = byte ^ acc;
  set_reg(c, REG_A, result);

  set_flag(c, FLAG_N, get_bit(result, 7));
  set_flag(c, FLAG_Z, result == 0);
  inc_pc(c);
}
