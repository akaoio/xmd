#!/bin/bash

# DEVELOPER BUILD SCRIPT - ISOLATED ENVIRONMENT
echo "🔨 Developer Build Environment - ISOLATED"
echo "Build Directory: build-developer/"
echo "Assigned Files: parsers_consolidated.c, performance.c, systems_consolidated.c"

# Clean and recreate build directory
rm -rf build-developer
mkdir -p build-developer

# Configure with proper paths (from root directory)
echo "🔄 Configuring CMake..."
cmake -B build-developer -S . -DCMAKE_BUILD_TYPE=Debug

# Enter build directory
cd build-developer

# Check if Makefile was generated
if [ ! -f "Makefile" ]; then
    echo "❌ ERROR: Makefile not generated!"
    exit 1
fi

# Build with proper error handling
echo "🔨 Building..."
if make -j$(nproc); then
    echo "✅ Developer Build Complete - Check YOUR assigned files only!"
else
    echo "❌ Build failed - check errors above"
    exit 1
fi