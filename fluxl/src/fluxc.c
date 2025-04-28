#include "../include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

void run_lexer(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *source = (char *)malloc(size + 1);
    if (!source) {
        fprintf(stderr, "Memory allocation failed!\n");
        fclose(file);
        return;
    }

    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);

    const char *src = source;
    Token token;
    while ((token = get_next_token(&src)).type != TOKEN_EOF) {
        switch (token.type) {
            case TOKEN_IDENTIFIER:
                printf("Identifier: %s\n", token.value);
                break;
            case TOKEN_KEYWORD:
                printf("Keyword: %s\n", token.value);
                break;
            case TOKEN_NUMBER:
                printf("Number: %s\n", token.value);
                break;
            case TOKEN_STRING:
                printf("String: \"%s\"\n", token.value);
                break;
            case TOKEN_SYMBOL:
                printf("Symbol: %s\n", token.value);
                break;
            case TOKEN_OPERATOR:
                printf("Operator: %s\n", token.value);
                break;
            case TOKEN_UNKNOWN:
                printf("Unknown: %s\n", token.value);
                break;
            default:
                break;
        }
    }

    free(source);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    run_lexer(argv[1]);
    return 0;
}
