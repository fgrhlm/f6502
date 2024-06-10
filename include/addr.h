#ifndef ADDR_H
#define ADDR_H

#include "cpu.h"
#include "mem.h"
#include <stdint.h>

uint16_t immediate_addr(cpu *c);
uint16_t absolute_addr(cpu *c, mem *m);
uint16_t indirect_addr(cpu *c, mem *m);
uint16_t indexed_indirect_addr(cpu *c, mem *m, reg r);
uint16_t relative_addr(cpu *c, mem *m);
uint16_t zero_page_addr(cpu *c, mem *m);
uint16_t get_addr(cpu *c, mem *m);

#endif
