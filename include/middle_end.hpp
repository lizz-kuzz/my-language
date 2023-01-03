#ifndef MIDDLE_END_HPP_INCLUDED
#define MIDDLE_END_HPP_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "back_end.hpp"

void optimizer_tree(Node *node);

int collapsing_nodes(Node *node, int *continue_optimiz);

int folding_constant(Node *node, int *continue_optimiz);

int pow(int x, int y);

#endif