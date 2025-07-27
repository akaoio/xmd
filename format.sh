#!/bin/bash

# format.sh - Format C/C++ source files using clang-format
# Usage: ./format.sh [--dry-run]
# Formats all .c and .h files recursively from the current working directory

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Parse command line arguments
DRY_RUN=""
VERBOSE=""

for arg in "$@"; do
    case $arg in
        --dry-run)
            DRY_RUN="--dry-run"
            shift
            ;;
        --verbose|-v)
            VERBOSE="-verbose"
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --dry-run    Preview changes without modifying files"
            echo "  --verbose,-v Show files being processed"
            echo "  --help,-h    Show this help message"
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
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        OS=$ID
    elif [ -f /etc/debian_version ]; then
        OS="debian"
    elif [ -f /etc/redhat-release ]; then
        OS="rhel"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macos"
    elif [ -n "$PREFIX" ] && [ -d "$PREFIX/bin" ]; then
        OS="termux"
    else
        OS="unknown"
    fi
}

# Function to install clang-format
install_clang_format() {
    echo -e "${YELLOW}Installing clang-format...${NC}"
    
    detect_os
    
    case $OS in
        ubuntu|debian)
            if command -v sudo &> /dev/null; then
                sudo apt update && sudo apt install -y clang-format
            else
                echo -e "${RED}sudo not available. Please run as root or install manually:${NC}"
                echo "apt update && apt install -y clang-format"
                exit 1
            fi
            ;;
        fedora|rhel|centos)
            if command -v sudo &> /dev/null; then
                sudo dnf install -y clang-tools-extra
            else
                echo -e "${RED}sudo not available. Please run as root or install manually:${NC}"
                echo "dnf install -y clang-tools-extra"
                exit 1
            fi
            ;;
        macos)
            if command -v brew &> /dev/null; then
                brew install clang-format
            else
                echo -e "${RED}Homebrew not found. Please install Homebrew first:${NC}"
                echo "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
                exit 1
            fi
            ;;
        termux)
            pkg install clang
            ;;
        arch)
            if command -v sudo &> /dev/null; then
                sudo pacman -S --noconfirm clang
            else
                echo -e "${RED}sudo not available. Please run as root or install manually:${NC}"
                echo "pacman -S clang"
                exit 1
            fi
            ;;
        *)
            echo -e "${RED}Unknown OS. Please install clang-format manually:${NC}"
            echo "  Ubuntu/Debian: sudo apt install clang-format"
            echo "  Fedora/RHEL:   sudo dnf install clang-tools-extra"
            echo "  macOS:         brew install clang-format"
            echo "  Arch Linux:    sudo pacman -S clang"
            echo "  Termux:        pkg install clang"
            exit 1
            ;;
    esac
}

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo -e "${YELLOW}clang-format is not installed${NC}"
    
    # Ask user if they want to install
    read -p "Do you want to install clang-format now? (y/N): " -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        install_clang_format
        
        # Check if installation was successful
        if ! command -v clang-format &> /dev/null; then
            echo -e "${RED}Installation failed. Please install clang-format manually.${NC}"
            exit 1
        else
            echo -e "${GREEN}clang-format installed successfully!${NC}"
        fi
    else
        echo -e "${RED}clang-format is required to run this script.${NC}"
        echo "Please install it manually or run this script again and choose to install."
        exit 1
    fi
fi

# Get the starting directory (where script was called from)
START_DIR="$(pwd)"

echo -e "${BLUE}Formatting C/C++ files in: ${START_DIR}${NC}"

if [ -n "$DRY_RUN" ]; then
    echo -e "${YELLOW}Running in dry-run mode (no files will be modified)${NC}"
fi

# Check if .clang-format exists in current or parent directories
FORMAT_FILE=""
CHECK_DIR="$START_DIR"
while [ "$CHECK_DIR" != "/" ]; do
    if [ -f "$CHECK_DIR/.clang-format" ]; then
        FORMAT_FILE="$CHECK_DIR/.clang-format"
        echo -e "${GREEN}Using .clang-format from: $FORMAT_FILE${NC}"
        break
    fi
    CHECK_DIR="$(dirname "$CHECK_DIR")"
done

if [ -z "$FORMAT_FILE" ]; then
    echo -e "${YELLOW}No .clang-format file found, using default LLVM style${NC}"
fi

# Find all .c and .h files
FILES=$(find "$START_DIR" -type f \( -name "*.c" -o -name "*.h" \) 2>/dev/null | grep -v -E '(build/|\.git/|node_modules/|vendor/|third_party/)')

# Count files
FILE_COUNT=$(echo "$FILES" | grep -c .)

if [ "$FILE_COUNT" -eq 0 ]; then
    echo -e "${YELLOW}No C/C++ files found in $START_DIR${NC}"
    exit 0
fi

echo -e "${BLUE}Found $FILE_COUNT files to format${NC}"

# Format files
FAILED=0
FORMATTED=0

# Create a temporary file to store results
TEMP_FILE=$(mktemp)

# Process each file
while IFS= read -r file; do
    if [ -n "$VERBOSE" ]; then
        echo "Processing: $file"
    fi
    
    # Run clang-format
    if [ -n "$DRY_RUN" ]; then
        # In dry-run mode, check if file would be modified
        if ! clang-format --dry-run --Werror "$file" 2>/dev/null; then
            echo -e "${YELLOW}Would format: $file${NC}"
            ((FORMATTED++))
        fi
    else
        # Actually format the file
        if clang-format -i "$file" 2>"$TEMP_FILE"; then
            if [ -s "$TEMP_FILE" ]; then
                # Error occurred
                echo -e "${RED}Failed to format: $file${NC}"
                cat "$TEMP_FILE"
                ((FAILED++))
            else
                ((FORMATTED++))
            fi
        else
            echo -e "${RED}Failed to format: $file${NC}"
            ((FAILED++))
        fi
    fi
done <<< "$FILES"

# Clean up
rm -f "$TEMP_FILE"

# Summary
echo
echo -e "${BLUE}=== Format Summary ===${NC}"
echo -e "Total files processed: $FILE_COUNT"

if [ -n "$DRY_RUN" ]; then
    echo -e "Files that would be formatted: ${YELLOW}$FORMATTED${NC}"
else
    echo -e "Files formatted: ${GREEN}$FORMATTED${NC}"
fi

if [ "$FAILED" -gt 0 ]; then
    echo -e "Files failed: ${RED}$FAILED${NC}"
    exit 1
fi

if [ -n "$DRY_RUN" ] && [ "$FORMATTED" -gt 0 ]; then
    echo
    echo -e "${YELLOW}Run without --dry-run to apply changes${NC}"
fi

exit 0