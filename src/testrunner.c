#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "emu.h"
#include "cpu.h"
#include "mem.h"

void load_test(char* fpath, cpu* c, mem* m){
    //emu_test* test = malloc(sizeof(emu_test));
   
    /*
    // Parse test filename and test index
    test->filename = argv[argc-2];
    test->index = argv[argc-1];

    // Parse program counter start and stop points
    test->pc_start = atoi(argv[1]);
    test->pc_stop = atoi(argv[2]);

    // Parse registers
    test->regs_start[REG_S] = atoi(argv[3]);
    test->regs_start[REG_A] = atoi(argv[4]);
    test->regs_start[REG_X] = atoi(argv[5]);
    test->regs_start[REG_Y] = atoi(argv[6]);
    test->regs_start[REG_P] = atoi(argv[7]);
    
    // Parse list of initial bytes in mem
    test->mem_start = malloc(sizeof(mem_byte_list));
    int mem_start_len = atoi(argv[8]);
    test->mem_start->count = mem_start_len;
    test->mem_start->bytes = calloc(mem_start_len, sizeof(mem_byte));

    for(int i=0;i<(mem_start_len * 2);i+=2){
        int idx = 9;
        test->mem_start->bytes[i].addr = atoi(argv[idx+i]);
        test->mem_start->bytes[i].byte = atoi(argv[(idx+i)+1]);
    }

    set_pc(e->c, test->pc_start);
    set_reg(e->c, REG_S, test->regs_start[REG_S]);
    set_reg(e->c, REG_A, test->regs_start[REG_A]);
    set_reg(e->c, REG_X, test->regs_start[REG_X]);
    set_reg(e->c, REG_Y, test->regs_start[REG_Y]);
    set_reg(e->c, REG_P, test->regs_start[REG_P]);

    for(int i=0; i<test->mem_start->count; i++){
        uint16_t addr = test->mem_start->bytes[i].addr;
        uint8_t byte = test->mem_start->bytes[i].byte;
        mem_set_byte(e->m, addr, byte);
    }
    */
}

void free_test(emu_test* test){
    for(int i=0; i<test->mem_start->count; i++){
        free(&test->mem_start->bytes[i]);
    }

    free(test->mem_start);
    free(test); 
}

int run_test(int argc, char* argv[]){
    emu* e = create_emu();

    e->load_mode = EMU_LOAD_TEST;
    e->run_mode = EMU_RUN_NORMAL;

    return 0;
}

int main(int argc, char* argv[]){
    return 0;
}
