#ifndef UTILS_PROC_HPP_INCLUDED
#define UTILS_PROC_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../utils.hpp"

#define SIGNATURE 'CP'
#define VERSION 3

#define SIZE_RAM 25
#define SIZE_REG 5
#define SIZE_ARR_SIGN 3


typedef struct {
    int      arr_sign[SIZE_ARR_SIGN];
    int      ram[SIZE_RAM];
    int      reg[SIZE_REG];
    int     *cmd;
    int      NUMBER_OF_CMD;
} prog;


#endif