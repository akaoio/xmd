#!/bin/bash
# XMD Build Optimization Script
# Quality + Infrastructure Lead: Tester
# Optimizes build performance and standardizes configuration

set -e

echo "=== XMD BUILD OPTIMIZATION SCRIPT ==="

# Configuration
BUILD_DIR="${1:-build-optimized}"
BUILD_TYPE="${2:-Release}"
PARALLEL_JOBS="${3:-$(nproc)}"

echo "Build directory: $BUILD_DIR"
echo "Build type: $BUILD_TYPE"
echo "Parallel jobs: $PARALLEL_JOBS"

# Clean previous build
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

# Create optimized build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring optimized build..."

# Optimized CMake configuration
cmake \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_C_FLAGS_RELEASE="-O3 -DNDEBUG -march=native" \
    -DCMAKE_C_FLAGS_DEBUG="-O0 -g -DDEBUG" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_VERBOSE_MAKEFILE=OFF \
    -S ..

echo "Building with $PARALLEL_JOBS parallel jobs..."
time make -j"$PARALLEL_JOBS" 2>&1 | tee build.log

# Analyze build results
echo "=== BUILD ANALYSIS ==="

# Count warnings
WARNING_COUNT=$(grep -c "warning:" build.log || true)
ERROR_COUNT=$(grep -c "error:" build.log || true)

echo "Warnings: $WARNING_COUNT"
echo "Errors: $ERROR_COUNT"

# Check binary size
if [ -f "xmd" ]; then
    BINARY_SIZE=$(stat -c%s "xmd")
    echo "Binary size: $BINARY_SIZE bytes ($(($BINARY_SIZE / 1024)) KB)"
else
    echo "❌ Binary not generated!"
    exit 1
fi

# Validate build success
if [ "$ERROR_COUNT" -eq 0 ]; then
    echo "✅ Build successful: 0 errors"
else
    echo "❌ Build failed: $ERROR_COUNT errors"
    exit 1
fi

# Warning threshold check
if [ "$WARNING_COUNT" -eq 0 ]; then
    echo "✅ Perfect build: 0 warnings"
elif [ "$WARNING_COUNT" -le 5 ]; then
    echo "⚠️  Acceptable warnings: $WARNING_COUNT (≤5)"
else
    echo "❌ Too many warnings: $WARNING_COUNT (>5)"
    echo "Warning details:"
    grep "warning:" build.log || true
    exit 1
fi

# Test basic functionality
echo "=== FUNCTIONALITY TEST ==="
echo 'print "Build optimization test successful!"' > test_build.xmd
./xmd process test_build.xmd

echo "=== BUILD OPTIMIZATION COMPLETE ==="
echo "Optimized build ready in: $BUILD_DIR"