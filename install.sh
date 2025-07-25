#!/bin/bash

# XMD Installation Script
# This script installs XMD (eXtended MarkDown) on your system

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
GITHUB_REPO="akaoio/xmd"
INSTALL_DIR="/usr/local/bin"
BINARY_NAME="xmd"

# Helper functions
print_step() {
    echo -e "${BLUE}==>${NC} $1"
}

print_success() {
    echo -e "${GREEN}✓${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
    exit 1
}

# Detect OS and architecture
detect_platform() {
    local os=$(uname -s | tr '[:upper:]' '[:lower:]')
    local arch=$(uname -m)
    
    case $os in
        linux)
            OS="linux"
            ;;
        darwin)
            OS="macos"
            ;;
        mingw*|cygwin*|msys*)
            OS="windows"
            ;;
        *)
            print_error "Unsupported operating system: $os"
            ;;
    esac
    
    case $arch in
        x86_64|amd64)
            ARCH="x64"
            ;;
        aarch64|arm64)
            ARCH="arm64"
            ;;
        armv7l)
            ARCH="arm"
            ;;
        *)
            print_error "Unsupported architecture: $arch"
            ;;
    esac
    
    PLATFORM="${OS}-${ARCH}"
    if [ "$OS" = "windows" ]; then
        BINARY_NAME="xmd.exe"
    fi
}

# Check if running as root when needed
check_permissions() {
    if [ "$EUID" -ne 0 ] && [ -w "$INSTALL_DIR" ] 2>/dev/null; then
        return 0
    elif [ "$EUID" -ne 0 ] && [ ! -w "$INSTALL_DIR" ] 2>/dev/null; then
        print_warning "Installation requires sudo privileges for $INSTALL_DIR"
        SUDO="sudo"
    fi
}

# Download and install XMD
install_xmd() {
    print_step "Installing XMD for $PLATFORM..."
    
    # Create temporary directory
    local tmp_dir=$(mktemp -d)
    cd "$tmp_dir"
    
    # Get latest release URL
    local latest_url="https://api.github.com/repos/$GITHUB_REPO/releases/latest"
    local download_url
    
    if command -v curl >/dev/null 2>&1; then
        download_url=$(curl -s "$latest_url" | grep "browser_download_url.*${PLATFORM}" | cut -d '"' -f 4)
    elif command -v wget >/dev/null 2>&1; then
        download_url=$(wget -qO- "$latest_url" | grep "browser_download_url.*${PLATFORM}" | cut -d '"' -f 4)
    else
        print_error "curl or wget is required to download XMD"
    fi
    
    if [ -z "$download_url" ]; then
        print_error "Could not find download URL for platform: $PLATFORM"
    fi
    
    print_step "Downloading from: $download_url"
    
    # Download binary
    if command -v curl >/dev/null 2>&1; then
        curl -L -o "$BINARY_NAME" "$download_url"
    else
        wget -O "$BINARY_NAME" "$download_url"
    fi
    
    # Make executable
    chmod +x "$BINARY_NAME"
    
    # Install to system
    print_step "Installing to $INSTALL_DIR..."
    $SUDO mv "$BINARY_NAME" "$INSTALL_DIR/"
    
    # Cleanup
    cd - >/dev/null
    rm -rf "$tmp_dir"
    
    print_success "XMD installed successfully!"
}

# Verify installation
verify_installation() {
    if command -v xmd >/dev/null 2>&1; then
        local version=$(xmd --version 2>/dev/null || echo "unknown")
        print_success "XMD is ready! Version: $version"
        
        cat << EOF

${GREEN}🎉 Installation complete!${NC}

${BLUE}Quick start:${NC}
  1. Create a markdown file with XMD syntax
  2. Run: ${YELLOW}xmd process your-file.md${NC}
  3. See the magic happen!

${BLUE}Resources:${NC}
  📖 Documentation: https://akaoio.github.io/xmd/
  🚀 Quick Start: https://akaoio.github.io/xmd/quick-start/
  💬 Community: https://discord.gg/xmd
  🐛 Issues: https://github.com/$GITHUB_REPO/issues

${BLUE}Examples:${NC}
  xmd process README.md              # Process single file
  xmd watch src/ -o dist/           # Watch directory
  xmd process template.md -v env=prod  # With variables

EOF
    else
        print_error "Installation failed - xmd command not found in PATH"
    fi
}

# Check for existing installation
check_existing() {
    if command -v xmd >/dev/null 2>&1; then
        local current_version=$(xmd --version 2>/dev/null | head -1 || echo "unknown")
        print_warning "XMD is already installed: $current_version"
        
        read -p "Do you want to reinstall/update? (y/N): " -r
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            print_step "Installation cancelled."
            exit 0
        fi
    fi
}

# Main installation flow
main() {
    echo -e "${BLUE}"
    cat << "EOF"
 __ __ __  __ ___  
|  \  |  |  | \ \ 
|     |  |  |  | |
 \____|__|__|_|_/ 

eXtended MarkDown
EOF
    echo -e "${NC}"
    
    print_step "Starting XMD installation..."
    
    # Pre-flight checks
    detect_platform
    check_existing
    check_permissions
    
    # Install
    install_xmd
    verify_installation
}

# Run main function
main "$@"