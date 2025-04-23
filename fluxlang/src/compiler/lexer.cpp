// filepath: /fluxlang/fluxlang/src/compiler/lexer.cpp
#include "lexer.hpp"
#include "token.hpp"  // Adjusted the path to locate token.hpp
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source) {
    // Initialize tokens
    tokenize();
}

void Lexer::tokenize() {
    // Implementation of the tokenization process
    for (size_t i = 0; i < source.length(); ++i) {
        char current = source[i];

        if (isspace(current)) {
            continue;  // Skip whitespace
        }

        if (isalpha(current)) {
            // Handle identifiers and keywords
            std::string lexeme;
            while (isalnum(current) || current == '_') {
                lexeme += current;
                current = source[++i];
            }
            addToken(TokenType::IDENTIFIER, lexeme);
            --i;  // Adjust for the loop increment
        } else if (isdigit(current)) {
            // Handle numbers
            std::string lexeme;
            while (isdigit(current)) {
                lexeme += current;
                current = source[++i];
            }
            addToken(TokenType::NUMBER, lexeme);
            --i;  // Adjust for the loop increment
        } else {
            // Handle other token types (operators, punctuation, etc.)
            switch (current) {
                case '+':
                    addToken(TokenType::PLUS, std::string(1, current));
                    break;
                case '-':
                    addToken(TokenType::MINUS, std::string(1, current));
                    break;
                // Add more cases for other token types
                default:
                    // Handle unknown characters
                    break;
            }
        }
    }
}

const std::vector<Token>& Lexer::getTokens() const {
    return tokens;
}

void Lexer::addToken(int tokenType, const std::string& lexeme) {
    tokens.emplace_back(tokenType, lexeme);  // Assuming Token constructor takes type and lexeme
}