#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct {
    Token current_token;
    const char *source;
    int position;
} Parser;

void init_parser(Parser *parser, const char *source);
void advance(Parser *parser);
ASTNode* parse(Parser *parser);

#endif // PARSER_H
