#ifndef AST_H
#define AST_H

// AST Node Types
typedef enum {
    AST_LITERAL,
    AST_BINARY_OP
} AstNodeType;

// AST Node Structure
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

#endif // AST_H