#include "../include/lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = { "if", "else", "while", "mod", "return", NULL };

int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Token get_next_token(const char **src) {
    Token token = {TOKEN_INVALID, ""};

    // Skip whitespace
    while (isspace(**src)) {
        (*src)++;
    }

    if (**src == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }

    // Handle identifiers and keywords
    if (isalpha(**src) || **src == '_') {
        int i = 0;
        while (isalnum(**src) || **src == '_') {
            if (i < MAX_TOKEN_LENGTH - 1)
                token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';

        if (is_keyword(token.value)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
    }
    // Handle numbers
    else if (isdigit(**src)) {
        int i = 0;
        while (isdigit(**src)) {
            if (i < MAX_TOKEN_LENGTH - 1)
                token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
    }
    // Handle string literals
    else if (**src == '"') {
        (*src)++; // Skip opening quote
        int i = 0;
        while (**src && **src != '"') {
            if (i < MAX_TOKEN_LENGTH - 1)
                token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        if (**src == '"') (*src)++; // Skip closing quote
        token.type = TOKEN_STRING;
    }
    // Handle operators and symbols
    else {
        char c = **src;
        token.value[0] = c;
        token.value[1] = '\0';
        (*src)++;

        switch (c) {
            case '+': 
                if (**src == '+') {
                    token.value[1] = '+';
                    token.value[2] = '\0';
                    (*src)++;
                    token.type = TOKEN_OPERATOR;
                } else {
                    token.type = TOKEN_OPERATOR;
                }
                break;
            case '>': case '<': case '=': case '!': case '*': case '/':
            case '(': case ')': case '{': case '}': case '[': case ']':
            case ';': case ',': case '.':
                token.type = TOKEN_SYMBOL;
                break;
            default:
                token.type = TOKEN_UNKNOWN;
                break;
        }
    }
    return token;
}
