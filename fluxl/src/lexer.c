#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../include/lexer.h"

const char *keywords[] = {"if", "else", "while", "mod"};
const char *pointers[] = {"int", "float", "string"};
const char *parenKeywords[] = {"{", "}", "(", ")", "[", "]", "."};

int is_keyword(const char *str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;  // Keyword found
        }
    }
    return 0;  // Not a keyword
}

Token get_next_token(const char **src) {
    Token token = {TOKEN_INVALID, ""};

    // Skip whitespace
    while (isspace(**src)) {
        (*src)++;
    }

    if (**src == '\0') {
        token.type = TOKEN_EOF;  // End of file
        return token;
    }

    if (isalpha(**src)) {  // Identifier or Keyword
        int i = 0;
        while (isalnum(**src) || **src == '_') {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';

        if (is_keyword(token.value)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
    } else if (isdigit(**src)) {  // Integer literal
        int i = 0;
        while (isdigit(**src)) {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
    } else {
        token.type = TOKEN_UNKNOWN;  // Unknown token
    }

    return token;
}
