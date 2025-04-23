#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

// Function to read the file and return its contents as a string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    return content;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: fluxl <file.flx>" << std::endl;
        return 1;
    }

    // Step 1: Read the input .flx file
    std::string filename = argv[1];
    std::string code = readFile(filename);

    // Step 2: Tokenize the input code using the lexer
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    // Step 3: Parse the tokens to create an AST
    Parser parser(tokens);
    ASTNode* root = parser.parse();

    // Step 4: Execute the AST using the interpreter
    Interpreter interpreter(root);
    interpreter.execute();

    return 0;
}
