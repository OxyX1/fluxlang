#ifndef AST_H
#define AST_H

typedef enum {
    AST_MOD,
    AST_RETURN,
    AST_FUNCTION,
    AST_EXPRESSION,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_UNKNOWN
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    struct ASTNode *left;
    struct ASTNode *right;
    char *value; // Can hold a string or number
} ASTNode;

ASTNode* create_ast_node(ASTNodeType type, const char *value);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent);

#endif // AST_H
