#ifndef EMU_H
#define EMU_H

#include <termios.h>
#include <unistd.h>

#include "types.h"

emu* create_emu();
void free_emu(emu* e);

emu_test* parse_test(int argc, char* argv[]);
void load_test(emu* e, emu_test* t);
void free_test(emu_test* test);

int run_test(int argc, char* argv[]);

#endif
