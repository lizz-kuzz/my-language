#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED

#include "../utils.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>


#define SIGNATURE 'CP'
#define VERSION 3

#define LEN_ARR_LABLES 100
#define MASK_CMD    0x1f
#define BIT_CONST   5
#define BIT_REG     6
#define BIT_RAM     7
#define LEN_LABLE   30
#define LEN_CMD     30

typedef struct {
    char *mame_label;
    int   ip;
} lable;

typedef struct {
    char    *text_buf;
    char   **text;
    int      lables[LEN_ARR_LABLES];
    int     *code;
    int      NUMBER;
    long int SYMBOLS;
    lable    arr_text_lab[LEN_ARR_LABLES];
} prog;

int compile(const char *file, prog *text_program);

void printf_listing(prog *text_program, int count_cmd);

int get_args(prog *program, char *text_cmd, char *cmd, int *ip);

int find_char(char * text, char symbol);

void my_strcpy_for_lable(char *text_for_cpy, char *text);

int processing_label(prog *program);

void dtor(prog *program);

#endif
