#include "../include/back_end.hpp"
#include "../include/DSL.hpp"
#include "../include/file.hpp"

const char *NAME_GRAPH_FILE = "res/graph.dot";
const char *NAME_FILE =       "res/text_output.txt";

FILE *file_tree = fopen(NAME_FILE, "w");

// -------------------------------------BEGIN TREE FUNCTIONS--------------------------------------


const int MAX_SIZE = 10;

int ctor_tree(const char *FILE_INPUT, Tree *tree) {

    char *text_buf;

    text_buf = read_file(FILE_INPUT, text_buf);

    char *point_text_buf = text_buf;

    Tokenizer tokens = {};

    tokenizer_ctor(&tokens, point_text_buf);

    printf("%d\n", tokens.capacity);

    for (int i = 0; i < tokens.capacity; i++) {
        printf("%d [\"%s\"] {%d} ", tokens.array[i].type, tokens.array[i].elem, tokens.array[i].oper);
    }

    printf("\n");

    tree->root_tree = (Node *) calloc(1, sizeof(Node));

    tree->root_tree = get_grammar(&tokens);
    
    int capacity = tokens.capacity;
    
    tokenizer_dtor(&tokens);

    free(text_buf);

    return capacity;
}

Node *create_tree_from_text(Node *node, char **text_buf) {

    if (**text_buf == '\0') return node;


    if (**text_buf == '(') {
        node->left = (Node *) calloc(1, sizeof(Node));
        (*text_buf)++;
        node->left = create_tree_from_text(node->left, text_buf);
    }

    char *elem = (char *) calloc(MAX_SIZE, sizeof(char));
    char *point = elem;

    for (; **text_buf != ')' && **text_buf != '(' && **text_buf != '\0' && **text_buf != '\n'; (*text_buf)++, elem++) *elem = **text_buf; 
    elem = point;

    node = tree_add_elem(node, elem);

    if (**text_buf == '(') { 
        (*text_buf)++;
        node->right = (Node *) calloc(1, sizeof(Node));
        node->right = create_tree_from_text(node->right, text_buf);
    }

    if (**text_buf == ')') {
        (*text_buf)++; 
        return node;
    }
  
    return node;
}

Node *tree_add_elem(Node *node, char *elem) {

    assert(node && "null node");

    if (isdigit(*elem)) {
        node->type = TP_NUMBER;
        node->value.number = atoi(elem); 
    } else {
        switch (*elem) {
            case OP_ADD: {
                node->type = TP_OPERATOR;
                node->value.oper  = OP_ADD;
                break;
            } case OP_SUB: {
                node->type = TP_OPERATOR;
                node->value.oper  = OP_SUB;
                break;
            } case OP_DIV: {
                node->type = TP_OPERATOR;
                node->value.oper  = OP_DIV;
                break;
            } case OP_MUL: {
                node->type = TP_OPERATOR;
                node->value.oper  = OP_MUL;
                break;
            } case OP_DEG: {
                node->type = TP_OPERATOR;
                node->value.oper  = OP_DEG;
                break;           
            } case (OP_LN): { 
                node->type = TP_OPERATOR;
                node->value.oper  = OP_LN;
                node->left = NULL;
                break;
            } default: {
                node->type = TP_VAR;
                node->value.var = (char *) calloc(MAX_SIZE, sizeof(char));
                node->value.var = strcpy(node->value.var, elem);
                break;
            }
        }
    }
    return node;
}

void dtor_tree(Node *node) {

    if (!node) return;

    dtor_tree(node->left);
    node->left = NULL;
    
    dtor_tree(node->right);
    node->right = NULL;
    
    if (node->type == TP_VAR) free(node->value.var);
    free(node);
}
// -------------------------------------END TREE FUNCTIONS------------------------------------------------------------


// -------------------------------------BEGIN RECURSIVE DESCENT-------------------------------------------------------

Node *get_grammar(Tokenizer *tokens) {

    Node *node = get_type(tokens);

    assert(tokens->size == tokens->capacity);
    
    printf("successful parsing\n");

    return node;
}

