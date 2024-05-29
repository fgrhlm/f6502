#include <stdio.h>
#include <json-c/json.h>
#include <json_visit.h>

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
    ram_byte *ram;
} test_state;

typedef struct {
    test_state initial;
    test_state final;
    cycle cycles;
} test_def;

void parse_test_state(json_object *obj, test_state *st){
    json_object *pc, *s, *a, *x, *y, *p;
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
}

void parse_test_ram(json_object *obj, ram_byte *ram, int ram_len){
    ram = malloc(ram_len*sizeof(ram_byte));

}

void parse_cycles(json_object *obj, cycle c){
    
}

void print_st(test_state st){
    printf(
        "pc: %d\ns: %d\na: %d\nx: %d\ny: %d\np: %d\n\n",
        st.pc,st.s,st.a,st.x,st.y,st.p
    );
}

int main(int argc, char **argv){
    if(argc < 2){ exit(1); }
    char* fn = argv[1];

    json_object *root = json_object_from_file(fn);
    if(!root){
        printf("%s\n", json_util_get_last_err());
        exit(1);
    } 

    json_object *t, *t_init, *t_final, *t_cycles;
    int t_ram_len, t_cycles_len;

    int len = json_object_array_length(root);
    
    test_def *tests = malloc(len*sizeof(test_def));

    for(int i=0; i<2; i++){
        t = json_object_array_get_idx(root, i);
        t_init = json_object_object_get(t, "initial");
        t_final = json_object_object_get(t, "final");

        t_cycles = json_object_object_get(t, "cycles");
        t_cycles_len = json_object_array_length(t_cycles);

        parse_test_state(t_init, &tests[i].initial);
        parse_test_state(t_final, &tests[i].final);
    }
   
    printf("INIT:\n");
    print_st(tests[0].initial);

    printf("FINAL:\n");
    print_st(tests[0].final);

    json_object_put(root);
    free(tests);
    return 0;
}
