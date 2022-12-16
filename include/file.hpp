#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void     create_file_path       (char *FILE_PROG, char *path, char *name_file);

long int count_symbols          (FILE *file_input);

int      num_of_rows            (char *text);

char    *read_file              (const char *TEXT, char *text_buf);

char *program_text_normalize(char *text, int SYMBOLS);

#endif