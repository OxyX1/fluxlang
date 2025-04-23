#pragma once
#include "lexer.hpp"
#include "ast.hpp"
#include <vector>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    ASTNode* parse();
    
private:
    std::vector<Token> tokens;
    size_t pos = 0;
    
    Token currentToken();
    void advance();
    
    ASTNode* parseProgram();
    ASTNode* parseVariableDeclaration();
    ASTNode* parseFunctionDeclaration();
    ASTNode* parseAssignment();
    ASTNode* parseExpression();
    ASTNode* parseIfStatement();
    
    void expect(TokenType type);
};
