#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

enum class ASTNodeType {
    FunctionCall,
    IntegerLiteral,
    // Add more node types as needed
};

struct ASTNode {
    ASTNodeType type;
    std::string functionName; // For FunctionCall nodes
    int value;                // For IntegerLiteral nodes
    std::vector<ASTNode> children; // For nested structures
};

struct ExpressionNode {
    // Define the structure of an expression node
    std::string value;
};

#endif // AST_HPP