// Node *get_decl_func(Tokenizer *tokens) {

//     Node *node = NULL;

//     if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_DEC_FUNC)) { 
//         tokens->size++;

//         char *name_func = (char *) calloc(strlen(tokens->array[tokens->size].elem), sizeof(char));
//         name_func = strcpy(name_func, tokens->array[tokens->size].elem);
//         tokens->size++;
//         assert(tokens->array[tokens->size++].oper == OP_LEFT_BRACKET && "sintax error: you forgot left bracket in declaration function");
//         // tokens->size++;        
//         assert(tokens->array[tokens->size++].oper == OP_RIGHT_BRACKET && "sintax error: you forgot right bracket in declaration function");
//         node = create_var_node(name_func, NULL, get_body(tokens));
//     printf("\n");
//           for (int i = tokens->size; i < tokens->capacity; i++) {
//         printf("%d [\"%s\"] {%d} ", tokens->array[i].type, tokens->array[i].elem, tokens->array[i].oper);
//     }
//     printf("\n");

//         free(name_func);
//     }

//     return node;
// }

Node *get_type(Tokenizer *tokens) {
    
    Node *node = NULL;
    // Node *node_l = NULL; 

    if (TOKEN_TYPE(TP_VAR) || ((TOKEN_TYPE(TP_OPERATOR) && (TOKEN_OP(OP_SUB_EQU) || TOKEN_OP(OP_ADD_EQU) || TOKEN_OP(OP_EQU))))) {
        node = get_assignment(tokens);
                // присваивание 
    } else if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_VAR)) {
        node = ger_var_declaration(tokens);
                // декларация переменных 
    } else if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_IF)) {
        node = get_condition(tokens);
        // условные операторы
    } else if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_WHILE)) {
    node = get_cycle(tokens);
    //циклы
    } else if (TOKEN_TYPE(TP_OPERATOR) && (TOKEN_OP(OP_SCAN) || TOKEN_OP(OP_PRINT_VAR))) {
        node = get_in_out_put(tokens);
        // 
    } else if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_EXIT)) {
        node = get_exit(tokens);
    }
    // else if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_DEC_FUNC)) {
        // printf("hhgfd");
        // node = get_decl_func(tokens);
    // }
    //  (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_DEC_FUNC)) {

    // }
    // for (int i = tokens->size; i < tokens->capacity; i++) {
    //     printf("%d [\"%s\"] {%d} ", tokens->array[i].type, tokens->array[i].elem, tokens->array[i].oper);
    // }
    // printf("\n");

    // node_l = create_node(TP_OPERATOR, OP_CONNECT, node_l, node);

    // dump_tree(node);
// декларация функций
    

    // assert(node_l && "null node in recursive despend get_type");

    return node;
}

Node *get_exit(Tokenizer *tokens) {
    Node *node = NULL;
    Node *node_l = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_EXIT)) {
        tokens->size++;
        assert(tokens->array[tokens->size++].oper == OP_END_LINE && "sintax error: you forgot ';' in oper EXIT");

        node_l = create_node(TP_OPERATOR, OP_EXIT, NULL, NULL);
        node = CN(node_l, get_type(tokens));
    }

    return node;
}

