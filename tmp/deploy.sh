#!/bin/bash
# XMD Production Deployment Script
# Author: DevOps Team
# Date: 2025-07-31

set -e

echo "🚀 XMD Deployment Script v1.0"
echo "=============================="

# Configuration
INSTALL_PREFIX="${INSTALL_PREFIX:-/usr/local}"
BUILD_TYPE="${BUILD_TYPE:-Release}"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Functions
success() {
    echo -e "${GREEN}✅ $1${NC}"
}

error() {
    echo -e "${RED}❌ $1${NC}"
    exit 1
}

# Check prerequisites
echo "📋 Checking prerequisites..."
command -v cmake >/dev/null 2>&1 || error "cmake is required but not installed"
command -v make >/dev/null 2>&1 || error "make is required but not installed"
command -v gcc >/dev/null 2>&1 || command -v clang >/dev/null 2>&1 || error "C compiler is required"

# Clean build
echo "🧹 Cleaning previous build..."
rm -rf build

# Configure
echo "⚙️  Configuring build..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}
success "Configuration complete"

# Build
echo "🔨 Building XMD..."
cmake --build build -- -j$(nproc)
success "Build complete"

# Test
echo "🧪 Running basic tests..."
if ./build/xmd test/simple_var.xmd >/dev/null 2>&1; then
    success "Basic tests passed"
else
    error "Basic tests failed"
fi

# Install
if [ "$1" == "install" ]; then
    echo "📦 Installing XMD to ${INSTALL_PREFIX}..."
    sudo cmake --install build
    success "Installation complete"
    echo ""
    echo "XMD has been installed to: ${INSTALL_PREFIX}/bin/xmd"
    echo "Run 'xmd --version' to verify installation"
else
    echo ""
    echo "Build complete! Binary available at: build/xmd"
    echo "To install system-wide, run: $0 install"
fi

echo ""
echo "🎉 Deployment successful!"