// filepath: /fluxlang/fluxlang/src/compiler/codegen.cpp
#include "codegen.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include <fstream>
#include <iostream>

class CodeGen {
public:
    CodeGen(const Parser& parser) : parser(parser) {}

    void generateAssembly(const std::string& outputFile) {
        std::ofstream outFile(outputFile);
        if (!outFile) {
            std::cerr << "Error: Could not open output file " << outputFile << std::endl;
            return;
        }

        outFile << "; Assembly code generated from Flux\n";
        outFile << ".section .text\n";
        outFile << ".globl _start\n";
        outFile << "_start:\n";

        // Generate assembly code from the AST
        for (const auto& node : parser.getAST()) {
            generateNode(node, outFile);
        }

        outFile << "    mov $1, %rax\n"; // syscall: exit
        outFile << "    xor %rdi, %rdi\n"; // status: 0
        outFile << "    syscall\n";

        outFile.close();
    }

private:
    const Parser& parser;

    void generateNode(const ASTNode& node, std::ofstream& outFile) {
        switch (node.type) {
            case ASTNodeType::FunctionCall:
                outFile << "    call " << node.functionName << "\n";
                break;
            case ASTNodeType::IntegerLiteral:
                outFile << "    mov $" << node.value << ", %rax\n";
                break;
            default:
                break;
        }
    }
};