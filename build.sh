#!/usr/bin/bash
rm -rf build
mkdir build
cd build
cmake ..
make
make test
# Binary stays in build/ folder - no need to move to root
cd ..
echo "✅ Build complete! Binary available at build/xmd"
