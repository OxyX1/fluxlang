// lexer.h
#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON
} TokenType;

typedef struct {
    TokenType type;
    char* text;
} Token;

void init_lexer(const char* input);
Token next_token(void);
void free_token(Token tok);

#endif
