#ifndef EMU_H
#define EMU_H

#include <termios.h>
#include <unistd.h>

#include "types.h"

void load_test(char* fpath, cpu* c, mem* m);
void load_bin(char* fpath, mem* mem, unsigned int offset);

emu* create_emu();
void free_emu(emu* e);

int run_test(int argc, char* argv[]);

#endif
