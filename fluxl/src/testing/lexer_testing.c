#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    }

    FreeTokenList(tokens, token_count);
    Lexer_Free(lexer);
    free(source);

    return 0;
}
