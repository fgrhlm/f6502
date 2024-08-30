#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bin.h"
#include "cpu.h"
#include "mem.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("please specify bin file and offset.\n");
        exit(1);
    }

    cpu c;
    mem *m = create_mem(65536);
    reset_cpu(&c);
    reset_mem(m);

    uint16_t offset = atoi(argv[2]);
    uint16_t start_pc = atoi(argv[3]);
    load_bin(argv[1], m, offset);
    set_pc(&c, start_pc);
    printf("bin: %s\noffset:%x\npc: %x\n", argv[1],offset,start_pc);

    //int msec = 1;
    unsigned long ticks = 0;

    int err = 0;

    while (1) {
        cpu_tick(&c, m);
        //usleep(msec * 100);
        ticks++;
        if(get_pc(&c) == 0x3469){
            break;
        }

        if(ticks > UINT64_MAX){
            err = 1;
            break;
        }
    }

    switch(err){
        case 1:
            printf("ERROR: long overflow..\n");
            break;
        default:
            printf("done!\n");
            break;
    }

    free_mem(m);
    return 0;
}