Node *get_in_out_put(Tokenizer *tokens) {

    Node *node = NULL;
    Node *node_l = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && (TOKEN_OP(OP_SCAN) || TOKEN_OP(OP_PRINT_VAR))) {
        
        int op = tokens->array[tokens->size].oper;

        tokens->size++;

        if (op == OP_SCAN) {
            assert(tokens->array[tokens->size++].oper == OP_LEFT_BRACKET && "sintax error: you forgot left bracket in oper SCAN");
            node_l = create_node(TP_OPERATOR, OP_SCAN, get_var(tokens), NULL);
            
            assert(tokens->array[tokens->size++].oper == OP_RIGHT_BRACKET && "sintax error: you forgot right bracket in oper SCAN");
            assert(tokens->array[tokens->size++].oper == OP_END_LINE && "sintax error: you forgot ';' in oper SCAN");
        } else if (op == OP_PRINT_VAR) {

            assert(tokens->array[tokens->size++].oper == OP_LEFT_BRACKET && "sintax error: you forgot left bracket in oper PRINT");
            node_l = create_node(TP_OPERATOR, OP_PRINT_VAR, get_var(tokens), NULL);
            
            assert(tokens->array[tokens->size++].oper == OP_RIGHT_BRACKET && "sintax error: you forgot right bracket in oper PRINT");
            assert(tokens->array[tokens->size++].oper == OP_END_LINE && "sintax error: you forgot ';' in oper PRINT");
        }
        
        node = CN(node_l, get_type(tokens));
    }
    return node;
}

Node *get_cycle(Tokenizer *tokens) {

    Node *node = NULL;
    Node *node_l = NULL;
    Node *node_body = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_WHILE)) {
        tokens->size++;
        assert(tokens->array[tokens->size++].oper == OP_LEFT_BRACKET && "sintax error: you forgot left bracket in oper WHILE");
        
        node_l = get_add_sub(tokens);

        assert(tokens->array[tokens->size++].oper == OP_RIGHT_BRACKET && "sintax error: you forgot right bracket in oper WHILE");
       
        node_body = get_body(tokens);

        node_l = create_node(TP_OPERATOR, OP_WHILE, node_l, node_body);

        node = CN(node_l, get_type(tokens));
    }

    return node;
}

Node *get_condition(Tokenizer *tokens) {

    Node *node = NULL;
    Node *node_l = NULL;
    Node *node_r = NULL;

    Node *node_l_body = NULL;
    Node *node_r_body = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_IF)) {

        tokens->size++;
        assert(tokens->array[tokens->size++].oper == OP_LEFT_BRACKET && "sintax error: you forgot left bracket in oper IF");
        node_l = get_add_sub(tokens);

        assert(tokens->array[tokens->size++].oper == OP_RIGHT_BRACKET && "sintax error: you forgot right bracket in oper IF");
        

        node_l_body = get_body(tokens);

        if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_ELSE)) {
            tokens->size++;

            if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_IF)) {
                node_r_body = get_condition(tokens);
            } else {
                node_r_body = get_body(tokens);
            }
        }

        if (node_r_body) {
            node_r = create_node(TP_OPERATOR, OP_ELSE, node_l_body, node_r_body);
            node_l = create_node(TP_OPERATOR, OP_IF, node_l, node_r);
        } else {
            node_l = create_node(TP_OPERATOR, OP_IF, node_l, node_l_body);
        }

        node = CN(node_l, get_type(tokens));
    }

    return node;
}

Node *get_body(Tokenizer *tokens) {

    Node *node = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_LEFT_FIGURE_BRACKET)) {

        tokens->size++;
        node = get_type(tokens);

        assert(tokens->array[tokens->size].oper == OP_RIGHT_FIGURE_BRACKET && "sintax erorr: you forgot } in body");
        tokens->size++;
    }

    return node;
}

Node *ger_var_declaration(Tokenizer *tokens) {

    Node *node = NULL;
    Node *node_l = NULL;
    Node *node_r = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_VAR)) {
        
        tokens->size++;
        node_l = get_var(tokens);
        assert(tokens->array[tokens->size].oper == OP_EQU && "syntax erorr");

        if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_EQU)) {
            tokens->size++;
            node_r = get_add_sub(tokens);
        }

        node_l = create_node(TP_OPERATOR, OP_VAR, node_l, node_r);

        tokens->size++;
        assert(tokens->array[tokens->size].oper != OP_END_LINE && "sintax erorr: you forgot ;");

        node = CN(node_l, get_type(tokens));

        assert(node != NULL && "syntax error in var declaration");
    }

    return node;
}

