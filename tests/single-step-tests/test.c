#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <json_visit.h>

#include "cpu.h"
#include "mem.h"

typedef enum { TEST_PASS, TEST_FAIL } test_result;
typedef enum { C_READ, C_WRITE } cycle_type;

typedef struct {
    int addr, val;
    cycle_type t;
} cycle;

typedef struct {
    int addr, val;
} ram_byte;

typedef struct {
    int pc, s, a, x, y, p;
    int ram_len;
    ram_byte *ram;
} test_state;

typedef struct {
    test_state initial;
    test_state final;
    int cycles_len;
    cycle *cycles;
} test_def;

void parse_state_ram(json_object *obj, int ram_len, test_state *st){
    json_object *t_ram, *t_addr, *t_val;
    st->ram_len = ram_len;
    st->ram = malloc(ram_len*sizeof(ram_byte));

    for(int i=0; i<ram_len; i++){
        t_ram = json_object_array_get_idx(obj, i);
        t_addr = json_object_array_get_idx(t_ram, 0);
        t_val = json_object_array_get_idx(t_ram, 1);

        st->ram[i].addr = json_object_get_int(t_addr);
        st->ram[i].val = json_object_get_int(t_val);
    }
}

void parse_test_state(json_object *obj, test_state *st){
    int ram_len;
    json_object *pc, *s, *a, *x, *y, *p, *ram;
    pc = json_object_object_get(obj, "pc");
    s = json_object_object_get(obj, "s");
    a = json_object_object_get(obj, "a");
    x = json_object_object_get(obj, "x");
    y = json_object_object_get(obj, "y");
    p = json_object_object_get(obj, "p");
    
    st->pc = json_object_get_int(pc);
    st->s = json_object_get_int(s);
    st->a = json_object_get_int(a);
    st->x = json_object_get_int(x);
    st->y = json_object_get_int(y);
    st->p = json_object_get_int(p);
    ram = json_object_object_get(obj, "ram");
    ram_len = json_object_array_length(ram);
    parse_state_ram(ram, ram_len, st);
}

void parse_cycles(json_object *obj, int cycles_len, test_def *t){
    json_object *t_cycle, *t_addr, *t_val, *t_type;
    const char* t_type_str;
    cycle_type t_type_enum;

    t->cycles = malloc(cycles_len*sizeof(cycle));

    for(int i=0; i<cycles_len; i++){
        t_cycle = json_object_array_get_idx(obj, i);
        t_addr = json_object_array_get_idx(t_cycle, 0);
        t_val = json_object_array_get_idx(t_cycle, 1);
        t_type = json_object_array_get_idx(t_cycle, 2);

        t->cycles[i].addr = json_object_get_int(t_addr);
        t->cycles[i].val = json_object_get_int(t_val);
        
        t_type_str = json_object_get_string(t_type);
        const char* r_str = "read";

        if(strcmp(t_type_str, r_str) == 0){
            t_type_enum = C_READ;
        }else{
            t_type_enum = C_WRITE;
        }

        t->cycles[i].t = t_type_enum;
    }
}

void print_st(test_state st){
    printf(
        "pc: %d s: %d a: %d x: %d y: %d p: %d\nram: ",
        st.pc,st.s,st.a,st.x,st.y,st.p
    );


    for(int i=0; i<st.ram_len; i++){
        printf("(%d, %d) ", st.ram[i].addr, st.ram[i].val);
    }

    printf("\n");
}

void print_cycles(test_def t){
    for(int i=0; i<t.cycles_len; i++){
        printf("(%d, %d, %d) ", t.cycles[i].addr, t.cycles[i].val, t.cycles[i].t);
    }
    printf("\n");
}

void parse_tests(json_object *obj, int obj_len, test_def *tests){
    json_object *t, *t_init, *t_final, *t_cycles;
    int t_cycles_len;
    
    for(int i=0; i<obj_len; i++){
        t = json_object_array_get_idx(obj, i);
        t_init = json_object_object_get(t, "initial");
        t_final = json_object_object_get(t, "final");

        t_cycles = json_object_object_get(t, "cycles");
        t_cycles_len = json_object_array_length(t_cycles);
        tests[i].cycles_len = t_cycles_len;

        parse_test_state(t_init, &tests[i].initial);
        parse_test_state(t_final, &tests[i].final);
        parse_cycles(t_cycles, t_cycles_len, &tests[i]);
    }
}

void free_tests(test_def *tests, int len){
    for(int i=0; i<len; i++){
        free(tests[i].initial.ram);
        free(tests[i].final.ram);
        free(tests[i].cycles);
    }
    free(tests);
}

void test_assert(char* n, uint8_t x, uint8_t y, test_result* t){
    if(x != y){ 
        *t = TEST_FAIL; 
        printf("    %s should be %d was %d\n", n, x, y);
    }

}

test_result run_test(test_def t, cpu* c, mem* m){
    reset_cpu(c);
    reset_mem(m);

    set_reg(c, REG_PH, (t.initial.pc >> 8));
    set_reg(c, REG_PL, (t.initial.pc & 0x00FF));
    set_reg(c, REG_S, t.initial.s);
    set_reg(c, REG_A, t.initial.a);
    set_reg(c, REG_X, t.initial.x);
    set_reg(c, REG_Y, t.initial.y);
    set_reg(c, REG_P, t.initial.p);

    for(int i=0; i<t.initial.ram_len; i++){
        mem_set_byte(m, t.initial.ram[0].addr, t.initial.ram[0].val);
    }

    cpu_tick(c, m);
    
    test_result res = TEST_PASS;
    
    test_assert("PC HI", (t.final.pc >> 8), *get_reg(c, REG_PH), &res);
    test_assert("PC LO", (t.final.pc & 0x00FF), *get_reg(c, REG_PL), &res);
    test_assert("S", t.final.s, *get_reg(c, REG_S), &res);
    test_assert("A", t.final.a, *get_reg(c, REG_A), &res);
    test_assert("X", t.final.x, *get_reg(c, REG_X), &res);
    test_assert("Y", t.final.y, *get_reg(c, REG_Y), &res);
    test_assert("P", t.final.p, *get_reg(c, REG_P), &res);
    
    for(int i=0; i<t.final.ram_len; i++){
        
    }

    return res;
}

int main(int argc, char **argv){
    if(argc < 2){ exit(1); }
    char* fn = argv[1];

    json_object *root = json_object_from_file(fn);
    if(!root){
        printf("%s\n", json_util_get_last_err());
        exit(1);
    } 


    int len = json_object_array_length(root);
    
    test_def *tests = malloc(len*sizeof(test_def));
    
    parse_tests(root, len, tests);
    
    cpu c;

    mem* m = create_mem(65535);
    test_result res;
    for(int i=0; i<len; i++){
        res = run_test(tests[i], &c, m);
        if(res == TEST_FAIL){
            printf("Test %d FAIL\n", i);
        }
    }

    json_object_put(root);
    free_tests(tests, len);
    free_mem(m);
    return 0;
}
