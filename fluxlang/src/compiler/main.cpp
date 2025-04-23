#include <iostream>
#include <string>
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: fluxl <source_file.flx>" << std::endl;
        return 1;
    }

    std::string sourceFile = argv[1];
    
    // Step 1: Read the source file
    std::ifstream file(sourceFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << sourceFile << std::endl;
        return 1;
    }
    
    std::string sourceCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Step 2: Initialize the lexer
    Lexer lexer(sourceCode);
    const std::vector<Token>& tokens = lexer.getTokens();

    // Step 3: Initialize the parser
    Parser parser(tokens);
    ASTNode* ast = parser.parse();

    // Step 4: Initialize the code generator
    CodeGen codegen;
    codegen.generate(ast);

    // Step 5: Output the generated assembly code
    codegen.outputAssembly("output.asm");

    return 0;
}