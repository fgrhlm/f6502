#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "emu.h"
#include "utils.h"
#include "cpu.h"
#include "mem.h"

emu* create_emu(){
    cpu* c = create_cpu();
    mem* m = create_mem(UINT16_MAX);

    emu* e = malloc(sizeof(emu));
    e->c = c;
    e->m = m;

    return e;
}

void free_emu(emu* e){ 
    free_mem(e->m);
    free_cpu(e->c);
    free(e); 
}

emu_test* parse_test(int argc, char* argv[]){
    emu_test* test = malloc(sizeof(emu_test));
    
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

    return test;
}

void load_test(emu* e, emu_test* t){
    set_pc(e->c, t->pc_start);
    set_reg(e->c, REG_S, t->regs_start[REG_S]);
    set_reg(e->c, REG_A, t->regs_start[REG_A]);
    set_reg(e->c, REG_X, t->regs_start[REG_X]);
    set_reg(e->c, REG_Y, t->regs_start[REG_Y]);
    set_reg(e->c, REG_P, t->regs_start[REG_P]);

    for(int i=0; i<t->mem_start->count; i++){
        uint16_t addr = t->mem_start->bytes[i].addr;
        uint8_t byte = t->mem_start->bytes[i].byte;
        mem_set_byte(e->m, addr, byte);
    } 
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

    emu_test* test = parse_test(argc, argv);
    load_test(e, test);

    e->load_mode = EMU_LOAD_TEST;
    e->run_mode = EMU_RUN_NORMAL;

    while(e->run_mode != EMU_RUN_STOP){
        if(!cpu_op(e->c,e->m)){ 
            e->run_mode = EMU_RUN_STOP;
        }

        if(get_pc(e->c) == test->pc_stop){
            e->run_mode = EMU_RUN_STOP;
        }

        if(e->step > 300){
            e->run_mode = EMU_RUN_STOP;
        }
    }
   
    printf("END PC %d\n", get_pc(e->c));
    free_test(test);
    dump_emu(e); 
    free_emu(e);

    return 0;
}

int main(int argc, char* argv[]){
    int success = run_test(argc, argv);
    return success;
}
