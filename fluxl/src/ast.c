#include "../include/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode* create_ast_node(ASTNodeType type, const char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->value = value ? strdup(value) : NULL;
    return node;
}

void free_ast(ASTNode *node) {
    if (node) {
        if (node->value) {
            free(node->value);
        }
        free_ast(node->left);
        free_ast(node->right);
        free(node);
    }
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch (node->type) {
        case AST_MOD:
            printf("MOD: %s\n", node->value);
            break;
        case AST_RETURN:
            printf("RETURN: %s\n", node->value);
            break;
        case AST_FUNCTION:
            printf("FUNCTION: %s\n", node->value);
            break;
        case AST_NUMBER:
            printf("NUMBER: %s\n", node->value);
            break;
        case AST_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->value);
            break;
        default:
            printf("UNKNOWN\n");
            break;
    }

    print_ast(node->left, indent + 1);
    print_ast(node->right, indent + 1);
}
