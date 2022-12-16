#include "../include/file.hpp"

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

char *read_file(const char *TEXT, char *text_buf) {
    FILE *file_input = fopen(TEXT, "r");

    assert(file_input != nullptr && "coudn't open file");

    if (file_input == NULL)
        printf("Could not open file.\n");
    
    long int SYMBOLS = count_symbols(file_input);

    text_buf = (char *) calloc(SYMBOLS + 1, sizeof(char)); 

    assert(text_buf != nullptr && "null pointer");

    fread(text_buf, sizeof(char), SYMBOLS, file_input);

    fclose(file_input);
    text_buf = program_text_normalize(text_buf, SYMBOLS);
    // printf("%s\n", text_buf);
    printf("%s\n", text_buf);
    return text_buf;

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

long int count_symbols(FILE *file_input)  {
    fseek(file_input, 0, SEEK_END);
    
    long int number = ftell(file_input);

    fseek(file_input, 0, SEEK_SET);

    return number;
}

char *program_text_normalize(char *text, int SYMBOLS)  {
    assert(text != nullptr && "null pointer");
    
    char *copy_text = (char *) calloc(SYMBOLS + 1, sizeof(char));

    *copy_text = *text;
    char *point = copy_text;
    
    for (; *text != '\0'; point++, text++)  {

        while (isspace(*text) && *text != '\0') 
            text++;
        
        *point = *text;
    }

    *point = '\0';

    return copy_text;
}

