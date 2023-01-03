#include "../include/middle_end.hpp"
#include "../include/DSL.hpp"

void optimizer_tree(Node *node) {

    int continue_optimizer = 0;

    while (true) {

        if (folding_constant(node, &continue_optimizer) == 0) {         
            break;
        }

        if (collapsing_nodes(node, &continue_optimizer) == 0) {
            break;
        }
        continue_optimizer = 0;
    }

    dump_tree(node);

}

int collapsing_nodes(Node *node, int *continue_optimiz) {
    if (!node) return *continue_optimiz;

    collapsing_nodes(node->left, continue_optimiz);

    if (node->type == TP_OPERATOR && node->value.oper == OP_CONNECT) {
        if (node->right == NULL) {
            COPY_NODE(node->left);
            node->right = node->left->right;
            node->left = node->left->left;  
            *continue_optimiz = 1;       
        }
    } else if (node->type == TP_OPERATOR && node->value.oper == OP_WHILE) {
        if (node->left->type == TP_NUMBER && node->left->value.number == 0) {
            dtor_tree(node);
            node = NULL;
            printf("fff\n");
            *continue_optimiz = 1;       
        }
    }
    if (node) collapsing_nodes(node->right, continue_optimiz);

    return *continue_optimiz;
}

int folding_constant(Node *node, int *continue_optimiz) {
    
    if (!node) return *continue_optimiz;

    folding_constant(node->left, continue_optimiz);

    if (node->left && node->right) {

        if (IS_NODE_OP(OP_MUL) && (IS_ZERO(node->left) || IS_ZERO(node->right))) {
            node->type = TP_NUMBER;
            node->value.number = 0;
            node->left = NULL;
            node->right = NULL;
            *continue_optimiz = 1;

        } else if ((IS_NODE_OP(OP_MUL) || IS_NODE_OP(OP_DEG)) && IS_ONE(node->left)) {
            COPY_NODE(node->right);
            node->left = node->right->left;  
            node->right = node->right->right;
            *continue_optimiz = 1;       

        } else if ((IS_NODE_OP(OP_MUL) || IS_NODE_OP(OP_DEG)) && IS_ONE(node->right)) {
            COPY_NODE(node->left);
            node->right = node->left->right;
            node->left = node->left->left;  
            *continue_optimiz = 1;

        } else if ((IS_NODE_OP(OP_ADD) || IS_NODE_OP(OP_SUB)) && IS_ZERO(node->left)) {
            COPY_NODE(node->right);
            node->left = node->right->left;  
            node->right = node->right->right;
            *continue_optimiz = 1;

        } else if ((IS_NODE_OP(OP_ADD) || IS_NODE_OP(OP_SUB)) && IS_ZERO(node->right)) {
            COPY_NODE(node->left);
            node->right = node->left->right;
            node->left = node->left->left; 
            *continue_optimiz = 1;

        } else if (node->type == TP_OPERATOR && (IS_CONST_SON_NODE(node))) {
            OP_CONST(node->value.oper);
            *continue_optimiz = 1;

        } else if (IS_NODE_OP(OP_DEG) && IS_ZERO(node->right)) {
            node->type = TP_NUMBER;
            node->value.number = 1;
            node->left = NULL;
            node->right = NULL;
            *continue_optimiz = 1;

        }
    }

    folding_constant(node->right, continue_optimiz);

    return *continue_optimiz;
}

int pow(int x, int y) {
    while (y > 1) {
        x *= x;
        y--;
    }
    return x;
}