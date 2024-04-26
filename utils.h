#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "types.h"

#define CONSOLE_CLEAR "\e[1;1H\e[2J"
#define LOG_FILE "tests/logs/log"

char* utobstr(uint8_t n);
char* addressing_mode_to_str(addr_mode am);
char* opcode_to_str(uint8_t op);
void print_bin(uint8_t n);
void print_reg_8(char* n, uint8_t r);
void print_reg_16(char* n, uint16_t r);
void print_status(cpu* c);
void print_cpu_state(cpu* c, mem* m);
void print_mem(mem* m);
void clearc();
void load_bin(char* fpath, mem* mem, unsigned int offset);
int read_key();
void debug_out_init(char* fn);
void debug_out(char* fn, const char* fmt, ...);

void dump_emu(emu* e);
void log_regs(cpu* c, mem* m);
void log_cpu_op(cpu* c, mem* m);

uint16_t merge_bytes(uint8_t hi, uint8_t lo);
bytes split_addr(uint16_t v);

#endif
