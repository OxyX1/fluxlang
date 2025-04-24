#!/bin/bash

# Set the name of the output binary
OUTPUT="fluxc"

# Find all .c files in the current directory
SRC_FILES=$(find . -name "*.c")

# Compile with GCC and show errors if any
echo "Compiling $OUTPUT..."
gcc -Wall -Wextra -o $OUTPUT $SRC_FILES

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "✅ Build successful: ./$OUTPUT"
else
    echo "❌ Build failed"
fi
