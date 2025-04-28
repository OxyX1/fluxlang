#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>

// Function to handle code generation and compilation
int generateWebAssembly(const char* sourceFile, const char* outputFile);

// Helper functions for file cleanup
void cleanupTempFiles(const char* tempFiles[], int numFiles);

#endif
