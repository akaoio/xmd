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
BINARY_NAME="xmd"

# Detect install directory
if [ -n "$PREFIX" ]; then
    # Termux environment
    INSTALL_DIR="$PREFIX/bin"
elif [ -w "/usr/local/bin" ] 2>/dev/null; then
    INSTALL_DIR="/usr/local/bin"
elif [ -w "$HOME/.local/bin" ] 2>/dev/null || mkdir -p "$HOME/.local/bin" 2>/dev/null; then
    INSTALL_DIR="$HOME/.local/bin"
else
    INSTALL_DIR="/usr/local/bin"
fi

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
    if [ -w "$INSTALL_DIR" ] 2>/dev/null; then
        return 0
    elif [ -n "$PREFIX" ]; then
        # Termux environment - should be writable
        return 0
    elif [ "$EUID" -ne 0 ] && [ ! -w "$INSTALL_DIR" ] 2>/dev/null; then
        print_warning "Installation requires sudo privileges for $INSTALL_DIR"
        SUDO="sudo"
    fi
}

# Check build dependencies
check_dependencies() {
    local missing_deps=()
    
    if ! command -v git >/dev/null 2>&1; then
        missing_deps+=("git")
    fi
    
    if ! command -v cmake >/dev/null 2>&1; then
        missing_deps+=("cmake")
    fi
    
    if ! command -v gcc >/dev/null 2>&1 && ! command -v clang >/dev/null 2>&1; then
        missing_deps+=("gcc or clang")
    fi
    
    if ! command -v make >/dev/null 2>&1; then
        missing_deps+=("make")
    fi
    
    if [ ${#missing_deps[@]} -gt 0 ]; then
        print_error "Missing required dependencies: ${missing_deps[*]}
        
Install them first:
  Termux: pkg install git cmake clang make
  Ubuntu/Debian: apt install git cmake gcc make
  CentOS/RHEL: yum install git cmake gcc make
  macOS: brew install git cmake gcc make"
    fi
}

# Build and install XMD from source
install_xmd() {
    print_step "Building XMD from source for $PLATFORM..."
    
    # Create temporary directory
    local tmp_dir=$(mktemp -d)
    cd "$tmp_dir"
    
    # Clone repository
    print_step "Cloning XMD repository..."
    if command -v git >/dev/null 2>&1; then
        git clone --depth 1 "https://github.com/$GITHUB_REPO.git" xmd-source
    else
        print_error "git is required to clone the repository"
    fi
    
    cd xmd-source
    
    # Build
    print_step "Building XMD..."
    mkdir -p build
    cd build
    
    if ! cmake -DCMAKE_BUILD_TYPE=Release ..; then
        print_error "CMake configuration failed"
    fi
    
    if ! make -j$(nproc 2>/dev/null || echo 4); then
        print_error "Build failed"
    fi
    
    # Test the build
    print_step "Running tests..."
    if ! ctest --output-on-failure; then
        print_warning "Some tests failed, but continuing with installation"
    fi
    
    # Install to system
    print_step "Installing to $INSTALL_DIR..."
    if ! $SUDO cp xmd "$INSTALL_DIR/"; then
        print_error "Failed to install to $INSTALL_DIR"
    fi
    
    # Cleanup
    cd - >/dev/null
    rm -rf "$tmp_dir"
    
    print_success "XMD built and installed successfully!"
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
    check_dependencies
    check_permissions
    
    # Install
    install_xmd
    verify_installation
}

# Run main function
main "$@"