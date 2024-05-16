#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "types.h"

#define CONSOLE_CLEAR "\e[1;1H\e[2J"

char* addressing_mode_to_str(addr_mode am);
char* opcode_to_str(uint8_t op);

uint16_t merge_bytes(uint8_t hi, uint8_t lo);
bytes split_addr(uint16_t v);

#endif
