#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Struct to represent a node in the AST
typedef struct ASTNode {
    char *value;             // Token value (e.g., variable name, keyword)
    int type;                // Token type (from lexer)
    struct ASTNode *left;    // Left child (for binary operations, etc.)
    struct ASTNode *right;   // Right child
} ASTNode;

// Function declarations for the parser
ASTNode* parseExpression(Token *tokens, int *currentIndex);
ASTNode* parseTerm(Token *tokens, int *currentIndex);
ASTNode* parseFactor(Token *tokens, int *currentIndex);
ASTNode* parseAssignment(Token *tokens, int *currentIndex);
ASTNode* parseDeclaration(Token *tokens, int *currentIndex);

// Function to create a new AST node
ASTNode* newASTNode(char *value, int type);

// Function to free the AST
void freeAST(ASTNode *node);

#endif // PARSER_H
