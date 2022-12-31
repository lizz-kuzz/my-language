#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED

#include "../stack/stack.hpp"
#include "../stack/debug.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "../utils.hpp"

#define SIGNATURE 'CP'
#define VERSION 3

#define SIZE_RAM 25
#define SIZE_REG 5
#define SIZE_ARR_SIGN 3

#define HEADER_SIZE 2

#define MASK_CMD       0x1f
#define MASK_ARG_REG   0x40
#define MASK_ARG_RAM   0x80
#define MASK_ARG_IMMED 0x20




typedef struct {
    int      arr_sign[SIZE_ARR_SIGN];
    int      ram[SIZE_RAM];
    int      reg[SIZE_REG];
    int     *cmd;
    int      NUMBER_OF_CMD;
} prog;


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

int      pow(int x, int y);

#endif

