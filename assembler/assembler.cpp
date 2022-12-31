#include "assembler.hpp"
#include "file.hpp"


int find_char(char * text, char symbol) {
    char *point = text;
    int count = 0;
    for (; *point != '\0'; point++) {
        if (*point == symbol) count++;
    }
    return count;
}

int get_args(prog *program, char *text_cmd, char *cmd, int *ip) {
    assert(program != nullptr && "null pointer");

    if (strcmp(cmd, "PUSH") == 0 || strcmp(cmd, "POP") == 0) {
        text_cmd += strlen(cmd) + 1;
        *ip -= 1;

        int arg = 0;
        char arg_reg_ram[10];

        if (sscanf(text_cmd, "%s", arg_reg_ram) != 0) {
            if (strncmp(arg_reg_ram, "[", 1) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_RAM);
                text_cmd++;
            }
        }

        if (sscanf(text_cmd, "%d", &arg) != 0) {
            program->code[*ip] = program->code[*ip] | (1 << BIT_CONST);

            // if (strstr(text_cmd, "+")) {
            //     text_cmd = strstr(text_cmd, "+");
            //     text_cmd++;
            //     *ip += 1;
            //     program->code[*ip] = arg;
            //     *ip += 1;
            // }

            // printf("text %s\n", text_cmd);
        } 
        
        if (sscanf(text_cmd, "%s", arg_reg_ram) != 0) {
            if (strncmp(arg_reg_ram, "ax", 2) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 1;
            } else if (strncmp(arg_reg_ram, "bx", 2) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 2;
            } else if (strncmp(arg_reg_ram, "cx", 2) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 3;
            } else if (strncmp(arg_reg_ram, "dx", 2) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 4;
            }

        }

        if (find_char(text_cmd, ']') > 1 || find_char(text_cmd, '[') > 1) {
            printf("compilation error unclosed brackets \"%s\"\n", text_cmd);
            return 1;
        }

        *ip += 1;
        program->code[*ip] = arg;
        *ip += 1;

    } else if (strncmp(cmd, "J", 1) == 0 || strncmp(cmd, "CALL", 4) == 0) {
        text_cmd += strlen(cmd) + 1;
        int arg = -1;
        char name_lable[LEN_LABLE];

        if (sscanf(text_cmd, "%s", name_lable) != 0) {
            for (int i = 0; i < LEN_ARR_LABLES && program->arr_text_lab[i].mame_label != NULL ; i++) {
                if (strcmp(name_lable, program->arr_text_lab[i].mame_label) == 0) {
                    arg = program->arr_text_lab[i].ip;
                    break;
                }
            }
            if (arg == -1) {
                printf("compilation error: %s without argument or lable didn't find \n", cmd);
                return 1;
            }
        }     
        program->code[*ip] = arg;
        *ip += 1;
    }
    return 0;
}

void my_strcpy_for_lable(char *text_for_cpy, char *text) {
    for (; *text_for_cpy != '\0' && *text_for_cpy != ':'; ) {
        *text++ = *text_for_cpy++;
    }
}


