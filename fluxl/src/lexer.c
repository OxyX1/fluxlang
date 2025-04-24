// lexer.c
#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static const char* src;
static size_t pos;

void init_lexer(const char* input) {
    src = input;
    pos = 0;
}

static char peek() {
    return src[pos];
}

static char advance() {
    return src[pos++];
}

static Token make_token(TokenType type, const char* start, size_t len) {
    Token tok;
    tok.type = type;
    tok.text = strndup(start, len);
    return tok;
}

Token next_token() {
    while (isspace(peek())) advance();

    char c = peek();

    if (c == '\0') return make_token(TOKEN_EOF, "", 0);
    if (c == '+') { advance(); return make_token(TOKEN_PLUS, "+", 1); }
    if (c == '=') { advance(); return make_token(TOKEN_ASSIGN, "=", 1); }
    if (c == ';') { advance(); return make_token(TOKEN_SEMICOLON, ";", 1); }

    if (isalpha(c)) {
        const char* start = &src[pos];
        while (isalnum(peek())) advance();
        return make_token(TOKEN_IDENTIFIER, start, &src[pos] - start);
    }

    if (isdigit(c)) {
        const char* start = &src[pos];
        while (isdigit(peek())) advance();
        return make_token(TOKEN_NUMBER, start, &src[pos] - start);
    }

    return make_token(TOKEN_EOF, "", 0); // fallback
}

void free_token(Token tok) {
    free(tok.text);
}
