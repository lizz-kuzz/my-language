#include "disassembler.hpp"

void disassembler(const char *file_input, const char *file_output) {
    prog program = {};
    
    read_file(file_input, &program);


    FILE *file = fopen(file_output, "w");
    assert(file != nullptr && "coudn't open file");

    char *point = program.text_buf;
    fprintf(file, "%s\n", point);

    size_t len_first_line = strlen(point);
    point += len_first_line + 1;
    
    for (; *point != '\0'; point++) {
        if (isalnum(*point) != 0) {
            if (*point == PUSH) {
                fprintf(file, "push ");
                point += 2;
                for (; isalnum(*point) != 0;) {
                    fputc(*point, file);
                    point++;
                }
                fprintf(file, "\n");
            } else if (*point == ADD) {
                fprintf(file, "add\n");
                point += 1;
            } else if (*point == SUB) {
                fprintf(file, "sub\n");
                point += 1;
            } else if (*point == MUL) {
                fprintf(file, "mul\n");
                point += 1;
            } else if (*point == DIV) {
                fprintf(file, "div\n");
                point += 1;
            } else if (*point == OUT) {
                fprintf(file, "out\n");
                point += 1;
            } else if (*point == HLT) {
                fprintf(file, "hlt\n");
                point += 1;
            } else if (*point == DUMP) {
                fprintf(file, "dump\n");
                point += 1;
            } else if (*point == IN) {
                fprintf(file, "in\n");
                point += 1;
            } 
        }
    }
    fclose(file);
    free(program.text_buf);
    free(program.text);
}