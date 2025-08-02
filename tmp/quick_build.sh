#!/bin/bash
# Quick build script for XMD

echo "Building XMD..."

# Create build directory
mkdir -p build_manual

# Compile all source files
gcc -c src/**/*.c -I./include -I./src -o build_manual/xmd.o 2>&1 | head -20

# Show what happened
echo "Build attempt complete. Check build_manual directory."
ls -la build_manual/