#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Token **tokens;
    size_t position;
    size_t token_count;
} Parser;

// Function declarations
Parser* Parser_New(Token **tokens, size_t token_count);
void Parser_Free(Parser *parser);
AstNode* Parser_Parse(Parser *parser);

#endif // PARSER_H