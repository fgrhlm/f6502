#ifndef MEM_H
#define MEM_H

#include <stdint.h>

typedef struct {
    uint8_t *bytes;
    unsigned int size;
} mem;

typedef struct {
    uint16_t addr;
    uint8_t byte;
} mem_byte;

mem *create_mem(unsigned int mem_size);
void free_mem(mem *m);
uint8_t mem_get_byte(mem *m, unsigned int p);
void mem_set_byte(mem *m, unsigned int p, uint8_t b);
void reset_mem(mem *m);

#endif
