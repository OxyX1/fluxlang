// lexer.cpp
#include "lexer.hpp"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& input) : src(input) {
    keywords = {
        {"mod", TokenType::ModuleImport},
        {"class", TokenType::Keyword},
        {"public", TokenType::Keyword},
        {"int", TokenType::Keyword},
        {"float", TokenType::Keyword},
        {"string", TokenType::Keyword},
        {"if", TokenType::Keyword},
        {"return", TokenType::Keyword}
    };
}

char Lexer::peek(int offset) const {
    return (pos + offset < src.length()) ? src[pos + offset] : '\0';
}

char Lexer::advance() {
    return src[pos++];
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) {
        if (peek() == '\n') line++;
        advance();
    }
}

void Lexer::skipComment() {
    if (peek() == '/' && peek(1) == '/') {
        while (peek() != '\n' && peek() != '\0') advance();
    }
}

Token Lexer::makeToken(TokenType type, const std::string& value) {
    return { type, value, line };
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (pos < src.length()) {
        skipWhitespace();
        skipComment();
        skipWhitespace();

        char current = peek();

        if (std::isalpha(current) || current == '_') {
            std::string ident;
            while (std::isalnum(peek()) || peek() == '_') {
                ident += advance();
            }

            TokenType type = keywords.count(ident) ? keywords[ident] : TokenType::Identifier;
            tokens.push_back(makeToken(type, ident));
            continue;
        }

        if (std::isdigit(current)) {
            std::string number;
            while (std::isdigit(peek())) number += advance();
            tokens.push_back(makeToken(TokenType::Number, number));
            continue;
        }

        if (current == '"') {
            advance(); // Skip opening quote
            std::string str;
            while (peek() != '"' && peek() != '\0') {
                str += advance();
            }
            advance(); // Skip closing quote
            tokens.push_back(makeToken(TokenType::String, str));
            continue;
        }

        switch (current) {
            case '=':
                if (peek(1) == '=') { advance(); advance(); tokens.push_back(makeToken(TokenType::Equal, "==")); }
                else { advance(); tokens.push_back(makeToken(TokenType::Assign, "=")); }
                break;
            case '+': advance(); tokens.push_back(makeToken(TokenType::Plus, "+")); break;
            case '-': advance(); tokens.push_back(makeToken(TokenType::Minus, "-")); break;
            case '*': advance(); tokens.push_back(makeToken(TokenType::Star, "*")); break;
            case '/':
                if (peek(1) == '/') skipComment();
                else { advance(); tokens.push_back(makeToken(TokenType::Slash, "/")); }
                break;
            case ':':
                if (peek(1) == ':') { advance(); advance(); tokens.push_back(makeToken(TokenType::ColonColon, "::")); }
                break;
            case '<': advance(); tokens.push_back(makeToken(TokenType::AngleL, "<")); break;
            case '>': advance(); tokens.push_back(makeToken(TokenType::AngleR, ">")); break;
            case ';': advance(); tokens.push_back(makeToken(TokenType::Semicolon, ";")); break;
            case ',': advance(); tokens.push_back(makeToken(TokenType::Comma, ",")); break;
            case '(': advance(); tokens.push_back(makeToken(TokenType::LParen, "(")); break;
            case ')': advance(); tokens.push_back(makeToken(TokenType::RParen, ")")); break;
            case '{': advance(); tokens.push_back(makeToken(TokenType::LBrace, "{")); break;
            case '}': advance(); tokens.push_back(makeToken(TokenType::RBrace, "}")); break;
            case '\0': tokens.push_back(makeToken(TokenType::EndOfFile, "")); break;
            default:
                std::cerr << "Unexpected character: '" << current << "' on line " << line << "\n";
                advance();
                break;
        }
    }

    tokens.push_back(makeToken(TokenType::EndOfFile, ""));
    return tokens;
}
