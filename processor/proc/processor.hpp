#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED
#include "utils_proc.hpp"
#include "../stack/stack.hpp"
#include "../stack/debug.hpp"

int      read_arr_cmd             (const char *FILE, prog *program, stack *stk);

void     dtor_program            (prog *program);

void     ctor_program            (prog *program, stack *stk);

int      check_version           (prog *program);

void     create_arr_cmd          (prog *text);

int      run_program             (prog *program, stack *stk);

long int count_symbols           (FILE *file);

int      num_of_rows             (char *text);

void     read_file               (const char *TEXT, prog *text);

void     program_text_normalize  (prog *text);

int      get_arg                 (prog *program, int cmd, int *ip);

void     create_cmd              (prog *program);

void     pop_arg                 (prog *program, int cmd, int arg, int *ip);

void     get_arg_call            (prog *program, int cmd, int *ip);


#endif

