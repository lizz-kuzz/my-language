#include "processor.hpp"

int main() {
    const char *FILE_ASS_OUTPUT = "../res/ass.output";

    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";
    
    prog program = {};
    stack stk = {};
    
    stack_ctor(stk, 1);

    if (read_arr_cmd(FILE_ASS_OUTPUT, &program, &stk) == 1) return 0;
    
    run_program(&program, &stk);

    
    dtor_program(&program);

    stack_dtor(&stk);


    return 0;
}