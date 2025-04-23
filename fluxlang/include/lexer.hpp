#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

class Token;  // Forward declaration of Token class

class Lexer {
public:
    Lexer(const std::string& source);
    const std::vector<Token>& getTokens() const;

private:
    std::string source;
    std::vector<Token> tokens;
    void addToken(int tokenType, const std::string& lexeme);  // Replace int with TokenType if defined
};

#endif