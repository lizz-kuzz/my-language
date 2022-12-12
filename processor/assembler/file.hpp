#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include "utils_ass.hpp"
long int count_symbols          (FILE *file);

int      num_of_rows            (char *text);

void     read_file              (const char *TEXT, prog *text);

void     program_text_normalize (prog *text);

#endif