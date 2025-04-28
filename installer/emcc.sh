#!/bin/bash

# Detect the OS and install emcc accordingly
echo "Checking for Linux or macOS..."

# Check if it's a Linux system using apt package manager
if command -v apt &> /dev/null
then
    echo "Detected Linux (apt found). Installing Emscripten using apt..."
    sudo apt update
    sudo apt install -y emscripten
    echo "Emscripten installed successfully."
    exit 0
fi

# Check if it's macOS using brew package manager
if command -v brew &> /dev/null
then
    echo "Detected macOS (Homebrew found). Installing Emscripten using Homebrew..."
    brew install emscripten
    echo "Emscripten installed successfully."
    exit 0
fi

# If neither package manager is found
echo "Could not detect apt or brew. Please install Emscripten manually."
exit 1
