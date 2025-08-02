#!/bin/bash

# SYSTEMS ENGINEER BUILD SCRIPT - ISOLATED ENVIRONMENT  
echo "🔧 Systems Engineer Build Environment - ISOLATED"
echo "Build Directory: build-systems/"
echo "Assigned Files: utils_consolidated.c, lexer_consolidated.c, import_consolidated.c"

# Clean and recreate build directory
rm -rf build-systems
mkdir -p build-systems

# Configure with proper paths (from root directory)
echo "🔄 Configuring CMake..."
cmake -B build-systems -S . -DCMAKE_BUILD_TYPE=Debug

# Enter build directory
cd build-systems

# Check if Makefile was generated
if [ ! -f "Makefile" ]; then
    echo "❌ ERROR: Makefile not generated!"
    exit 1
fi

# Build with proper error handling
echo "🔨 Building..."
if make -j$(nproc); then
    echo "✅ Systems Engineer Build Complete - Monitor YOUR assigned files only!"
else
    echo "❌ Build failed - check errors above"
    exit 1
fi