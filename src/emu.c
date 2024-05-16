#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "emu.h"
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
