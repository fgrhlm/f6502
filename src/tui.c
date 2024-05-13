#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <panel.h>
#include <stdint.h>
#include <string.h>

#include "types.h"
#include "mem.h"
#include "cpu.h"

cpu* CPU;
mem* MEM;

void finish(int sig){
    endwin();
    exit(sig);
}

void show_reg(WINDOW* w, int y, int x, char* n, uint8_t v){ 
    mvwprintw(w, y, x, "%s", n);
    wattron(w, COLOR_PAIR(3) | A_BOLD );
    mvwprintw(w, y, x+6, "0x%02x", v);
    wattroff(w, COLOR_PAIR(3));
    wattron(w, COLOR_PAIR(4));
    mvwprintw(w, y, x+12, "%03d", v);
    wattroff(w, COLOR_PAIR(4) | A_BOLD);
}

void show_regs(WINDOW* w){
    int align_x = 2;
    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ Regs ]");
    wattroff(w, A_BOLD);
    show_reg(w, 1,align_x,"PCH", *get_reg(CPU, REG_PH));
    show_reg(w, 2,align_x,"PCL", *get_reg(CPU, REG_PL));
    show_reg(w, 3,align_x,"A",   *get_reg(CPU, REG_A));
    show_reg(w, 4,align_x,"X",   *get_reg(CPU, REG_X));
    show_reg(w, 5,align_x,"Y",   *get_reg(CPU, REG_Y));
    show_reg(w, 6,align_x,"S",   *get_reg(CPU, REG_S));
    show_reg(w, 7,align_x,"P",   *get_reg(CPU, REG_P));
    wrefresh(w);
}

void show_flags(WINDOW* w){
    char* flags[] = { "N", "V", "X", "B", "D", "I", "Z", "C" };
    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ Flags ]");
    wattroff(w, A_BOLD);

    int next_skip = 0;
    for(int i=0; i<8; i++){
        int flag = get_bit(*get_reg(CPU, REG_P), i);
        flag ? wattron(w, COLOR_PAIR(2) | A_BOLD) : wattron(w, COLOR_PAIR(1) | A_BOLD);
        mvwprintw(w, 1, (2+i)+next_skip, "%d", 0);
        flag ? wattroff(w, COLOR_PAIR(2) | A_BOLD) : wattroff(w, COLOR_PAIR(1) | A_BOLD);
        mvwprintw(w, 2, (2+i)+next_skip, "%s", flags[i]);
        next_skip++;
    }
    wrefresh(w);
}

void show_cycles(WINDOW* w){
    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ Timing ]");
    wattroff(w, A_BOLD);
    mvwprintw(w, 1, 2, "EMU");
    mvwprintw(w, 2, 2, "CPU");
    mvwprintw(w, 3, 2, "Time");
    mvwprintw(w, 1, 8, "%d", 0);
    mvwprintw(w, 2, 8, "%d", 0);
    mvwprintw(w, 3, 8, "%d", 0);
    wrefresh(w);
}

void show_asm(WINDOW* w){
    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ ASM ] ");
    wattroff(w, A_BOLD);
    wrefresh(w);
}

void show_log(WINDOW* w){
    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ Log ]");
    wattroff(w, A_BOLD);
    wrefresh(w);
}

void show_mem(WINDOW* w){
    int max_y, max_x;
    getmaxyx(w, max_y, max_x);

    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ RAM ]");
    mvwprintw(w, 0, max_x-17, "[ Page: ");
    mvwprintw(w, 0, max_x-9, "0x%04x ]", 0);
    wattroff(w, A_BOLD);
    wrefresh(w);
}

void show_info(WINDOW* w){
    int max_y, max_x;
    getmaxyx(w, max_y, max_x);
    box(w,0,0);
    wattron(w, A_BOLD);
    mvwprintw(w, 0, 1, "[ Debugger ]");
    wattroff(w, A_BOLD);
    mvwprintw(w, 1, 2, "ROM:");
    mvwprintw(w, 2, 2, "Breakpoints:");

    wrefresh(w);
}

void show_main(WINDOW* w){
    wrefresh(w);
}

void init_curses(){
    signal(SIGINT, finish);
    initscr();
    keypad(stdscr, 1);
    nonl();
    cbreak();
    noecho();
    clear();

    start_color();
    use_default_colors();

    // FG / BG
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_BLUE, -1);
    init_pair(5, COLOR_CYAN, -1);
    init_pair(6, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_WHITE, -1);

    // BG / FG
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(9, COLOR_BLACK, COLOR_GREEN);
    init_pair(10, COLOR_BLACK, COLOR_YELLOW);
    init_pair(11, COLOR_BLACK, COLOR_BLUE);
    init_pair(12, COLOR_BLACK, COLOR_CYAN);
    init_pair(13, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(14, COLOR_BLACK, COLOR_WHITE);
}

typedef struct {
    WINDOW* win;
    int h, w, y, x;
    void (*draw_func)(WINDOW*);
} dwin;

dwin* new_dwin(int h, int w, int y, int x, void (*draw_func)(WINDOW*)){
    dwin* dw = malloc(sizeof(dwin));
    *dw = (dwin){
        .h = h,
        .w = w,
        .y = y,
        .x = x,
        .draw_func = draw_func,
        .win = newwin(h,w,y,x)
    };

    return dw;
}

void render_dwin(dwin* d){ d->draw_func(d->win); }

int main(int argc, char** argv){
    CPU = create_cpu();
    MEM = create_mem(UINT16_MAX);

    init_curses();
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int low_row = 9;
    int low_row_w = (int)(max_x / 3);
    dwin* windows[] = {
        new_dwin(max_y, max_x, 0, 0, &show_main),
        new_dwin(9, 19, 0, 0, &show_regs),
        new_dwin(4, 19, 0, 19, &show_flags),
        new_dwin(5, 19, 4, 19, &show_cycles),
        new_dwin((max_y-low_row), low_row_w, low_row, 0, &show_asm),
        new_dwin((max_y-low_row), low_row_w, low_row, low_row_w, &show_log),
        new_dwin((max_y-low_row), low_row_w, low_row, low_row_w*2, &show_mem),
        new_dwin(9, (max_x - 19*2), 0, 19*2, &show_info)
    };

    size_t win_len = sizeof(windows) / sizeof(dwin*);

    refresh();

    for(int i=0; i < win_len; i++){ render_dwin(windows[i]); }
    
    refresh();
    getch();
    
    for(int i=0; i < win_len; i++){
        delwin(windows[i]->win);
        free(windows[i]);
    }
    
    free_mem(MEM);
    free_cpu(CPU);
    finish(0);
}
