#!/bin/bash
# XMD Production Deployment Script
# Author: XMD Development Team
# Date: August 3, 2025

set -e

echo "🚀 XMD Production Deployment Script"
echo "=================================="

# Configuration
BUILD_DIR="build-developer"
TARGET_EXECUTABLE="xmd"
BACKUP_DIR="backup"

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "❌ Build directory '$BUILD_DIR' not found. Building project..."
    mkdir -p "$BUILD_DIR"
    cmake -B "$BUILD_DIR" -S .
    cd "$BUILD_DIR" && make -j4
    cd ..
fi

# Check if executable exists in build directory
if [ ! -f "$BUILD_DIR/$TARGET_EXECUTABLE" ]; then
    echo "❌ Executable '$BUILD_DIR/$TARGET_EXECUTABLE' not found. Building project..."
    cd "$BUILD_DIR" && make -j4
    cd ..
fi

# Backup existing executable if it exists
if [ -f "./$TARGET_EXECUTABLE" ]; then
    echo "📦 Backing up existing executable..."
    mkdir -p "$BACKUP_DIR"
    cp "./$TARGET_EXECUTABLE" "$BACKUP_DIR/${TARGET_EXECUTABLE}.$(date +%Y%m%d_%H%M%S).bak"
fi

# Deploy new executable
echo "🔧 Deploying executable to root directory..."
cp "$BUILD_DIR/$TARGET_EXECUTABLE" "./$TARGET_EXECUTABLE"

# Make executable
chmod +x "./$TARGET_EXECUTABLE"

# Validate deployment
echo "✅ Validating deployment..."
if [ -x "./$TARGET_EXECUTABLE" ]; then
    echo "📊 Version check:"
    "./$TARGET_EXECUTABLE" --version
    echo ""
    echo "🎯 Help check:"
    "./$TARGET_EXECUTABLE" --help
    echo ""
    echo "🏆 Deployment successful! XMD is ready for production."
    echo "💡 Usage: ./xmd process your_file.xmd"
else
    echo "❌ Deployment failed! Executable is not executable."
    exit 1
fi