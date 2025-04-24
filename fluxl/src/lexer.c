#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"

typedef struct {
    const char *source;
    size_t position;
} Lexer;

Lexer* Lexer_New(const char *source) {
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    if (!lexer) {
        fprintf(stderr, "Memory allocation failed for Lexer\n");
        return NULL;
    }
    lexer->source = source;
    lexer->position = 0;
    return lexer;
}

void Lexer_Free(Lexer *lexer) {
    if (lexer) {
        free(lexer);
    }
}

Token* CreateToken(TokenType type, const char *value) {
    Token *token = (Token *)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation failed for Token\n");
        return NULL;
    }
    token->type = type;
    token->value = strdup(value); // Duplicate the string
    return token;
}

void FreeToken(Token *token) {
    if (token) {
        free(token->value); // Free the string
        free(token);        // Free the token itself
    }
}

void FreeTokenList(Token **tokens, size_t count) {
    for (size_t i = 0; i < count; i++) {
        FreeToken(tokens[i]);
    }
    free(tokens); // Free the array of tokens
}

void PrintToken(Token *token) {
    if (!token) return;
    const char *type_str;
    switch (token->type) {
        case TOKEN_IDENTIFIER: type_str = "IDENTIFIER"; break;
        case TOKEN_NUMBER: type_str = "NUMBER"; break;
        case TOKEN_STRING: type_str = "STRING"; break;
        case TOKEN_OPERATOR: type_str = "OPERATOR"; break;
        case TOKEN_KEYWORD: type_str = "KEYWORD"; break;
        case TOKEN_EOF: type_str = "EOF"; break;
        case TOKEN_UNKNOWN: type_str = "UNKNOWN"; break;
        default: type_str = "INVALID"; break;
    }
    printf("Token(Type: %s, Value: %s)\n", type_str, token->value);
}

Token** Lexer_Tokenize(Lexer *lexer, size_t *token_count) {
    size_t capacity = 10;
    Token **tokens = (Token **)malloc(capacity * sizeof(Token *));
    if (!tokens) {
        fprintf(stderr, "Memory allocation failed for token list\n");
        return NULL;
    }
    *token_count = 0;

    const char *ptr = lexer->source;
    while (*ptr) {
        // Skip whitespace
        if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r') {
            ptr++;
            continue;
        }

        // Skip single-line comments
        if (strncmp(ptr, "//", 2) == 0) {
            while (*ptr && *ptr != '\n') ptr++; // Skip until the end of the line
            continue;
        }

        // Handle keywords and identifiers
        if (isalpha(*ptr)) {
            const char *start = ptr;
            while (isalnum(*ptr)) ptr++;
            size_t length = ptr - start;
            char *value = strndup(start, length);

            // Check if the value is a keyword
            if (strcmp(value, "mod") == 0 || strcmp(value, "int") == 0 || strcmp(value, "return") == 0) {
                tokens[*token_count] = CreateToken(TOKEN_KEYWORD, value);
            } else {
                tokens[*token_count] = CreateToken(TOKEN_IDENTIFIER, value);
            }
            free(value);
            (*token_count)++;
            continue;
        }

        // Handle punctuation
        if (*ptr == '{' || *ptr == '}' || *ptr == '(' || *ptr == ')' || *ptr == ';') {
            char value[2] = {*ptr, '\0'};
            tokens[*token_count] = CreateToken(TOKEN_OPERATOR, value);
            (*token_count)++;
            ptr++;
            continue;
        }

        // Handle "::" operator
        if (strncmp(ptr, "::", 2) == 0) {
            tokens[*token_count] = CreateToken(TOKEN_OPERATOR, "::");
            (*token_count)++;
            ptr += 2;
            continue;
        }

        // Handle "++" operator
        if (strncmp(ptr, "++", 2) == 0) {
            tokens[*token_count] = CreateToken(TOKEN_OPERATOR, "++");
            (*token_count)++;
            ptr += 2;
            continue;
        }

        // Handle numbers
        if (isdigit(*ptr)) {
            const char *start = ptr;
            while (isdigit(*ptr)) ptr++;
            size_t length = ptr - start;
            tokens[*token_count] = CreateToken(TOKEN_NUMBER, strndup(start, length));
            (*token_count)++;
            continue;
        }

        // Handle string literals
        if (*ptr == '"') {
            const char *start = ++ptr; // Skip the opening quote
            while (*ptr && *ptr != '"') ptr++;
            if (*ptr == '"') {
                size_t length = ptr - start;
                char *value = strndup(start, length);
                tokens[*token_count] = CreateToken(TOKEN_STRING, value);
                free(value);
                (*token_count)++;
                ptr++; // Skip the closing quote
            } else {
                fprintf(stderr, "Error: Unterminated string literal\n");
            }
            continue;
        }

        // Handle unknown characters
        char value[2] = {*ptr, '\0'};
        tokens[*token_count] = CreateToken(TOKEN_UNKNOWN, value);
        (*token_count)++;
        ptr++;
    }

    // Add EOF token
    tokens[*token_count] = CreateToken(TOKEN_EOF, "");
    (*token_count)++;

    return tokens;
}

char* READF(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed for file buffer\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0'; // Null-terminate the string
    fclose(file);
    return buffer;
}

int has_flx_extension(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return ext && strcmp(ext, ".flx") == 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.flx>\n", argv[0]);
        return 1;
    }

    if (!has_flx_extension(argv[1])) {
        fprintf(stderr, "Error: Only .flx files are supported.\n");
        return 1;
    }

    char *source = READF(argv[1]);
    if (!source) {
        fprintf(stderr, "Error: Could not read file %s\n", argv[1]);
        return 1;
    }

    Lexer *lexer = Lexer_New(source);
    size_t token_count = 0;
    Token **tokens = Lexer_Tokenize(lexer, &token_count);

    if (token_count == 0) {
        fprintf(stderr, "No tokens found in the file.\n");
    } else {
        printf("Tokens:\n");
        for (size_t i = 0; i < token_count; i++) {
            PrintToken(tokens[i]);
        }

        // Parse the tokens
        Parser *parser = Parser_New(tokens, token_count);
        AstNode *ast = Parser_Parse(parser);

        if (ast) {
            printf("Parsed AST successfully!\n");
            // Print or process the AST here
            FreeAstNode(ast); // Free the AST
        } else {
            fprintf(stderr, "Failed to parse the input.\n");
        }

        Parser_Free(parser);
    }

    FreeTokenList(tokens, token_count);
    Lexer_Free(lexer);
    free(source);

    return 0;
}
