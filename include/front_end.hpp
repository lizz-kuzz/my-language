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
    char *name_var;
};

struct Variable_table {
    int      size;
    int      capacity;
    Arr_var *arr;
};

int  find_var(Variable_table *var_table, char *var);
void ctor_var_table(Variable_table *var_table);
void printf_asm(const char *FILE_INPUT, Node *node, Variable_table *var_table);
void print_asm_code(Node *node, Node *parent, FILE *file, Variable_table *var_table);
void print_asm_node(Node *node, Node *parent, FILE *file, Variable_table *var_table);

#endif