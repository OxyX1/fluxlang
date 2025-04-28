#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/codegen.h"

// Function to handle code generation and compilation
int generateWebAssembly(const char* sourceFile, const char* outputFile) {
    char command[512];

    // Step 1: Generate WebAssembly object file (.o) from the source code
    // Here we use emcc to compile the source code into a .o file
    snprintf(command, sizeof(command), "emcc -O3 -c %s -o temp.o", sourceFile);
    if (system(command) != 0) {
        fprintf(stderr, "Error compiling the source file into .o\n");
        return -1;
    }

    // Step 2: Link the .o file into a WebAssembly binary (.wasm)
    snprintf(command, sizeof(command), "emcc temp.o -o %s", outputFile);
    if (system(command) != 0) {
        fprintf(stderr, "Error linking the object file into WebAssembly\n");
        return -1;
    }

    // Step 3: Clean up temporary .o files
    cleanupTempFiles((const char*[]){"temp.o"}, 1);

    return 0;
}

// Function to clean up temporary files
void cleanupTempFiles(const char* tempFiles[], int numFiles) {
    for (int i = 0; i < numFiles; i++) {
        if (remove(tempFiles[i]) != 0) {
            perror("Error deleting temporary file");
        }
    }
}
