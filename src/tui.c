#include <curses.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bin.h"
#include "cpu.h"
#include "mem.h"

#define STR_BIN "BIN: %s"
#define STR_CYCLES "CYCLES: %d"
#define STR_REG "REG %s:\t%05dd    %02xh"
#define STR_PC "PC: %05dd %04xh"
#define STR_TICKS "TICKS: %lu"

static void finish(int sig) {
    endwin();
    exit(0);
}

static void init_all(void) {
    signal(SIGINT, finish);
    initscr();
    keypad(stdscr, TRUE);
    nonl();
    cbreak();
    noecho();

    if (has_colors()) {
        start_color();

        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }
}

void update_registers(cpu *c) {
    uint8_t ra, rx, ry, rs, rp;
    uint16_t pc;

    pc = get_pc(c);
    ra = *get_reg(c, REG_A);
    rx = *get_reg(c, REG_X);
    ry = *get_reg(c, REG_Y);
    rs = *get_reg(c, REG_S);
    rp = *get_reg(c, REG_P);

    mvprintw(2, 0, STR_PC, pc, pc);
    mvprintw(4, 0, STR_REG, "A", ra, ra);
    mvprintw(5, 0, STR_REG, "X", rx, rx);
    mvprintw(6, 0, STR_REG, "Y", ry, ry);
    mvprintw(7, 0, STR_REG, "S", rs, rs);
    mvprintw(8, 0, STR_REG, "P", rp, rp);
}

void update_state(cpu *c, char *bin, unsigned long ticks) {
    mvprintw(0, 0, STR_BIN, bin);
    mvprintw(1, 0, STR_TICKS, ticks);
    update_registers(c);
}

typedef struct {
    int max_y, max_x;
} win_info;

void update_win_info(win_info *winfo) {
    getmaxyx(stdscr, winfo->max_y, winfo->max_x);
}

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
    printf("set pc to %d\n", start_pc);

    win_info winfo;
    update_win_info(&winfo);

    init_all();

    //int msec = 1;
    unsigned long ticks = 0;

    while (1) {
        update_win_info(&winfo);
        update_state(&c, argv[1], ticks);
        refresh();
        cpu_tick(&c, m);
        //usleep(msec * 100);
        ticks++;
        if(get_pc(&c) == 0x3469){
            finish(0);
        }
    }

    free_mem(m);
    finish(0);
    return 0;
}
