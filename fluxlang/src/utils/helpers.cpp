// filepath: /fluxlang/fluxlang/src/utils/helpers.cpp
#include "helpers.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace flux {

void printError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

} // namespace flux