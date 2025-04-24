// parser.c
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Token current;

extern Token next_token();
extern void free_token(Token);
static Token advance_token() {
    free_token(current);
    current = next_token();
    return current;
}

static ASTNode* parse_expression();

static ASTNode* parse_number() {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->number = atoi(current.text);
    advance_token();
    return node;
}

static ASTNode* parse_term() {
    return parse_number();
}

static ASTNode* parse_expression() {
    ASTNode* left = parse_term();
    while (current.type == TOKEN_PLUS) {
        Token op = current;
        advance_token();
        ASTNode* right = parse_term();
        ASTNode* expr = malloc(sizeof(ASTNode));
        expr->type = AST_BINARY_OP;
        expr->binary.left = left;
        expr->binary.op = op;
        expr->binary.right = right;
        left = expr;
    }
    return left;
}

ASTNode* parse_assignment() {
    if (current.type != TOKEN_IDENTIFIER) return NULL;
    char* name = strdup(current.text);
    advance_token();

    if (current.type != TOKEN_ASSIGN) return NULL;
    advance_token();

    ASTNode* value = parse_expression();

    if (current.type == TOKEN_SEMICOLON) advance_token();

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGNMENT;
    node->assign.name = name;
    node->assign.value = value;
    return node;
}

ASTNode* parse(void) {
    current = next_token();
    return parse_assignment();
}

void print_ast(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case AST_NUMBER:
            printf("%d", node->number);
            break;
        case AST_BINARY_OP:
            printf("(");
            print_ast(node->binary.left);
            printf(" %s ", node->binary.op.text);
            print_ast(node->binary.right);
            printf(")");
            break;
        case AST_ASSIGNMENT:
            printf("%s = ", node->assign.name);
            print_ast(node->assign.value);
            printf(";");
            break;
    }
}

void free_ast(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case AST_BINARY_OP:
            free_ast(node->binary.left);
            free_token(node->binary.op);
            free_ast(node->binary.right);
            break;
        case AST_ASSIGNMENT:
            free(node->assign.name);
            free_ast(node->assign.value);
            break;
        default: break;
    }
    free(node);
}
