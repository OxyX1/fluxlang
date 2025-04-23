#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "token.hpp"
#include <vector>
#include <string>

class Parser {
public:
    Parser(const std::string& source); // Existing constructor
    Parser(const std::vector<Token>& tokens); // Add this constructor

    const std::vector<ASTNode>& getAST() const;

private:
    std::vector<Token> tokens;
    size_t current;
    std::vector<ASTNode> ast;

    void parse();
    ASTNode* program();
    ASTNode* statement();
    ASTNode* printStatement();
    ExpressionNode* expression();

    bool match(TokenType type);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token currentToken();
    Token previous();
};

#endif // PARSER_HPP