#define DEF_CMD(cmd_name, number_cmd, args, ...)                                                     \
    if (*program->text[i] != '\0' && strncmp(program->text[i], #cmd_name, strlen(#cmd_name)) == 0) { \
        ip++;                                                                                        \
        if (args == 1) ip++;                                                                         \
        continue;                                                                                    \
    } else 


int processing_label(prog *program) {
    assert(program != nullptr && "null pointer");

    int ip = 0; 
    int ind_labl = 0;

    for (int i = 0; i < program->NUMBER; i++) {
        if (strlen(program->text[i]) >= LEN_LABLE) {
            printf("compilation error: the length of the lable \"%s\" exceeded the allowed length\n", program->text[i]);
            return 1;
        }
        if (*program->text[i] == '\0') i++;

        #include "../config.hpp"
            /*else*/ 

            if (find_char(program->text[i], ':') != 0) {

                for (int j = 0; j < LEN_ARR_LABLES && program->arr_text_lab[j].mame_label != NULL ; j++) {

                    if (strncmp(program->text[i], program->arr_text_lab[j].mame_label, strlen(program->arr_text_lab[j].mame_label)) == 0) {
                        printf("compilation error: the label \"%s\" has already been used\n", program->arr_text_lab[j].mame_label);
                        return 1;
                    }
                }

                program->arr_text_lab[ind_labl].mame_label = (char *) calloc(strlen(program->text[i]), sizeof(char));
                my_strcpy_for_lable(program->text[i], program->arr_text_lab[ind_labl].mame_label);
                program->arr_text_lab[ind_labl].ip = ip;
                ind_labl++;
            }
    }
    return 0;
}
#undef DEF_CMD




#define DEF_CMD(cmd_name, number_cmd, args, ...)                        \
    if (strcmp(cmd, #cmd_name) == 0) {                                  \
        program->code[ip++] = number_cmd;                               \
        int error = -1;                                                 \
        if (args) {                                                     \
            error = get_args(program, program->text[i], cmd, &ip);      \
        }                                                               \
        if (error == 1) return 1;                                       \
        } else


int compile(const char *file, prog *program) {

    assert(program != nullptr && "null pointer");

    program->code = (int *) calloc(program->NUMBER * 2, sizeof(int));

    assert(program->code != nullptr && "null pointer");

    int error_lable = 0;
    error_lable = processing_label(program);

    if (error_lable == 1) return 1;
    
    char cmd[LEN_CMD]; 
    int ip = 0;

    for (int i = 0; i < program->NUMBER; i++) {

        if (strlen(program->text[i]) >= LEN_CMD) {
            printf("compilation error: the length of the command \"%s\" exceeded the allowed length\n", program->text[i]);
            return 1;
        }

        if (strchr(program->text[i], ':') != 0 && *program->text[i] != '\0') {
            continue;
        } else if (sscanf(program->text[i], "%s", cmd) != 0 && *program->text[i] != '\0') {

            #include "../config.hpp"
            /*else*/ printf("comand didn't found\n");
        }
    }
    
    FILE *fp = fopen(file, "w+b");
    assert(fp != nullptr && "coudn't open file");
  
    int version   = VERSION;
    int signature = SIGNATURE;

    const int *psign    = &signature;
    const int *pversion = &version;
    const int *pnum     = &ip; 

    fwrite(psign,    sizeof(int), 1, fp);
    fwrite(pversion, sizeof(int), 1, fp);
    fwrite(pnum,     sizeof(int), 1, fp);

    fwrite(program->code, sizeof(int), ip, fp);
    
    printf_listing(program, ip);

    fclose(fp);
    return 0;
}
#undef DEF_CMD


#define DEF_CMD(cmd_name, number_cmd, args, ...)                                        \
    case cmd_name:                                                                      \
        fprintf(fp, "%02x", text_program->code[ip]);                                    \
        if (args)  {                                                                    \
            ip++;                                                                       \
            fprintf(fp, "%10d %20s\n", text_program->code[ip], #cmd_name);              \
        } else  {                                                                       \
            fprintf(fp, "%30s\n", #cmd_name); }                                         \
        break;                                                                          \
    

void printf_listing(prog *text_program, int count_cmd) {
    assert(text_program != nullptr && "null pointer");

    const char *FILE_LISTING = "res_cpu/listing.txt"; 

    FILE *fp = fopen(FILE_LISTING, "w");
    assert(fp != nullptr && "coudn't open file");

    for (int ip = 0; ip < count_cmd; ip++) {
        fprintf(fp, "%05d    ", ip);
        switch (text_program->code[ip] & MASK_CMD)
        {
            #include "../config.hpp"      
        default:
            fprintf(fp, "didn't found comand\n");
            break;
        }
    }
    fclose(fp);
}

#undef DEF_CMD

void dtor(prog *program) {
    assert(program != nullptr && "null pointer");

    free(program->code);
    free(program->text);
    free(program->text_buf);
}