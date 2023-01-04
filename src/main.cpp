#include "../include/file.hpp"
#include "../include/back_end.hpp"
#include "../include/front_end.hpp"
#include "../include/middle_end.hpp"


int main(int argc, char *argv[]) {
    
    // char *path = "res/";
    // char *name_file = argv[1];
    // char *FILE_INPUT = (char *) calloc(strlen(path) + strlen(name_file), sizeof(char));
    // create_file_path(FILE_INPUT, path, name_file);
    const char *FILE_INPUT = "res/program.txt";
    const char *FILE_ASM = "res/asm_output.txt";

    Tree tree = {};
    Variable_table var_table = {};

    var_table.capacity = ctor_tree(FILE_INPUT, &tree);
    dump_tree(tree.root_tree);
    optimizer_tree(tree.root_tree);
    ctor_var_table(&var_table);
    printf_asm(FILE_ASM, tree.root_tree, &var_table);

    // for (int i = 0; i < var_table.size; i++) {
    //     printf("'%s' [%d]\n", var_table.arr[i].name_var, var_table.arr[i].id);
    // }


    // dtor_tree(tree.root_tree);

    // system("./ass.exe asm_output.txt");
    // system("./cpu.exe");




    return 0;
}