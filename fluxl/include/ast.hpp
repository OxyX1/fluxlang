#pragma once
#include <string>
#include <vector>

enum class NodeType {
    Program,
    VariableDeclaration,
    FunctionDeclaration,
    Assignment,
    Expression,
    IfStatement,
    BinaryExpression
};

class ASTNode {
public:
    NodeType type;
    virtual ~ASTNode() = default;
};

class VariableDeclarationNode : public ASTNode {
public:
    std::string type;
    std::string name;
    std::string value;

    VariableDeclarationNode(const std::string& t, const std::string& n, const std::string& v)
        : type(t), name(n), value(v) {
        type = NodeType::VariableDeclaration;
    }
};

class FunctionDeclarationNode : public ASTNode {
public:
    std::string returnType;
    std::string name;
    std::vector<ASTNode*> body;

    FunctionDeclarationNode(const std::string& rType, const std::string& n)
        : returnType(rType), name(n) {
        type = NodeType::FunctionDeclaration;
    }
};

class AssignmentNode : public ASTNode {
public:
    std::string varName;
    std::string value;

    AssignmentNode(const std::string& var, const std::string& v)
        : varName(var), value(v) {
        type = NodeType::Assignment;
    }
};

class IfStatementNode : public ASTNode {
public:
    ASTNode* condition;
    std::vector<ASTNode*> body;

    IfStatementNode(ASTNode* cond)
        : condition(cond) {
        type = NodeType::IfStatement;
    }
};

class BinaryExpressionNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string op;

    BinaryExpressionNode(ASTNode* l, ASTNode* r, const std::string& o)
        : left(l), right(r), op(o) {
        type = NodeType::BinaryExpression;
    }
};

class ProgramNode : public ASTNode {
public:
    std::vector<ASTNode*> statements;

    ProgramNode() {
        type = NodeType::Program;
    }
};
