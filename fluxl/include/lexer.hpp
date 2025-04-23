// lexer.hpp
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

enum class TokenType {
    Identifier, Keyword, Number, String,
    Assign, Plus, Minus, Star, Slash, Equal, ColonColon,
    LParen, RParen, LBrace, RBrace, AngleL, AngleR, Semicolon, Comma,
    ModuleImport, Comment, CastType,
    EndOfFile, Invalid
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string src;
    size_t pos = 0;
    int line = 1;

    std::unordered_map<std::string, TokenType> keywords;

    char peek(int offset = 0) const;
    char advance();
    void skipWhitespace();
    void skipComment();
    Token makeToken(TokenType type, const std::string& value);
};
