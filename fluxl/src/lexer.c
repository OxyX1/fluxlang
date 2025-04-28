#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../include/lexer.h"

#define MAX_LENGTH 100

// Token type names
const char *tokenTypeNames[] = {
    "Keyword",      // 0
    "Identifier",   // 1
    "Operator",     // 2
    "Integer",      // 3
    "Unidentified"  // 4
};

// Function to check if the character is a delimiter (space, operator, parentheses, etc.)
bool isDelimiter(char chr) {
    return (chr == ' ' || chr == '+' || chr == '-'
            || chr == '*' || chr == '/' || chr == ','
            || chr == ';' || chr == '%' || chr == '>'
            || chr == '<' || chr == '=' || chr == '('
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}');
}

// Function to check if the character is an operator (+, -, *, etc.)
bool isOperator(char chr) {
    return (chr == '+' || chr == '-' || chr == '*'
            || chr == '/' || chr == '>' || chr == '<'
            || chr == '=');
}

// Function to check if a string is a valid identifier (not starting with a digit)
bool isValidIdentifier(char* str) {
    return (str[0] != '0' && str[0] != '1' && str[0] != '2'
            && str[0] != '3' && str[0] != '4'
            && str[0] != '5' && str[0] != '6'
            && str[0] != '7' && str[0] != '8'
            && str[0] != '9' && !isDelimiter(str[0]));
}

// Function to check if a string is a keyword (e.g., int, for, return)
bool isKeyword(char* str) {
    const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a string is an integer
bool isInteger(char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    int i = 0;
    while (isdigit(str[i])) {
        i++;
    }
    return str[i] == '\0';
}

// Function to extract a substring from a given string
char* getSubstring(char* str, int start, int end) {
    int length = strlen(str);
    int subLength = end - start + 1;
    char* subStr = (char*)malloc((subLength + 1) * sizeof(char));
    strncpy(subStr, str + start, subLength);
    subStr[subLength] = '\0';
    return subStr;
}

// Lexical analyzer function to process the input string
void lexicalAnalyzer(char* input) {
    int left = 0, right = 0;
    int len = strlen(input);

    while (right <= len && left <= right) {
        if (!isDelimiter(input[right])) {
            right++;
        }

        if (isDelimiter(input[right]) && left == right) {
            if (isOperator(input[right])) {
                printf("Token: %s, Value: %c\n", tokenTypeNames[2], input[right]);
            }
            right++;
            left = right;
        } else if (isDelimiter(input[right]) && left != right
                   || (right == len && left != right)) {
            char* subStr = getSubstring(input, left, right - 1);

            if (isKeyword(subStr)) {
                printf("Token: %s, Value: %s\n", tokenTypeNames[0], subStr);
            } else if (isInteger(subStr)) {
                printf("Token: %s, Value: %s\n", tokenTypeNames[3], subStr);
            } else if (isValidIdentifier(subStr) && !isDelimiter(input[right - 1])) {
                printf("Token: %s, Value: %s\n", tokenTypeNames[1], subStr);
            } else {
                printf("Token: %s, Value: %s\n", tokenTypeNames[4], subStr);
            }

            free(subStr);
            left = right;
        }
    }
}
