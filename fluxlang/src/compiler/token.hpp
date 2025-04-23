#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    PLUS,
    MINUS,
    PRINT, // Add PRINT token type
    // Add more token types as needed
};

class Token {
public:
    Token(TokenType type, const std::string& lexeme);

    TokenType getType() const; // Accessor for type
    const std::string& getLexeme() const; // Accessor for lexeme

private:
    TokenType type;
    std::string lexeme;
};

#endif // TOKEN_HPP