Node *get_assignment(Tokenizer *tokens) {

    Node *node_r = get_var(tokens);
    Node *node = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && (TOKEN_OP(OP_SUB_EQU) || TOKEN_OP(OP_ADD_EQU) || TOKEN_OP(OP_EQU))) {
        
        int op =  tokens->array[tokens->size].oper;
        tokens->size++;

        Node *node_l = get_add_sub(tokens);

        node_r = create_node(TP_OPERATOR, op, node_r, node_l);

        tokens->size++;
        assert(tokens->array[tokens->size].oper != OP_END_LINE && "sintax erorr: you forgot ;");

        node = CN(node_r, get_type(tokens));

    }

    assert(node != NULL && "null node in recursive despend get type");
    return node;
}

Node *get_add_sub(Tokenizer *tokens) {
    
    Node *node_r = get_mul_div(tokens);
   
    while (TOKEN_TYPE(TP_OPERATOR) && (TOKEN_OP(OP_ADD) || TOKEN_OP(OP_SUB))) {

        int op = tokens->array[tokens->size].oper;

        tokens->size++;

        Node *node_l = get_mul_div(tokens);

        if (op == OP_ADD) {
            node_r = ADD(node_r, node_l);
        } else if (op == OP_SUB) {
            node_r = SUB(node_r, node_l);
        }
    }

    return node_r; 
}


Node *get_mul_div(Tokenizer *tokens) {

    Node *node_r = get_deg(tokens);

    while (TOKEN_TYPE(TP_OPERATOR) && (TOKEN_OP(OP_MUL) || TOKEN_OP(OP_DIV))) {

        int op = tokens->array[tokens->size].oper;

        tokens->size++;

        Node *node_l = get_deg(tokens);
        
        if (op == OP_MUL) {
            node_r = MUL(node_r, node_l);
        } else if (op == OP_DIV) {
            node_r = DIV(node_r, node_l);
        }
    }

    return node_r;
}

Node *get_deg(Tokenizer *tokens) {

    Node *node_r = get_unary_op(tokens);
 
    while (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_DEG)) {

        int op = tokens->array[tokens->size].oper;
        tokens->size++;

        Node *node_l = get_unary_op(tokens);
        
        if (op == OP_DEG) {
            node_r = DEG(node_r, node_l);
        }
    }

    return node_r;
}

Node *get_unary_op(Tokenizer *tokens) {

    Node *node_r = get_bracket(tokens);

    if (TOKEN_TYPE(TP_OPERATOR) && TOKEN_OP(OP_LN)) {

        int op = tokens->array[tokens->size].oper;
        tokens->size++;        

        Node *node_l = get_bracket(tokens);
        
        if (op == OP_LN) {
            node_r = LN(node_l);
        } else if (op == OP_SIN) {
            node_r = SIN(node_l);
        } else if (op == OP_COS) {
            node_r = COS(node_l);
        }
    }

    assert(node_r != NULL);

    return node_r;
}

Node *get_bracket(Tokenizer *tokens) {

    Node *node = NULL;

    if (TOKEN_TYPE(TP_OPERATOR) && tokens->array[tokens->size].oper == OP_LEFT_BRACKET) {
        tokens->size++;        

        node = get_add_sub(tokens);

        assert(tokens->array[tokens->size].oper == OP_RIGHT_BRACKET);

        tokens->size++;

    } else if (TOKEN_TYPE(TP_NUMBER)) {

        node = get_number(tokens);

    } else if (TOKEN_TYPE(TP_VAR)) {

        node = get_var(tokens);

    }

    return node;
}

Node *get_number(Tokenizer *tokens) {

    Node *node = CREATE_NUM(atoi(tokens->array[tokens->size].elem));

    tokens->size++;  

    assert(node != NULL);

    return node;
}


Node *get_var(Tokenizer *tokens) {

    Node *node = NULL;

    node = CREATE_VAR(tokens->array[tokens->size].elem);

    tokens->size++;        

    assert(node != NULL);

    return node;

}
// -------------------------------------END RECURSIVE DESCENT---------------------------------------------------


// -------------------------------------BEGIN TOKENIZER---------------------------------------------------

