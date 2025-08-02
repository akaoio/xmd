#!/bin/bash
set -e
rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -j1
echo "✅ Build complete! Binary available at build/xmd"
