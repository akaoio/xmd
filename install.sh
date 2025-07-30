#!/bin/bash

# XMD Installation Script
# This script installs XMD (eXtended MarkDown) from the latest GitHub release

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

# Check installation dependencies
check_dependencies() {
    local missing_deps=()
    
    if ! command -v curl >/dev/null 2>&1 && ! command -v wget >/dev/null 2>&1; then
        missing_deps+=("curl or wget")
    fi
    
    if ! command -v tar >/dev/null 2>&1; then
        missing_deps+=("tar")
    fi
    
    if [ ${#missing_deps[@]} -gt 0 ]; then
        print_error "Missing required dependencies: ${missing_deps[*]}
        
Install them first:
  Termux: pkg install curl tar
  Ubuntu/Debian: apt install curl tar
  CentOS/RHEL: yum install curl tar
  macOS: brew install curl tar"
    fi
}

# Get latest release info from GitHub API
get_latest_release() {
    local api_response
    local download_tool
    
    # Determine which tool to use for download
    if command -v curl >/dev/null 2>&1; then
        download_tool="curl"
    elif command -v wget >/dev/null 2>&1; then
        download_tool="wget"
    else
        print_error "Either curl or wget is required for installation"
    fi
    
    print_step "Fetching latest release information..."
    
    if [ "$download_tool" = "curl" ]; then
        api_response=$(curl -s "https://api.github.com/repos/$GITHUB_REPO/releases/latest" 2>/dev/null)
    else
        api_response=$(wget -qO- "https://api.github.com/repos/$GITHUB_REPO/releases/latest" 2>/dev/null)
    fi
    
    if [ $? -ne 0 ] || [ -z "$api_response" ]; then
        print_error "Failed to fetch release information from GitHub API"
    fi
    
    # Extract tag name (version) from JSON response
    LATEST_VERSION=$(echo "$api_response" | grep '"tag_name"' | head -1 | cut -d'"' -f4)
    if [ -z "$LATEST_VERSION" ]; then
        print_error "Could not parse version from GitHub API response"
    fi
    
    print_success "Latest version found: $LATEST_VERSION"
}

# Download and install XMD from latest release
install_xmd() {
    print_step "Installing XMD from latest release for $PLATFORM..."
    
    # Get latest release information
    get_latest_release
    
    # Create temporary directory
    local tmp_dir=$(mktemp -d)
    cd "$tmp_dir"
    
    # Try to download pre-built binary first
    local binary_name="xmd-$PLATFORM"
    local binary_url="https://github.com/$GITHUB_REPO/releases/download/$LATEST_VERSION/$binary_name"
    
    print_step "Attempting to download pre-built binary for $PLATFORM..."
    
    local download_success=false
    if command -v curl >/dev/null 2>&1; then
        if curl -f -L -o "$BINARY_NAME" "$binary_url" 2>/dev/null; then
            download_success=true
        fi
    elif command -v wget >/dev/null 2>&1; then
        if wget -q -O "$BINARY_NAME" "$binary_url" 2>/dev/null; then
            download_success=true
        fi
    fi
    
    if [ "$download_success" = true ] && [ -f "$BINARY_NAME" ]; then
        print_success "Downloaded pre-built binary successfully!"
        
        # Install the binary
        print_step "Installing to $INSTALL_DIR..."
        if ! $SUDO cp "$BINARY_NAME" "$INSTALL_DIR/xmd"; then
            print_error "Failed to install to $INSTALL_DIR"
        fi
        
        # Make executable
        $SUDO chmod +x "$INSTALL_DIR/xmd"
    else
        # Fall back to building from source
        print_warning "Pre-built binary not available for $PLATFORM, building from source..."
        
        # Construct download URL for the release tarball
        local download_url="https://github.com/$GITHUB_REPO/archive/refs/tags/$LATEST_VERSION.tar.gz"
        local tarball_name="xmd-$LATEST_VERSION.tar.gz"
        
        print_step "Downloading source release $LATEST_VERSION..."
        
        # Download the release
        if command -v curl >/dev/null 2>&1; then
            if ! curl -L -o "$tarball_name" "$download_url"; then
                print_error "Failed to download release from $download_url"
            fi
        elif command -v wget >/dev/null 2>&1; then
            if ! wget -O "$tarball_name" "$download_url"; then
                print_error "Failed to download release from $download_url"
            fi
        else
            print_error "Either curl or wget is required for installation"
        fi
        
        # Extract the tarball
        print_step "Extracting release..."
        if ! tar -xzf "$tarball_name"; then
            print_error "Failed to extract release archive"
        fi
        
        # Find the extracted directory (should be xmd-<version>)
        local extracted_dir=$(find . -maxdepth 1 -type d -name "xmd-*" | head -1)
        if [ -z "$extracted_dir" ]; then
            print_error "Could not find extracted directory"
        fi
        
        cd "$extracted_dir"
        
        # Build from source
        print_step "Building from source..."
        
        # Check for build dependencies
        local missing_deps=()
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
            print_error "Missing build dependencies: ${missing_deps[*]}
            
Install them first:
  Termux: pkg install cmake clang make
  Ubuntu/Debian: apt install cmake gcc make
  CentOS/RHEL: yum install cmake gcc make
  macOS: brew install cmake gcc make"
        fi
        
        # Build
        mkdir -p build
        cd build
        
        if ! cmake -DCMAKE_BUILD_TYPE=Release ..; then
            print_error "CMake configuration failed"
        fi
        
        make -j$(nproc 2>/dev/null || echo 4)
        make_exit_code=$?
        
        # Check if the main binary was built successfully
        if [ $make_exit_code -ne 0 ] || [ ! -f "xmd" ]; then
            print_error "Build failed - exit code: $make_exit_code"
        fi
        
        # Install to system
        print_step "Installing to $INSTALL_DIR..."
        if ! $SUDO cp xmd "$INSTALL_DIR/"; then
            print_error "Failed to install to $INSTALL_DIR"
        fi
    fi
    
    # Make executable
    $SUDO chmod +x "$INSTALL_DIR/xmd"
    
    # Cleanup
    cd - >/dev/null
    rm -rf "$tmp_dir"
    
    print_success "XMD installed successfully from release $LATEST_VERSION!"
}

# Verify installation
verify_installation() {
    if command -v xmd >/dev/null 2>&1; then
        local version=$(xmd version 2>/dev/null | head -1 || echo "unknown")
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
        local current_version=$(xmd version 2>/dev/null | head -1 || echo "unknown")
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