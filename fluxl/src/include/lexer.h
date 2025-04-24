#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token* CreateToken(TokenType type, const char *value) {
    Token *token = (Token *)malloc(sizeof(Token));
    if (!token) return NULL;
    token->type = type;
    token->value = strdup(value);
    return token;
}

void FreeToken(Token *token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

void PrintToken(Token *token) {
    if (token)
        printf("Token Type: %d, Value: %s\n", token->type, token->value);
}

void FreeTokenList(Token **tokens, size_t count) {
    for (size_t i = 0; i < count; i++) {
        FreeToken(tokens[i]);
    }
    free(tokens);
}

typedef struct {
    const char *src;
    const char *cur;
} Lexer;

Lexer* Lexer_New(const char *input) {
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    lexer->src = input;
    lexer->cur = input;
    return lexer;
}

void Lexer_Free(Lexer *lexer) {
    free(lexer);
}

Token* Lexer_NextToken(Lexer *lexer) {
    while (*lexer->cur) {
        if (isspace(*lexer->cur)) {
            lexer->cur++;
            continue;
        }

        if (isalpha(*lexer->cur)) {
            const char *start = lexer->cur;
            while (isalnum(*lexer->cur)) lexer->cur++;
            size_t len = lexer->cur - start;
            char *value = strndup(start, len);
            return CreateToken(TOKEN_IDENTIFIER, value);
        }

        // TODO: Add handling for more token types
        lexer->cur++;  // Skip unknowns for now
    }

    return CreateToken(TOKEN_EOF, "");
}

Token **Lexer_Tokenize(Lexer *lexer, size_t *token_count) {
    size_t capacity = 10;
    Token **tokens = malloc(capacity * sizeof(Token *));
    *token_count = 0;

    Token *token;
    while ((token = Lexer_NextToken(lexer))->type != TOKEN_EOF) {
        if (*token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token *));
        }
        tokens[(*token_count)++] = token;
    }

    tokens[(*token_count)++] = token;  // Add EOF token
    return tokens;
}

char* READF(const char* filename) {
    printf("Attempting to open file: %s\n", filename); // Debug print
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file"); // Print detailed error
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}

int has_flx_extension(const char *filename) {
    const char *dot = strrchr(filename, '.'); // Find last '.'
    return dot && strcmp(dot, ".flx") == 0;
}