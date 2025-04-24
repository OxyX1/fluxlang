#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"
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
    if (!source) return 1;

    Lexer *lexer = Lexer_New(source);
    size_t token_count;
    Token **tokens = Lexer_Tokenize(lexer, &token_count);

    for (size_t i = 0; i < token_count; i++) {
        PrintToken(tokens[i]);
    }

    FreeTokenList(tokens, token_count);
    Lexer_Free(lexer);
    free(source);
    return 0;

    for (size_t i = 0; i < token_count; i++) {
        PrintToken(tokens[i]);
    }    
}
