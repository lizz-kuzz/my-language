#include "../include/file.hpp"
#include "../include/back_end.hpp"

int main(int argc, char *argv[]) {
    
    // char *path = "res/";
    // char *name_file = argv[1];
    // char *FILE_INPUT = (char *) calloc(strlen(path) + strlen(name_file), sizeof(char));
    // create_file_path(FILE_INPUT, path, name_file);
    const char *FILE_INPUT = "res/program.txt";

    Tree tree = {};
    ctor_tree(FILE_INPUT, &tree);
    // printf("%d", tree.root_tree->type);

    dump_tree(tree.root_tree);




    return 0;
}