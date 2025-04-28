#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/lexer.h"

// Function to create a new AST node
ASTNode* newASTNode(char *value, int type) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->value = strdup(value);
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to free an AST
void freeAST(ASTNode *node) {
    if (node) {
        free(node->value);
        freeAST(node->left);
        freeAST(node->right);
        free(node);
    }
}

// Function to parse expressions (handles +, - operators)
ASTNode* parseExpression(Token *tokens, int *currentIndex) {
    ASTNode *left = parseTerm(tokens, currentIndex);
    
    while (tokens[*currentIndex].type == TOKEN_OPERATOR && 
           (tokens[*currentIndex].value[0] == '+' || tokens[*currentIndex].value[0] == '-')) {
        char *op = tokens[*currentIndex].value;
        (*currentIndex)++;
        
        ASTNode *right = parseTerm(tokens, currentIndex);
        ASTNode *opNode = newASTNode(op, TOKEN_OPERATOR);
        opNode->left = left;
        opNode->right = right;
        
        left = opNode;
    }

    return left;
}

// Function to parse terms (handles * and / operators)
ASTNode* parseTerm(Token *tokens, int *currentIndex) {
    ASTNode *left = parseFactor(tokens, currentIndex);

    while (tokens[*currentIndex].type == TOKEN_OPERATOR && 
           (tokens[*currentIndex].value[0] == '*' || tokens[*currentIndex].value[0] == '/')) {
        char *op = tokens[*currentIndex].value;
        (*currentIndex)++;

        ASTNode *right = parseFactor(tokens, currentIndex);
        ASTNode *opNode = newASTNode(op, TOKEN_OPERATOR);
        opNode->left = left;
        opNode->right = right;

        left = opNode;
    }

    return left;
}

// Function to parse factors (handles numbers, identifiers, and parenthesis)
ASTNode* parseFactor(Token *tokens, int *currentIndex) {
    if (tokens[*currentIndex].type == TOKEN_IDENTIFIER || tokens[*currentIndex].type == TOKEN_NUMBER) {
        char *value = tokens[*currentIndex].value;
        ASTNode *node = newASTNode(value, tokens[*currentIndex].type);
        (*currentIndex)++;
        return node;
    }
    
    // Handle parentheses for grouping
    if (tokens[*currentIndex].type == TOKEN_OPERATOR && strcmp(tokens[*currentIndex].value, "(") == 0) {
        (*currentIndex)++;
        ASTNode *node = parseExpression(tokens, currentIndex);
        
        if (tokens[*currentIndex].type == TOKEN_OPERATOR && strcmp(tokens[*currentIndex].value, ")") == 0) {
            (*currentIndex)++;
            return node;
        } else {
            printf("Error: Missing closing parenthesis\n");
            return NULL;
        }
    }

    printf("Error: Unexpected token '%s'\n", tokens[*currentIndex].value);
    return NULL;
}

// Function to parse an assignment statement
ASTNode* parseAssignment(Token *tokens, int *currentIndex) {
    if (tokens[*currentIndex].type == TOKEN_IDENTIFIER) {
        char *identifier = tokens[*currentIndex].value;
        (*currentIndex)++;
        
        if (tokens[*currentIndex].type == TOKEN_OPERATOR && strcmp(tokens[*currentIndex].value, "=") == 0) {
            (*currentIndex)++;
            ASTNode *right = parseExpression(tokens, currentIndex);
            
            ASTNode *assignNode = newASTNode("=", TOKEN_OPERATOR);
            assignNode->left = newASTNode(identifier, TOKEN_IDENTIFIER);
            assignNode->right = right;
            
            return assignNode;
        }
    }

    return NULL;
}

// Function to parse variable declaration
ASTNode* parseDeclaration(Token *tokens, int *currentIndex) {
    if (tokens[*currentIndex].type == TOKEN_KEYWORD && strcmp(tokens[*currentIndex].value, "int") == 0) {
        (*currentIndex)++;
        
        if (tokens[*currentIndex].type == TOKEN_IDENTIFIER) {
            char *identifier = tokens[*currentIndex].value;
            (*currentIndex)++;
            
            if (tokens[*currentIndex].type == TOKEN_OPERATOR && strcmp(tokens[*currentIndex].value, "=") == 0) {
                (*currentIndex)++;
                ASTNode *right = parseExpression(tokens, currentIndex);
                
                ASTNode *declNode = newASTNode("int", TOKEN_KEYWORD);
                declNode->left = newASTNode(identifier, TOKEN_IDENTIFIER);
                declNode->right = right;
                
                return declNode;
            }
        }
    }

    return NULL;
}
