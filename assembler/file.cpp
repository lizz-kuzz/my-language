#include "file.hpp"

void create_file_path(char *FILE_PROG, char *path, char *name_file) {
    assert(path      != nullptr && "null pointer");
    assert(name_file != nullptr && "null pointer");
    assert(FILE_PROG != nullptr && "null pointer");

    char *save_point = FILE_PROG;

    for (; *path != '\0'; path++, save_point++) {
        *save_point = *path;
    }
    for (; *name_file != '\0'; name_file++, save_point++) {
        *save_point = *name_file;
    }
    *save_point = '\0';

}

void read_file(const char *TEXT, prog *text) {
    FILE *file = fopen(TEXT, "r");

    assert(file != nullptr && "coudn't open file");

    if (file == NULL)
        printf("Could not open file.\n");
    
    text->SYMBOLS = count_symbols(file);

    text->text_buf = (char *) calloc(text->SYMBOLS + 1, sizeof(char)); 

    assert(text->text_buf != nullptr && "null pointer");

    fread(text->text_buf, sizeof(char), text->SYMBOLS, file);

    fclose(file);

    program_text_normalize(text);
}

int num_of_rows(char *text)  {
    int count = 0;
    char *point = text;

    while (*point != '\0')  {
        if (*point == '\n')
            count++;
        point++;
    }
    return count;
}

long int count_symbols(FILE *file)  {
    fseek(file, 0, SEEK_END);
    
    long int number = ftell(file);

    fseek(file, 0, SEEK_SET);

    return number;
}



void program_text_normalize(prog *text)  {
    assert(text != nullptr && "null pointer");

    text->NUMBER = num_of_rows(text->text_buf);
   
    char *point = text->text_buf;
    
    text->text = (char **) calloc(text->NUMBER + 1, sizeof(char *));

    assert(text->text != nullptr && "null pointer");

    text->text[0] = point;

    for (int i = 1; (i <= text->NUMBER) && *(point) != '\0'; point++)  { 
        if (*point == '\n')  {
            *point = '\0';
            for (;*(point + 1) == ' '; point++) continue;
            text->text[i] = point + 1;
            i++;
        } else if (*point == ';') {
            for (; *point != '\n'; point++) continue;
            *point = '\0';
            text->text[i] = point + 1;
            i++;
        }
    }
}

