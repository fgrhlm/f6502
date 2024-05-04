#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "utils.h"
#include "cpu.h"
#include "mem.h"

#define BIN_FUNC_TEST "tests/nestest.nes"
#define EMU_MEM_SIZE 70000

enum flow_ctl {prg_cont, prg_stop};

char* emu_get_rom(emu* e){ return e->loaded_bin; }
unsigned long emu_get_step(emu* e){ return e->step; }
emu_mode emu_get_mode(emu* e){ return e->mode; }

void emu_inc_step(emu* e){ e->step++; }
void emu_set_mode(emu* e, emu_mode m){ e->mode = m; }

void print_emu_state(emu* e){
        char* emu_mode_strings[] = { "RUN", "STEP", "STOP" };
        printf("[ROM]: %s\n", emu_get_rom(e));
        printf("[Step]: %lu\n", emu_get_step(e));
        printf("[Mode]: %s\n", emu_mode_strings[emu_get_mode(e)]);
}

emu* create_emu(){
    cpu* c = create_cpu();
    mem* m = create_mem(EMU_MEM_SIZE);

    emu* e = malloc(sizeof(emu));
    e->cpu = c;
    e->mem = m;

    return e;
}

void init_emu(emu* e, char* rom, unsigned int pc){
    e->test_mode = 0;
    set_pc(e->cpu, pc);

    e->mode = STEP;
}

void init_emu_test(emu* e, int argc, char* argv[]){
    e->test_mode = 1;
    cpu* c = e->cpu;
    mem* m = e->mem;
    
    debug_logf("[TEST %s - %s.json]\n", argv[argc-1], argv[argc-2]);

    e->test_file = argv[argc-2];
    e->test_index = argv[argc-1];

    uint16_t test_start = atoi(argv[1]);
    set_pc(c, test_start);

    uint16_t test_stop = atoi(argv[2]);
    e->test_stop = 1;

    uint8_t init_sp = atoi(argv[3]);
    set_reg(c, REG_S, init_sp);
    
    uint8_t init_a = atoi(argv[4]);
    set_reg(c, REG_A, init_a);
    
    uint8_t init_x = atoi(argv[5]);
    set_reg(c, REG_X, init_x);
    
    uint8_t init_y = atoi(argv[6]);
    set_reg(c, REG_Y, init_y);
    
    uint8_t init_p = atoi(argv[7]);
    set_reg(c, REG_P, init_p);

    int write_bytes = atoi(argv[8])*2;

    for(int i=0;i<write_bytes;i++){
        int idx = 9;
        int addr = atoi(argv[idx+i]);
        i++;
        int byte = atoi(argv[idx+i]);
        mem_set_byte(m, addr, byte);
    }
    
    emu_set_mode(e, RUN);
}

void free_emu(emu* e){ 
    free_mem(e->mem);
    free_cpu(e->cpu);
    free(e); 
}


void emu_run(emu* e){
    cpu* c = e->cpu;
    mem* m = e->mem;

    while(emu_get_mode(e) != STOP){
        emu_inc_step(e);
        if(!cpu_op(c,m)){ emu_set_mode(e, STOP); };
        
        if(emu_get_mode(e) == STEP){
            int ch = read_key();
            switch(ch){
                case 'q':
                    emu_set_mode(e, STOP);
                    break;
                case 'r':
                    emu_set_mode(e, RUN);
                    break;
                default:
                    break;
            }
        }

        if(emu_get_step(e) == e->test_stop){ emu_set_mode(e, STOP); }
        if(e->step > 300){ debug_logf("Took too long..\n"); emu_set_mode(e, STOP); }
    }

    debug_logf("Done..\n");
}

int main(int argc, char* argv[]){
    debug_out_init(); 

    emu* emu = create_emu();
    init_emu_test(emu,argc,argv);

    emu_run(emu);
    dump_emu(emu); 
    free_emu(emu);

    return 0;
}