int is_oper(char symbol) {

    return (symbol == OP_ADD || symbol == OP_SUB || symbol == OP_DIV 
         || symbol == OP_DEG || symbol == OP_LN  || symbol == OP_MUL);

}

void create_number_token(Tokenizer *tokens, char **text_buf, int ip) {

    tokens->array[ip].type = TP_NUMBER;
    char *point = tokens->array[ip].elem;

    while ('0' <= **text_buf && **text_buf <= '9') {
        *point++ = **text_buf;
        (*text_buf)++;
    }

}

void create_var_token(Tokenizer *tokens, char **text_buf, int ip) {

    tokens->array[ip].type = TP_VAR;
    char *point = tokens->array[ip].elem;

    while (isalpha(**text_buf) || isdigit(**text_buf)) {
        *point++ = **text_buf;
        (*text_buf)++;
    }

}

#define DEF_OPER(operator, num, mean, len, ...)                              \
    if (strncmp(text_buf, mean, len) == 0) {                            \
        tokens->array[i].type = TP_OPERATOR;                            \
        tokens->array[i].oper = operator;                               \
        tokens->array[i].elem = (char *) calloc(len + 1, sizeof(char)); \
        strcpy(tokens->array[i].elem, mean);                            \
        text_buf += len;                                                \
    } else                                                              \

void tokenizer_ctor(Tokenizer *tokens, char *text_buf) {

    assert(tokens   != NULL && "null poiner tokens");
    assert(text_buf != NULL && "null poiner text_buf");

    long long unsigned size_buf = strlen(text_buf);

    tokens->array = (Token_elem *) calloc(size_buf, sizeof(Token_elem));

    unsigned i = 0;

    for (; i < size_buf && *text_buf != '\0'; i++) {

        if ('0' <= *text_buf && *text_buf <= '9') {
            
            tokens->array[i].elem = (char *) calloc(size_buf, sizeof(char));
            create_number_token(tokens, &text_buf, i);
            
        } else 
            #include "../config_oper.hpp"


        /*} else */ if (isalpha(*text_buf)) {
            tokens->array[i].elem = (char *) calloc(size_buf, sizeof(char));
            create_var_token(tokens, &text_buf, i);
            
        } else break;
    }

    tokens->capacity = i;

    tokens->size = 0;
}

#undef DEF_OPER

void tokenizer_dtor(Tokenizer *tokens) {

    for (int i = 0; i < tokens->capacity; i++) {
        free(tokens->array[i].elem);
    }

    free(tokens->array);
}

// -------------------------------------END TOKENIZER---------------------------------------------------



//--------------------------------------BEGIN TREE OUNPUT--------------------------------------------------------

int checking_for_priority(Node *node, Node *parent) {

    if (!node || !parent) return 0;

    return (parent->type == TP_OPERATOR && node->type == TP_OPERATOR && 
          ((parent->value.oper == OP_ADD || parent->value.oper == OP_SUB) ||
           (node->value.oper == parent->value.oper) || 
           (node->value.oper == OP_MUL && parent->value.oper == OP_DIV) ||
           (parent->value.oper == OP_MUL && node->value.oper == OP_DIV)));

}

void print_tree(Node *node, Node *parent) {
     
    if (!node) return;     
     
    if (node->left && parent && !checking_for_priority(node, parent)) {     
        fprintf(file_tree, "(");     
    }     
        
    if (!(!node->left && node->right)) {     
        print_tree(node->left, node);     
    }     
     
    print_node(file_tree, node);     
         
    if (node->right) {     
     
        print_tree(node->right, node);
        
        if (!(!node->left && node->right) && parent && !checking_for_priority(node, parent)) {
            fprintf(file_tree, ")");
        }
        
    }
    
}

#define DEF_OPER(operator, num, string, len, ...) \
        case (operator): {                     \
            fprintf(file, string);       \
            break;                       \
        }                                \


