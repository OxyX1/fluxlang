#include "../include/lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = { "if", "else", "while", "mod", NULL };

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

    if (isalpha(**src) || **src == '_') { // Identifiers and Keywords
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
    else if (isdigit(**src)) { // Numbers
        int i = 0;
        while (isdigit(**src)) {
            if (i < MAX_TOKEN_LENGTH - 1)
                token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
    }
    else if (**src == '"') { // String literals
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
    else { // Operators and Symbols
        char c = **src;

        if (c == '+' || c == '-') { // Handle ++ and --
            token.value[0] = c;
            if (*(*src + 1) == c) { // Check for ++ or --
                token.value[1] = c;
                token.value[2] = '\0';
                (*src) += 2;
            } else {
                token.value[1] = '\0';
                (*src)++;
            }
            token.type = TOKEN_OPERATOR;
        }
        else if (c == '*' || c == '/') { // Single-char operators
            token.value[0] = c;
            token.value[1] = '\0';
            (*src)++;
            token.type = TOKEN_OPERATOR;
        }
        else { // Symbols and others
            token.value[0] = c;
            token.value[1] = '\0';
            (*src)++;

            switch (c) {
                case '{': case '}':
                case '(': case ')':
                case '[': case ']':
                case ';': case '.':
                    token.type = TOKEN_SYMBOL;
                    break;
                case '=':
                    token.type = TOKEN_OPERATOR;
                    break;
                default:
                    token.type = TOKEN_UNKNOWN;
                    break;
            }
        }
    }

    return token;
}
