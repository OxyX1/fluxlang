#include "interpreter.hpp"
#include <iostream>

Interpreter::Interpreter(ASTNode* root) : root(root) {}

void Interpreter::execute() {
    executeProgram(root);
}

void Interpreter::executeProgram(ASTNode* node) {
    ProgramNode* program = static_cast<ProgramNode*>(node);
    for (auto& stmt : program->statements) {
        if (stmt->type == NodeType::VariableDeclaration) {
            executeVariableDeclaration(static_cast<VariableDeclarationNode*>(stmt));
        } else if (stmt->type == NodeType::Assignment) {
            executeAssignment(static_cast<AssignmentNode*>(stmt));
        }
    }
}

void Interpreter::executeVariableDeclaration(VariableDeclarationNode* node) {
    variables[node->name] = node->value;
    std::cout << "Variable " << node->name << " declared with value " << node->value << std::endl;
}

void Interpreter::executeAssignment(AssignmentNode* node) {
    variables[node->varName] = node->value;
    std::cout << "Variable " << node->varName << " assigned value " << node->value << std::endl;
}
