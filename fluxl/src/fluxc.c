#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *source = malloc(length + 1);
    fread(source, 1, length, file);
    fclose(file);

    source[length] = '\0';

    // Initialize parser
    Parser parser;
    init_parser(&parser, source);

    // Parse and generate AST
    ASTNode *root = parse(&parser);

    // Print AST
    print_ast(root, 0);

    // Free resources
    free_ast(root);
    free(source);

    return 0;
}
