#include "../include/front_end.hpp"


void printf_asm(const char *FILE_INPUT, Node *node, Variable_table *name_table) {
    
    FILE *file = fopen(FILE_INPUT, "w");

    print_asm_code(node->left, node, file, name_table);
    print_asm_code(node->right, node, file, name_table);

    fprintf(file, "HLT\n");
    
    fclose(file);

}

static int count_if = 0;
static int count_else = 0;
static int count_while = 0;

void print_asm_code(Node *node, Node *parent, FILE *file, Variable_table *name_table) {

    if (!node) return;

    if (parent->type == TP_OPERATOR && parent->left == node  && parent->value.oper == OP_WHILE) {
        count_while++;
        fprintf(file, "\nlable_while_beg_%d:\n\n", count_while);
    } else if (parent->type == TP_OPERATOR && parent->left == node && parent->value.oper == OP_DEC_FUNC) {
        fprintf(file, "func_%s:\n", node->value.var);

    }

    print_asm_code(node->left, node, file, name_table);

    print_asm_code(node->right, node, file, name_table);

    print_asm_node(node, parent, file, name_table);
    
}


#define DEF_OPER(op, num_op, name, len_name, ...)   \
    case op: {                                      \
        __VA_ARGS__                                 \
        break;                                      \
    }                                               \

void print_asm_node(Node *node, Node *parent, FILE *file, Variable_table *name_table) {
    
 
    switch (node->type) {
        case TP_OPERATOR:
            switch (node->value.oper) {
                #include "../config_oper.hpp"
                        
            default:
                printf("oper didn't find\n");
                break;
            }
            break;
        case TP_VAR:
            if (!(parent->type == TP_OPERATOR && (parent->value.oper == OP_VAR || parent->value.oper == OP_EQU || parent->value.oper == OP_SCAN))) {
                fprintf(file, "PUSH [%d]\n", find_name(name_table, node->value.var));
            } else if (parent->type == TP_OPERATOR && parent->right == node && (parent->value.oper == OP_VAR || parent->value.oper == OP_EQU)) {
                fprintf(file, "PUSH [%d]\n", find_name(name_table, node->value.var));
            }
            break;

        case TP_NUMBER:
            fprintf(file, "PUSH %d\n", node->value.number);
            break;

        case TP_FUNC:
            if (!(parent->type == TP_OPERATOR && parent->value.oper == OP_DEC_FUNC)){
                fprintf(file, "CALL func_%s\n", node->value.var);
            } 
            break;
    
        default:
            break;
    }

    if (parent->type == TP_OPERATOR && parent->left == node) {
        if (parent->value.oper == OP_IF) {
            fprintf(file, "PUSH 0\n");
            count_if++;
            fprintf(file, "JE lable_if_%d\n", count_if);
        } else if (parent->value.oper == OP_ELSE) {
            fprintf(file, "JMP lable_else_%p\n\n", parent);
            fprintf(file, "lable_if_%d:\n", count_if);
        } else if (parent->value.oper == OP_WHILE) {
            fprintf(file, "PUSH 0\n");
            fprintf(file, "JE lable_while_end_%d\n", count_while);
            // fprintf(file, "lable_while_beg_%d:\n", count_while);
        }
    } 
}

#undef DEF_OPER

void ctor_var_func_table(Variable_table *name_table) {
    
    name_table->arr = (Arr_var *)calloc(name_table->capacity, sizeof(Arr_var));

    name_table->size = 0;

}

int find_name(Variable_table *name_table, char *var) {
    
    int id = -1;
    
    for (int i = 0; i < name_table->size; i++) {
        if (strcmp(name_table->arr[i].name, var) == 0) {
            id = name_table->arr[i].id;
            break;
        }
    }

    return id;
}