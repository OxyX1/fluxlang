#!/bin/bash

# Exit on any error
set -e

echo "🔨 Building fluxc from sources..."

# Compiler output binary name
OUTPUT="fluxc"

# Source folder
SRC_DIR="fluxl"

# Find all .c files in the fluxl folder
SOURCES=$(find "$SRC_DIR" -name '*.c')

# Compile
gcc -o "$OUTPUT" $SOURCES

echo "✅ Build complete: ./$OUTPUT"
