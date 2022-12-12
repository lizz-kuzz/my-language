#include "disassembler.hpp"

int main() {
    const char *FILE_DISASS_INPUT = "/mnt/c/Users/User/Desktop/programs/fsa/processor/res/ass_output.txt";
    const char *FILE_DISASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/fsa/processor/res/disass_output.txt";

    // const char *FILE_PROG = "C://Users//User//Desktop//programs//processor//res//ass_input.txt";
    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";
    // const char *FILE_DISASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//disass.output";


    disassembler(FILE_DISASS_INPUT, FILE_DISASS_OUTPUT);

    return 0;
}