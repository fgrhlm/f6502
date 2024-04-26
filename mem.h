#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include "types.h"

mem* create_mem(unsigned int mem_size);
void free_mem(mem* m);
uint8_t mem_get_byte(mem* m, unsigned int p);
void mem_set_byte(mem* m, unsigned int p, uint8_t b);

#endif
