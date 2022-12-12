#ifndef UTILS_ASS_HPP_INCLUDED
#define UTILS_ASS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../utils.hpp"

#define SIGNATURE 'CP'
#define VERSION 3
#define LEN_ARR_LABLES 10
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



#endif