#!/bin/bash

echo "Installing XMD development dependencies..."

# Update package list
sudo apt update

# Install JSON-C development library
echo "Installing json-c library..."
sudo apt install -y libjson-c-dev

# Install libyaml development library
echo "Installing libyaml library..."
sudo apt install -y libyaml-dev

# Install build essentials if not already present
echo "Installing build essentials..."
sudo apt install -y build-essential cmake pkg-config

# Math library is usually built-in, no need to install separately
echo "Math library (libm) is typically available by default"

echo "✅ All dependencies installed!"
echo "You can now run 'cd build && cmake .. && make' to rebuild with full library support."