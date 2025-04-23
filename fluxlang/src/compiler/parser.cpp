// filepath: /fluxlang/fluxlang/src/compiler/parser.cpp
#include "parser.hpp"
#include "lexer.hpp"
#include <stdexcept>

Parser::Parser(const std::string& source) {
    // Initialize and parse the source code
    parse();
}

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

void Parser::parse() {
    ast.push_back(*program());
}

ASTNode* Parser::program() {
    std::vector<ASTNode*> statements;
    while (!isAtEnd()) {
        statements.push_back(statement());
    }
    return new ASTNode{ASTNodeType::FunctionCall, "program", 0, {}};
}

ASTNode* Parser::statement() {
    if (match(TokenType::PRINT)) {
        return printStatement();
    }
    throw std::runtime_error("Unexpected token: " + currentToken().getLexeme());
}

ASTNode* Parser::printStatement() {
    Token token = previous();
    ExpressionNode* expr = expression();
    return new ASTNode{ASTNodeType::FunctionCall, "print", 0, {}};
}

ExpressionNode* Parser::expression() {
    // Placeholder for expression parsing
    return nullptr;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return currentToken().getType() == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return current >= tokens.size();
}

Token Parser::currentToken() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}