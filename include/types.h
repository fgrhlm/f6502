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
    uint16_t addr;
    uint8_t byte;
} mem_byte;

typedef struct {
    uint8_t* regs;
    addr_mode addr_mode;
    uint8_t stop;
} cpu;

typedef enum { EMU_LOAD_TEST, EMU_LOAD_NORMAL, EMU_LOAD_DEBUG } emu_load_mode;
typedef enum { EMU_RUN_NORMAL, EMU_RUN_STEP, EMU_RUN_STOP, EMU_RUN_BREAKPOINT } emu_run_mode;

// Container for Tom Harts processor tests
typedef struct {
    unsigned int count;
    mem_byte* bytes;
} mem_byte_list;

typedef struct {
    uint16_t pc_start;
    uint16_t pc_stop;

    uint8_t regs_start[7];
    mem_byte_list* mem_start;

    char* filename;
    char* index;
} emu_test;

typedef struct {
    uint64_t date_created;
    uint64_t date_modified;
    uint16_t pc_offset;
} emu_rom_meta;

typedef struct {
    char* filename;
    uint8_t* data;
    emu_rom_meta* meta;
} emu_rom;

typedef struct {
    cpu* c;
    mem* m;
    
    emu_load_mode load_mode;
    emu_run_mode run_mode;
    
    unsigned long step;
} emu;

#endif
