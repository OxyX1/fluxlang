// parser.h
#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY_OP,
    AST_ASSIGNMENT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        int number;
        struct {
            struct ASTNode* left;
            Token op;
            struct ASTNode* right;
        } binary;
        struct {
            char* name;
            struct ASTNode* value;
        } assign;
    };
} ASTNode;

ASTNode* parse(void);
void print_ast(ASTNode* node);
void free_ast(ASTNode* node);

#endif
