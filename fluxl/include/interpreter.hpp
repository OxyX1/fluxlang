#pragma once
#include "ast.hpp"
#include <unordered_map>

class Interpreter {
public:
    explicit Interpreter(ASTNode* root);
    void execute();

private:
    ASTNode* root;
    std::unordered_map<std::string, std::string> variables;

    void executeProgram(ASTNode* node);
    void executeVariableDeclaration(VariableDeclarationNode* node);
    void executeAssignment(AssignmentNode* node);
};
