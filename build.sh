#!/usr/bin/bash
rm -rf build
mkdir build
cd build
cmake ..
make -j4
cd ..
echo "✅ Build complete! Binary available at build/xmd"
