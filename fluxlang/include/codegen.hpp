#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include <string>
#include <vector>

class ASTNode;  // Forward declaration of ASTNode class

class CodeGen {
public:
    CodeGen(const std::string& outputFile);
    void generateCode(const ASTNode& root);
    void finalize();

private:
    std::string outputFile;
    std::vector<std::string> assemblyInstructions;

    void emit(const std::string& instruction);
    void writeToFile();
};

#endif