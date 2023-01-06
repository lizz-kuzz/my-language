#include "processor.hpp"

int main() {
    const char *FILE_ASS_OUTPUT = "res/asm.output";
    
    prog program = {};
    stack stk = {};
    
    stack_ctor(stk, 1);

    if (read_arr_cmd(FILE_ASS_OUTPUT, &program, &stk) == 1) return 0;
    
    run_program(&program, &stk);

    for (int i = 0; i < SIZE_RAM; i ++) {
        printf("%d ", program.ram[i]);
    }
    
    dtor_program(&program);

    stack_dtor(&stk);




    return 0;
}