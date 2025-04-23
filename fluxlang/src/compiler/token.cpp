#include "token.hpp"

Token::Token(TokenType type, const std::string& lexeme)
    : type(type), lexeme(lexeme) {}

TokenType Token::getType() const {
    return type;
}

const std::string& Token::getLexeme() const {
    return lexeme;
}