#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/codegen.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./fluxc <file.flx>\n");
        return 1;
    }

    // Read the source code
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    char input[MAX_LENGTH];
    while (fgets(input, MAX_LENGTH, file) != NULL) {
        lexicalAnalyzer(input);
    }

    fclose(file);

    // Generate WebAssembly from source code
    if (generateWebAssembly(argv[1], "output.wasm") != 0) {
        printf("Error generating WebAssembly output\n");
        return 1;
    }

    printf("Compilation to WebAssembly completed successfully!\n");

    return 0;
}