void print_node(FILE *file, Node *node) {
    assert(node && "node null");

    switch (node->type) {
        case TP_OPERATOR: {
            switch (node->value.oper) {
                
                #include "../config_oper.hpp"

                default: {
                    fprintf(file, "didn't find oper");
                    break;
                }
            }

            break;
        } case TP_VAR: {
            fprintf(file, "%s", node->value.var);
            break;
        } case TP_NUMBER: {
            if (node->value.number < 0) {
                fprintf(file, "(%d)", node->value.number);
            } else {
                fprintf(file, "%d", node->value.number);
            } 
            break;
        }

        default:
            break;
    }
}

#undef DEF_OPER

void close_file() {
    fclose(file_tree);
}

static int count_png = 0;

void dump_tree(Node *root) {

    assert(root != nullptr && "null pointer tree");
    FILE *dot_file = fopen(NAME_GRAPH_FILE, "w");

    fprintf(dot_file,"digraph {\n");
    // printf("")

    graph_dump(dot_file, root, root->left);
    graph_dump(dot_file, root, root->right);

    fprintf(dot_file,"}\n");

    fclose(dot_file);

    const int size_cmd = 100; 
    char cmd[size_cmd] = "";
    
    sprintf(cmd, "dot res/graph.dot -Tpng -o res/output%d.png 2>text_error.txt", count_png);
    count_png++;
    system(cmd);
    
}


void graph_dump(FILE *dot_file, Node *node, Node *node_son) {
    
    if (!node_son) {
        return;
    }

    fprintf   (dot_file, "\tnode%p[label=\"", node);
    print_node(dot_file, node);
    fprintf   (dot_file, "\"]\n");

    fprintf   (dot_file, "\tnode%p[label=\"", node_son);
    print_node(dot_file, node_son);
    fprintf   (dot_file, "\"]\n");
    
    fprintf(dot_file, "\tnode%p -> node%p\n", node, node_son);

    graph_dump(dot_file, node_son, node_son->left);
    graph_dump(dot_file, node_son, node_son->right);

}

//--------------------------------------END TREE OUNPUT----------------------------------------------------------


//------------------------------------BEGIN DIFFERENTIATOR-----------------------------------------------------------


Node *copy_tree(Node *node) {

    if (!node) return node;

    Node *copy_node = (Node *) calloc(1, sizeof(Node));

    copy_node->left      = node->left;
    copy_node->right     = node->right;
    copy_node->value     = node->value;
    copy_node->right     = node->right;
    copy_node->type   = node->type;

    if (node->left) {
        copy_node->left = copy_tree(copy_node->left);
    }

    if (node->right) {
        copy_node->right = copy_tree(copy_node->right);
    }

    return copy_node;

}

Node *create_node(TYPE_NODE tp_node, int value, Node *node_left, Node *node_right) {
    
    Node *node = (Node *)calloc(1, sizeof(Node));

    node->type = tp_node;
    node->left = node_left;
    node->right = node_right;

    switch (tp_node) {
        case TP_NUMBER: {
            node->value.number = value;
            break;
        }

        case TP_OPERATOR: {
            node->value.oper = (TYPE_OPERATOR)value;
            break;
        }

        case TP_VAR: {
            break;
        }

        default:
            printf("didn't find type node\n");
            break;
    }

    return node;
}

Node *create_var_node(char *var, Node *node_left, Node *node_right) {

    Node *node = (Node *)calloc(1, sizeof(Node));

    node->type = TP_VAR;
    node->left = node_left;
    node->right = node_right;

    node->value.var = (char *) calloc(strlen(var), sizeof(char));
    node->value.var = strcpy(node->value.var, var);

    return node;
}

Node *create_func_node(char *name_func, Node *node_left, Node *node_right) {
    Node *node = (Node *)calloc(1, sizeof(Node));

    node->type = TP_FUNC;
    node->left = node_left;
    node->right = node_right;

    node->value.var = (char *) calloc(strlen(name_func), sizeof(char));
    node->value.var = strcpy(node->value.var, name_func);

    return node;
}

//-----------------------------------------END DIFFERENTIATOR-----------------------------------------------------------


