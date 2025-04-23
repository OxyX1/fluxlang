// filepath: /fluxlang/fluxlang/src/runtime/flux_runtime.cpp
#include "flux_runtime.hpp"
#include <iostream>

namespace FluxRuntime {

void print(const std::string& message) {
    std::cout << message << std::endl;
}

void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    exit(EXIT_FAILURE);
}

// Additional runtime functions can be added here

} // namespace FluxRuntime