#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ast.h"

typedef enum { AST_LITERAL, AST_BINARY_OP } AstNodeType;

typedef struct AstNode {
    AstNodeType type;
    union {
        int value;  // For literals
        struct {
            struct AstNode* left;
            struct AstNode* right;
            char op;  // For operators ('+', '-', etc.)
        } bin_op;
    };
} AstNode;

// Function to free an AST node
void FreeAstNode(AstNode *node) {
    if (!node) return;
    if (node->type == AST_BINARY_OP) {
        FreeAstNode(node->bin_op.left);
        FreeAstNode(node->bin_op.right);
    }
    free(node);
}
