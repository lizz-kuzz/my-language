#include <stdio.h>
#include "file.hpp"
#include "assembler.hpp"

#include <string.h>


int main(int argc, char *argv[]) {
    prog program = {};

    char *path = "res/";
    char *name_file = argv[1];
    char *FILE_PROG = (char *) calloc(strlen(path) + strlen(name_file), sizeof(char));

    
    create_file_path(FILE_PROG, path, name_file);
 
    // printf("%s", FILE_PROG);
    const char *FILE_ASS_OUTPUT = "res_cpu/asm.output";

    read_file(FILE_PROG, &program);

    if (compile(FILE_ASS_OUTPUT, &program) == 1) return 1;
    
    dtor(&program);
    // system("./cpu.exe");
    // printf("ffff");
  
    return 0;
}