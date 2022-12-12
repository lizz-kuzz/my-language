#include "processor.hpp"

#define HEADER_SIZE 2

#define MASK_CMD       0x1f
#define MASK_ARG_REG   0x40
#define MASK_ARG_RAM   0x80
#define MASK_ARG_IMMED 0x20


int read_arr_cmd(const char *FILE_BIN, prog *program, stack *stk) {

    FILE *file = fopen(FILE_BIN, "r+b");
    
    fread(program->arr_sign, sizeof(int), SIZE_ARR_SIGN, file);
    if (check_version(program) != 0) {
        dtor_program(program);
        stack_dtor(stk);
        return 1;
    }

    program->cmd = (int *) calloc(program->NUMBER_OF_CMD + 1, sizeof(int));
    fread(program->cmd, sizeof(int), program->NUMBER_OF_CMD, file);

    fclose(file);  

    return 0;
}

void ctor_program(prog *program, stack *stk) {
    assert(program != nullptr && "null pointer");
    assert(stk     != nullptr && "null pointer");

    for (int i = 0; i < 20; i++) {
        program->ram[i] = 0;
    }
    program->reg[1] = 0;
    program->reg[2] = 0;
    program->reg[3] = 0;
    program->reg[4] = 0;
}

void dtor_program (prog *program) {    
    assert(program != nullptr && "null pointer");

    free(program->cmd);
}

int check_version(prog *program) {
    assert(program != nullptr && "null pointer");
    
    if (program->arr_sign[0] != SIGNATURE) {
        printf("the signature does not match, it is impossible to execute the program\n");
        return 1;
    }
    if (program->arr_sign[1] != VERSION) {
        printf("the processor does not support this version of the program, buy coffee to the developer or a new processor\n");
        return 1;
    }
    program->NUMBER_OF_CMD = program->arr_sign[2];

    return 0;
}


int get_arg(prog *program, int cmd, int *ip) {
    assert(program != nullptr && "null pointer");

    int arg = 0;
        *ip += 1;
    if (cmd & MASK_ARG_IMMED) {
        arg += program->cmd[*ip];
    }
    if (cmd & MASK_ARG_REG) {
        arg += program->reg[program->cmd[*ip]];
    }
    if (cmd & MASK_ARG_RAM) {
        arg = program->ram[arg];
    }

    return arg;
}


void pop_arg (prog *program, int cmd, int arg, int *ip) {
    assert(program != nullptr && "null pointer");

    *ip += 1;

    if (cmd & MASK_ARG_RAM && cmd & MASK_ARG_REG) {
        program->ram[program->reg[program->cmd[*ip]]] = arg;
    } else if (cmd & MASK_ARG_REG) {
        program->reg[program->cmd[*ip]] = arg;
    } else if (cmd & MASK_ARG_RAM) {
        program->ram[program->cmd[*ip]] = arg;
    }
}



#define DEF_CMD(cmd, number_cmd, arg, ...)      \
    case cmd:                                   \
    {                                           \
        __VA_ARGS__                             \
        break;                                  \
    } 

int run_program(prog *program, stack *stk) {

    assert(program != nullptr && "null pointer");
    stack stk_ip = {};
    stack_ctor(stk_ip, 4);

    for (int ip = 0; ip < program->NUMBER_OF_CMD; ip++) {
        switch (program->cmd[ip] & MASK_CMD)
        {
            #include "../config.hpp"
        default:
            printf("comand didn't found %d cmd %d\n", ip, program->cmd[ip]);
            break;
        }
    }

    stack_dtor(&stk_ip);
    return 0;
}
#undef DEF_CMD
