#ifndef FRONT_END_HPP_INCLUDED
#define FRONT_END_HPP_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "back_end.hpp"

struct Arr_var {
    int   id;
    char *name;
};

struct Variable_table {
    int      size;
    int      capacity;
    Arr_var *arr;
};

int  find_name(Variable_table *name_table, char *var);

void ctor_var_func_table(Variable_table *name_table);

void printf_asm(const char *FILE_INPUT, Node *node, Variable_table *name_table);

void print_asm_code(Node *node, Node *parent, FILE *file, Variable_table *name_table);

void print_asm_node(Node *node, Node *parent, FILE *file, Variable_table *name_table);

void print_jump_lable(Node *node, Node *parent, FILE *file, Variable_table *name_table);


#endif