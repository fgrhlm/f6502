#include <stdlib.h>
#include <stdint.h>

#include "mem.h"
#include "types.h"

mem* create_mem(unsigned int mem_size){
    mem* m = malloc(sizeof(mem)); 
    m->size = mem_size;
    m->bytes = calloc(mem_size, sizeof(uint8_t));
    return m;
}

void free_mem(mem* m){
    free(m->bytes);
    free(m);
}

uint8_t mem_get_byte(mem* m, unsigned int p){
    uint8_t byte = m->bytes[p];
    return byte;
}

void mem_set_byte(mem* m, unsigned int p, uint8_t b){
    m->bytes[p] = b;
}
