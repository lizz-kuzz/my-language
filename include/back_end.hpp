#ifndef DIFF_FUNC_HPP_INCLUDED
#define DIFF_FUNC_HPP_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>



#define DEF_OPER(oper, num_oper, mean, len) \
    oper = num_oper,                        \


enum TYPE_OPERATOR {
    #include "../config_oper.hpp"
};

#undef DEF_OPER


enum TYPE_NODE {
    TP_OPERATOR = 1,
    TP_VAR = 2,
    TP_NUMBER = 3,
};

union data {
    TYPE_OPERATOR  oper;
    int             number;
    char *          var;
};

struct Node {
    TYPE_NODE       type;
    data            value;
    Node *          left;
    Node *          right;
};

struct Tree {
    Node *root_tree;
};

struct token_elem { 
    char      *elem;
    TYPE_NODE  type;
    TYPE_OPERATOR oper;
};

struct Tokenizer {
    token_elem *array;
    int         size;
    int         capacity;
};

/*
grammar = 




*/
// -------------------------------------BEGIN RECURSIVE DESCENT FUNC---------------------------------------------------

Node *get_grammar(Tokenizer *tokens);

Node *get_type(Tokenizer *tokens);

Node *get_condition(Tokenizer *tokens);

Node *get_body(Tokenizer *tokens);

Node *ger_var_declaration(Tokenizer *tokens);

Node *get_assignment(Tokenizer *tokens);

Node *get_add_sub(Tokenizer *tokens);

Node *get_mul_div(Tokenizer *tokens);

Node *get_deg(Tokenizer *tokens);

Node *get_unary_op(Tokenizer *tokens);

Node *get_bracket(Tokenizer *tokens);

Node *get_number(Tokenizer *tokens);

Node *get_var(Tokenizer *tokens);

// -------------------------------------END RECURSIVE DESCENT FUNC---------------------------------------------------



// -------------------------------------BEGIN TOKENIZER FUNC---------------------------------------------------

void create_number_token(Tokenizer *tokens, char **text_buf, int ip);

void create_var_token(Tokenizer *tokens, char **text_buf, int ip);

void tokenizer_ctor(Tokenizer *tokens, char *text_buf);

void tokenizer_dtor(Tokenizer *tokens);

int is_oper(char symbol);

// -------------------------------------END TOKENIZER FUNC---------------------------------------------------




// -------------------------------------BEGIN TREE FUNCTIONS--------------------------------------

Node *create_tree_from_text(Node *node, char **text_buf);

void ctor_tree(const char *FILE_INPUT, Tree *tree);

void dtor_tree(Node *node);

Node *tree_add_elem(Node *node, char *elem);

// -------------------------------------END TREE FUNCTIONS------------------------------------------------------------



//--------------------------------------BEGIN TREE OUNPUT FUNC--------------------------------------------------------

int checking_for_priority(Node *node, Node *parent);

void dump_tree(Node *root);

void print_tree(Node *node, Node *parent);

void print_node(FILE *file, Node *node);

void graph_dump(FILE *dot_file, Node *node, Node *node_son);

void close_file();

//--------------------------------------END TREE OUNPUT FUNC----------------------------------------------------------



//------------------------------------BEGIN DIFFERENTIATOR FUNC-----------------------------------------------------------

Node *diff_tree(Node *node);

Node *copy_tree(Node *node); 

Node *create_node(TYPE_NODE tp_node, int value, Node *node_left, Node *node_right);

Node *create_var_node(char *var, Node *node_left, Node *node_right);

//-----------------------------------------END DIFFERENTIATOR FUNC-----------------------------------------------------------



//-----------------------------------------BEGIN OPTIMIZER FUNC--------------------------------------------------------------

void optimizer_tree(Node *node);

int folding_constant(Node *node, int *continue_optimiz);

int pow(int x, int y);

//-----------------------------------------END OPTIMIZER FUNC------------------------------------------


#endif
