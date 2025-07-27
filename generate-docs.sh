#!/bin/bash

# generate-docs.sh - Generate documentation using Doxygen
# Usage: ./generate-docs.sh [options]

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
OUTPUT_DIR="build/docs"
OPEN_BROWSER=false
QUIET=false

# Parse command line arguments
for arg in "$@"; do
    case $arg in
        --open|-o)
            OPEN_BROWSER=true
            shift
            ;;
        --quiet|-q)
            QUIET=true
            shift
            ;;
        --output-dir=*)
            OUTPUT_DIR="${arg#*=}"
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --open,-o         Open documentation in browser after generation"
            echo "  --quiet,-q        Suppress output"
            echo "  --output-dir=DIR  Set output directory (default: build/docs)"
            echo "  --help,-h         Show this help message"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $arg${NC}"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

# Function to detect OS
detect_os() {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macos"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS="linux"
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        OS="windows"
    else
        OS="unknown"
    fi
}

# Function to install doxygen
install_doxygen() {
    echo -e "${YELLOW}Installing Doxygen...${NC}"
    
    detect_os
    
    case $OS in
        linux)
            if [ -f /etc/debian_version ]; then
                if command -v sudo &> /dev/null; then
                    sudo apt update && sudo apt install -y doxygen graphviz
                else
                    echo -e "${RED}sudo not available. Please run as root or install manually:${NC}"
                    echo "apt update && apt install -y doxygen graphviz"
                    exit 1
                fi
            elif [ -f /etc/redhat-release ]; then
                if command -v sudo &> /dev/null; then
                    sudo dnf install -y doxygen graphviz
                else
                    echo -e "${RED}sudo not available. Please run as root or install manually:${NC}"
                    echo "dnf install -y doxygen graphviz"
                    exit 1
                fi
            elif [ -n "$PREFIX" ] && [ -d "$PREFIX/bin" ]; then
                # Termux
                pkg install doxygen graphviz
            else
                echo -e "${RED}Unknown Linux distribution. Please install manually:${NC}"
                echo "  Ubuntu/Debian: sudo apt install doxygen graphviz"
                echo "  Fedora/RHEL:   sudo dnf install doxygen graphviz"
                echo "  Arch Linux:    sudo pacman -S doxygen graphviz"
                exit 1
            fi
            ;;
        macos)
            if command -v brew &> /dev/null; then
                brew install doxygen graphviz
            else
                echo -e "${RED}Homebrew not found. Please install Homebrew first:${NC}"
                echo "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
                exit 1
            fi
            ;;
        windows)
            echo -e "${RED}Windows detected. Please install Doxygen manually:${NC}"
            echo "Download from: https://www.doxygen.nl/download.html"
            exit 1
            ;;
        *)
            echo -e "${RED}Unknown OS. Please install Doxygen manually.${NC}"
            exit 1
            ;;
    esac
}

# Check if doxygen is installed
if ! command -v doxygen &> /dev/null; then
    echo -e "${YELLOW}Doxygen is not installed${NC}"
    
    # Ask user if they want to install
    read -p "Do you want to install Doxygen now? (y/N): " -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        install_doxygen
        
        # Check if installation was successful
        if ! command -v doxygen &> /dev/null; then
            echo -e "${RED}Installation failed. Please install Doxygen manually.${NC}"
            exit 1
        else
            echo -e "${GREEN}Doxygen installed successfully!${NC}"
        fi
    else
        echo -e "${RED}Doxygen is required to generate documentation.${NC}"
        echo "Please install it manually or run this script again and choose to install."
        exit 1
    fi
fi

# Check if Doxyfile exists
if [ -f "Doxyfile" ]; then
    DOXYFILE="Doxyfile"
elif [ -f "docs/dev/Doxyfile.in" ]; then
    # Generate Doxyfile from template
    echo -e "${BLUE}Generating Doxyfile from template...${NC}"
    
    # Get project version from CMakeLists.txt or default
    PROJECT_VERSION=$(grep -E "project\(.*VERSION" CMakeLists.txt | sed -E 's/.*VERSION[[:space:]]+([0-9.]+).*/\1/' || echo "1.0.0")
    
    # Create Doxyfile from template
    sed -e "s|@PROJECT_VERSION@|$PROJECT_VERSION|g" \
        -e "s|@CMAKE_CURRENT_SOURCE_DIR@|.|g" \
        -e "s|@CMAKE_CURRENT_BINARY_DIR@|.|g" \
        docs/dev/Doxyfile.in > Doxyfile
    
    # Update output directory
    sed -i.bak "s|OUTPUT_DIRECTORY.*=.*|OUTPUT_DIRECTORY = $OUTPUT_DIR|g" Doxyfile && rm Doxyfile.bak
    
    DOXYFILE="Doxyfile"
else
    echo -e "${RED}No Doxyfile found!${NC}"
    echo "Creating a basic Doxyfile..."
    doxygen -g
    DOXYFILE="Doxyfile"
fi

# Create output directory
mkdir -p "$OUTPUT_DIR"

# Generate documentation
if [ "$QUIET" = true ]; then
    echo -e "${BLUE}Generating documentation...${NC}"
    doxygen "$DOXYFILE" > /dev/null 2>&1
else
    echo -e "${BLUE}Generating documentation...${NC}"
    doxygen "$DOXYFILE"
fi

# Check if generation was successful
if [ -d "$OUTPUT_DIR/html/index.html" ] || [ -f "$OUTPUT_DIR/html/index.html" ]; then
    echo -e "${GREEN}Documentation generated successfully!${NC}"
    echo -e "Output directory: ${YELLOW}$OUTPUT_DIR/html${NC}"
    
    # Open in browser if requested
    if [ "$OPEN_BROWSER" = true ]; then
        detect_os
        case $OS in
            linux)
                xdg-open "$OUTPUT_DIR/html/index.html" 2>/dev/null || echo "Please open $OUTPUT_DIR/html/index.html manually"
                ;;
            macos)
                open "$OUTPUT_DIR/html/index.html"
                ;;
            windows)
                start "$OUTPUT_DIR/html/index.html"
                ;;
        esac
    fi
else
    echo -e "${RED}Documentation generation failed!${NC}"
    echo "Check the output above for errors."
    exit 1
fi

# Show quick tips
echo
echo -e "${BLUE}Quick tips:${NC}"
echo "  • View documentation: open $OUTPUT_DIR/html/index.html"
echo "  • Update docs: Run this script again after code changes"
echo "  • Add comments: Use Doxygen format (@brief, @param, @return)"
echo
echo -e "${BLUE}Doxygen comment example:${NC}"
cat << 'EOF'
/**
 * @brief Calculate the sum of two numbers
 * @param a First number
 * @param b Second number
 * @return Sum of a and b
 */
int add(int a, int b) {
    return a + b;
}
EOF

exit 0