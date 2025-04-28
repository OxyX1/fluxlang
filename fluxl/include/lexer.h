#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#define MAX_LENGTH 100

// Function declarations
bool isDelimiter(char chr);
bool isOperator(char chr);
bool isValidIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
char* getSubstring(char* str, int start, int end);
void lexicalAnalyzer(char* input);

#endif
