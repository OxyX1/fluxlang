// fluxc.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

// Dummy codegen: replace with real codegen later
void generate_asm(ASTNode* ast, const char* out_filename) {
    FILE* out = fopen(out_filename, "w");
    fprintf(out,
        "global _start\n"
        "_start:\n"
        "    mov rax, 60\n"
        "    xor rdi, rdi\n"
        "    syscall\n"
    );
    fclose(out);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: fluxc <file.flx>\n");
        return 1;
    }

    // Read source file
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char* source = malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);

    // Compile pipeline
    init_lexer(source);
    ASTNode* ast = parse();

    // Debug print AST
    printf("AST: ");
    print_ast(ast);
    printf("\n");

    // Generate assembly
    generate_asm(ast, "output.s");

    // Assemble & Link
    system("as -o output.o output.s");
    system("ld -o output output.o");

    // Clean up
    free(source);
    free_ast(ast);
    return 0;
}
