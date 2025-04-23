// filepath: /fluxlang/fluxlang/include/parser.hpp
#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <memory>
#include "lexer.hpp"  // Include the Lexer header for token handling
#include "codegen.hpp" // Include the CodeGen header for assembly generation

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parse(); // Method to parse tokens into an AST

private:
    std::vector<Token> tokens; // Token stream
    size_t current; // Current position in the token stream

    // Parsing methods for different grammar rules
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseStatement();
    void consume(TokenType type, const std::string& errorMessage);
};

#endif