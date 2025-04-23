#ifndef FLUX_RUNTIME_HPP
#define FLUX_RUNTIME_HPP

#include <string>
#include <vector>

// Function to initialize the Flux runtime environment
void initializeRuntime();

// Function to execute a Flux program
void executeProgram(const std::string& program);

// Function to handle runtime errors
void handleError(const std::string& errorMessage);

// Function to print output to the console
void printOutput(const std::string& output);

// Function to read input from the user
std::string readInput();

#endif // FLUX_RUNTIME_HPP