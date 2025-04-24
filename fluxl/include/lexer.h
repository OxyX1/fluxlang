#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token Types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
} TokenType;

// Token Structure
typedef struct {
    TokenType type;
    char *value;
} Token;

// Function to create a new token
Token* CreateToken(TokenType type, const char *value);

// Function to free a token
void FreeToken(Token *token);

// Function to print a token
void PrintToken(Token *token);

// Function to free a list of tokens
void FreeTokenList(Token **tokens, size_t count);

// Function to tokenize input
Token **Tokenize(const char *input, size_t *token_count);

// Function to read a file into a string
char* READF(const char* filename);

// Function to check if the file has a .flx extension
int has_flx_extension(const char *filename);

#endif // LEXER_H

