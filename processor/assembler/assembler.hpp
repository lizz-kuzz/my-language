#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED

#include "utils_ass.hpp"

int compile(const char *file, prog *text_program);

void printf_listing(prog *text_program, int count_cmd);

int get_args(prog *program, char *text_cmd, char *cmd, int *ip);

int find_char(char * text, char symbol);

void my_strcpy_for_lable(char *text_for_cpy, char *text);

int processing_label(prog *program);

void dtor(prog *program);

void create_file_path(char *FILE_PROG, char *path, char *name_file);

#endif
