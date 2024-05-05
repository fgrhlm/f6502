#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct { 
    uint8_t hi; 
    uint8_t lo;
} bytes;

typedef enum { REG_A, REG_X, REG_Y, REG_PL, REG_PH, REG_S, REG_P } reg;
typedef enum { FLAG_C, FLAG_Z, FLAG_I, FLAG_D, FLAG_B, FLAG_X, FLAG_V, FLAG_N } flag;

typedef enum { 
    AM_ACCUMULATOR, AM_IMMEDIATE, AM_ZERO_PAGE, 
    AM_ZERO_PAGE_X,AM_ZERO_PAGE_Y,AM_RELATIVE,
    AM_ABSOLUTE,AM_ABSOLUTE_X,AM_ABSOLUTE_Y,
    AM_ABSOLUTE_INDIRECT,AM_ZERO_PAGE_INDIRECT_X,AM_ZERO_PAGE_INDIRECT_Y,
    AM_IMPLIED,
} addr_mode;

typedef struct {
    uint8_t* bytes;
    unsigned int size;
} mem;

typedef struct {
    uint8_t* regs;
    addr_mode addr_mode;
    uint8_t stop;
} cpu;

typedef enum { RUN, STEP, STOP } emu_mode;

typedef struct {
    cpu* cpu;
    mem* mem;
    
    unsigned long step;
    char* loaded_bin;
    emu_mode mode;
    
    // Test stuff
    uint8_t test_mode;
    uint16_t test_start;
    uint16_t test_stop;
    uint16_t test_stop_pc;

    char* test_file;
    char* test_index;
} emu;

#endif
