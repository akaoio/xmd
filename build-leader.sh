#!/bin/bash

# GENESIS LEADER BUILD SCRIPT - ISOLATED ENVIRONMENT
echo "👑 Genesis Leader Build Environment - ISOLATED" 
echo "Build Directory: build-leader/"
echo "Assigned Files: bindings_consolidated.c, native_xmd_consolidated.c, parsers_consolidated.c"

# Clean and recreate build directory
rm -rf build-leader
mkdir -p build-leader

# Configure with proper paths (from root directory)
echo "🔄 Configuring CMake..."
cmake -B build-leader -S . -DCMAKE_BUILD_TYPE=Debug

# Enter build directory
cd build-leader

# Check if Makefile was generated
if [ ! -f "Makefile" ]; then
    echo "❌ ERROR: Makefile not generated!"
    exit 1
fi

# Build with proper error handling
echo "🔨 Building..."
if make -j$(nproc); then
    echo "✅ Genesis Leader Build Complete - Supervise all team progress!"
else
    echo "❌ Build failed - check errors above"
    exit 1
fi