#include "parser.hpp"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

Token Parser::currentToken() {
    if (pos < tokens.size()) {
        return tokens[pos];
    }
    return { TokenType::EndOfFile, "", 0 };  // Return EOF token at the end
}

void Parser::advance() {
    if (pos < tokens.size()) pos++;
}

void Parser::expect(TokenType type) {
    if (currentToken().type != type) {
        throw std::runtime_error("Unexpected token");
    }
}

ASTNode* Parser::parse() {
    return parseProgram();
}

ASTNode* Parser::parseProgram() {
    ProgramNode* program = new ProgramNode();

    while (currentToken().type != TokenType::EndOfFile) {
        if (currentToken().type == TokenType::Keyword) {
            if (currentToken().value == "int" || currentToken().value == "float" || currentToken().value == "string") {
                program->statements.push_back(parseVariableDeclaration());
            } else if (currentToken().value == "if") {
                program->statements.push_back(parseIfStatement());
            }
        }
        else if (currentToken().type == TokenType::Identifier) {
            program->statements.push_back(parseAssignment());
        }
        advance();
    }

    return program;
}

ASTNode* Parser::parseVariableDeclaration() {
    std::string type = currentToken().value;
    advance();
    
    expect(TokenType::Identifier);
    std::string name = currentToken().value;
    advance();
    
    expect(TokenType::Assign);
    advance();

    std::string value = currentToken().value;
    advance();
    
    return new VariableDeclarationNode(type, name, value);
}

ASTNode* Parser::parseFunctionDeclaration() {
    // Example: `int main() { ... }`
    std::string returnType = currentToken().value;
    advance();

    expect(TokenType::Identifier);
    std::string name = currentToken().value;
    advance();
    
    expect(TokenType::LParen);
    advance();
    
    expect(TokenType::RParen);
    advance();

    expect(TokenType::LBrace);
    advance();

    FunctionDeclarationNode* function = new FunctionDeclarationNode(returnType, name);
    while (currentToken().type != TokenType::RBrace) {
        function->body.push_back(parseVariableDeclaration());
    }
    advance();

    return function;
}

ASTNode* Parser::parseAssignment() {
    std::string varName = currentToken().value;
    advance();

    expect(TokenType::Assign);
    advance();

    std::string value = currentToken().value;
    advance();

    return new AssignmentNode(varName, value);
}

ASTNode* Parser::parseIfStatement() {
    expect(TokenType::LParen);
    advance();

    ASTNode* condition = parseExpression();

    expect(TokenType::RParen);
    advance();

    expect(TokenType::LBrace);
    advance();

    IfStatementNode* ifStmt = new IfStatementNode(condition);
    while (currentToken().type != TokenType::RBrace) {
        ifStmt->body.push_back(parseAssignment());
    }
    advance();

    return ifStmt;
}

ASTNode* Parser::parseExpression() {
    // For simplicity, we handle only binary expressions for now: `a + b`
    ASTNode* left = new VariableDeclarationNode("int", "a", "0");  // Placeholder
    advance();
    
    std::string op = currentToken().value;
    advance();

    ASTNode* right = new VariableDeclarationNode("int", "b", "0");  // Placeholder
    advance();
    
    return new BinaryExpressionNode(left, right, op);
}
