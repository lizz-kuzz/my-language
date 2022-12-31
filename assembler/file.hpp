#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include "assembler.hpp"

long int count_symbols          (FILE *file);

void     create_file_path(char *FILE_PROG, char *path, char *name_file);

int      num_of_rows            (char *text);

void     read_file              (const char *TEXT, prog *text);

void     program_text_normalize (prog *text);

#endif