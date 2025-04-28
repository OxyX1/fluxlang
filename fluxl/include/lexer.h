#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>  // For NULL

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_POINTER,
    TOKEN_INVALID,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

extern const char *keywords[];
extern const char *pointers[];
extern const char *parenKeywords[];

int is_keyword(const char *str);
Token get_next_token(const char **src);

#endif  // LEXER_H
