#include "../include/front_end.hpp"


void printf_asm(const char *FILE_INPUT, Node *node, Variable_table *var_table) {
    
    FILE *file = fopen(FILE_INPUT, "w");

    print_asm_code(node->left, node, file, var_table);
    print_asm_code(node->right, node, file, var_table);

    fprintf(file, "HLT\n");
    
    fclose(file);

}

void print_asm_code(Node *node, Node *parent, FILE *file, Variable_table *var_table) {

    if (!node) return;

    print_asm_code(node->left, node, file, var_table);
    print_asm_code(node->right, node, file, var_table);


    print_asm_node(node, parent, file, var_table);
    
}

static int count_if = 1;
static int count_else = 1;
static int count_while = 1;


#define DEF_OPER(op, num_op, name, len_name, ...)   \
    case op: {                                      \
        __VA_ARGS__                                 \
        break;                                      \
    }                                               \

void print_asm_node(Node *node, Node *parent, FILE *file, Variable_table *var_table) {
    
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
// табличка переменных
            if (!(parent->type == TP_OPERATOR && (parent->value.oper == OP_VAR || parent->value.oper == OP_EQU))) {
                fprintf(file, "PUSH [%d]\n", find_var(var_table, node->value.var));
            }
            break;

        case TP_NUMBER:
            fprintf(file, "PUSH %d\n", node->value.number);
            break;

        case TP_FUNC:
            break;
    
        default:
            break;
    }

}

#undef DEF_OPER

void ctor_var_table(Variable_table *var_table) {
    
    var_table->arr = (Arr_var *)calloc(var_table->capacity, sizeof(Arr_var));

    var_table->size = 0;

}

int find_var(Variable_table *var_table, char *var) {
    int id = -1;
    for (int i = 0; i < var_table->size; i++) {
        if (strcmp(var_table->arr[i].name_var, var) == 0) {
            id = var_table->arr[i].id;
            printf("%d\n", id);
            break;
        }
    }
    return id;
}