DEF_OPER(OP_CONNECT, 0, "CN", 1,
            {
            fprintf(file, "\n");
            })

DEF_OPER(OP_SUB_EQU, 11, "-=", 2,
            {
            fprintf(file, "POP ax\n");
            fprintf(file, "PUSH [%d]\n", find_var(var_table, node->left->value.var));
            fprintf(file, "PUSH ax\n");
            fprintf(file, "SUB\n");
            fprintf(file, "POP [%d]\n", find_var(var_table, node->left->value.var));
            })

DEF_OPER(OP_ADD_EQU, 12, "+=", 2, 
            {
            fprintf(file, "PUSH [%d]\n", find_var(var_table, node->left->value.var));
            fprintf(file, "ADD\n");
            fprintf(file, "POP [%d]\n", find_var(var_table, node->left->value.var));
            }) 

DEF_OPER(OP_ADD, 1, "+", 1, 
            {
            fprintf(file, "ADD\n");
            })


DEF_OPER(OP_SUB, 2, "-", 1, 
            {
            fprintf(file, "SUB\n");
            })

DEF_OPER(OP_DIV, 3, "/", 1, 
            {
            fprintf(file, "DIV\n");
            })

DEF_OPER(OP_MUL, 4, "*", 1, 
            {
            fprintf(file, "MUL\n");
            })

DEF_OPER(OP_DEG, 5, "^", 1, 
            {
            fprintf(file, "DEG\n");
            })

DEF_OPER(OP_LN, 6, "ln", 2, 
            {
            fprintf(file, "LN\n");
            })


DEF_OPER(OP_SIN, 7, "sin", 3, 
            {
            fprintf(file, "\n");
            })


DEF_OPER(OP_COS, 8, "cos", 3, 
            {
            fprintf(file, "\n");
            })


DEF_OPER(OP_VAR, 9, "var", 3,  
            {
            assert(find_var(var_table, node->left->value.var) == -1 && "you are initializing a variable that already exists");
            
            var_table->arr[var_table->size].name_var = (char *) calloc(strlen(node->left->value.var) + 1, sizeof(char));
            strcpy(var_table->arr[var_table->size].name_var, node->left->value.var);
            
            var_table->arr[var_table->size].id = var_table->size;
            
            fprintf(file, "POP [%d]\n", var_table->size);
            var_table->size++;        
            })

DEF_OPER(OP_EQU, 10, "=", 1, 
            {
            fprintf(file, "POP [%d]\n", find_var(var_table, node->left->value.var));
            })


DEF_OPER(OP_LEFT_BRACKET, 13, "(", 1,
            {
            })

DEF_OPER(OP_RIGHT_BRACKET, 14, ")", 1, 
            {
            })

DEF_OPER(OP_END_LINE, 15, ";", 1, 
            {
            })

DEF_OPER(OP_IF, 16, "if", 2,
            {
            if (node->right->type == TP_OPERATOR && node->right->value.oper != OP_ELSE) {
                fprintf(file, "lable_if_%d:\n", count_if);
            }
            })

DEF_OPER(OP_ELSE, 17, "else", 4,
            {
            fprintf(file, "lable_else_%p:\n", node);
            })

DEF_OPER(OP_LEFT_FIGURE_BRACKET, 18, "{", 1, 
            {
            })

DEF_OPER(OP_RIGHT_FIGURE_BRACKET, 19, "}", 1, 
            {
            })

DEF_OPER(OP_WHILE, 20, "while", 5,
            {
            fprintf(file, "JMP lable_while_beg_%d\n", count_while);
            
            fprintf(file, "lable_while_end_%d:\n", count_while);
            })

DEF_OPER(OP_DEC_FUNC, 21, "decl", 4, )

DEF_OPER(OP_RET, 22, "return", 6, )

DEF_OPER(OP_SCAN, 23, "scan", 4, 
            {
            fprintf(file, "IN\n");
            fprintf(file, "POP [%d]\n", find_var(var_table, node->left->value.var));
            })

DEF_OPER(OP_PRINT_VAR, 24, "print_var", 9, 
            {
            fprintf(file, "OUT\n");
            })

        
DEF_OPER(OP_PRINT_STR, 25, "print_str", 9, 
            {
            fprintf(file, "OUT_CHAR\n");
            })

DEF_OPER(OP_EXIT, 26, "exit", 4, 
            {
            fprintf(file, "HLT\n");
            })







