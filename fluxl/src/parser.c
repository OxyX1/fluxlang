#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

// Create a new parser
Parser* Parser_New(Token **tokens, size_t token_count) {
    Parser *parser = (Parser *)malloc(sizeof(Parser));
    if (!parser) {
        fprintf(stderr, "Memory allocation failed for Parser\n");
        return NULL;
    }
    parser->tokens = tokens;
    parser->position = 0;
    parser->token_count = token_count;
    return parser;
}

// Free the parser
void Parser_Free(Parser *parser) {
    if (parser) {
        free(parser);
    }
}

// Get the current token
Token* Parser_Current(Parser *parser) {
    if (parser->position < parser->token_count) {
        return parser->tokens[parser->position];
    }
    return NULL;
}

// Advance to the next token
void Parser_Advance(Parser *parser) {
    if (parser->position < parser->token_count) {
        parser->position++;
    }
}

// Parse a literal (e.g., numbers, strings)
AstNode* ParseLiteral(Parser *parser) {
    Token *current = Parser_Current(parser);
    if (current->type == TOKEN_NUMBER) {
        AstNode *node = (AstNode *)malloc(sizeof(AstNode));
        node->type = AST_LITERAL;
        node->value = atoi(current->value); // Convert string to integer
        Parser_Advance(parser);
        return node;
    }
    return NULL;
}

// Parse a binary operation (e.g., addition, subtraction)
AstNode* ParseBinaryOp(Parser *parser) {
    AstNode *left = ParseLiteral(parser);
    if (!left) return NULL;

    Token *current = Parser_Current(parser);
    if (current && current->type == TOKEN_OPERATOR) {
        char op = current->value[0];
        Parser_Advance(parser);

        AstNode *right = ParseLiteral(parser);
        if (!right) {
            fprintf(stderr, "Error: Expected a literal after operator\n");
            free(left);
            return NULL;
        }

        AstNode *node = (AstNode *)malloc(sizeof(AstNode));
        node->type = AST_BINARY_OP;
        node->bin_op.left = left;
        node->bin_op.right = right;
        node->bin_op.op = op;
        return node;
    }

    return left;
}

// Parse the entire input
AstNode* Parser_Parse(Parser *parser) {
    Token *current = Parser_Current(parser);
    if (!current) {
        fprintf(stderr, "Error: Unexpected end of input\n");
        return NULL;
    }

    // Example: Parse a single binary operation
    AstNode *node = ParseBinaryOp(parser);
    if (!node) {
        fprintf(stderr, "Error: Failed to parse binary operation\n");
    }
    return node;
}