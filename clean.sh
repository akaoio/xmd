#!/bin/bash

# XMD Cleanup Script
# Safely removes temporary and test files while preserving source code
# Author: XMD Development Team
# Version: 1.0.0

# Removed set -e to prevent early exit on minor errors

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo -e "${BLUE}🧹 XMD Cleanup Script${NC}"
echo "Working directory: $PWD"
echo

# Important files that should NEVER be removed (exact filenames)
PROTECTED_FILES=(
    # Core project files
    "README.md"
    "CHANGELOG.md" 
    "LICENSE"
    "CONTRIBUTING.md"
    "CODE_OF_CONDUCT.md"
    ".gitignore"
    ".gitattributes"
    
    # Build system files
    "CMakeLists.txt"
    "Makefile"
    "configure"
    "configure.ac"
    "Makefile.am"
    "Makefile.in"
    "config.h.in"
    "install.sh"
    
    # Project metadata
    "package.json"
    "package-lock.json"
    "yarn.lock"
    "Cargo.toml"
    "Cargo.lock"
    "setup.py"
    "requirements.txt"
    "pyproject.toml"
    "go.mod"
    "go.sum"
    
    # Important documentation files
    "COMPATIBILITY.md"
    "quick_demo.md"
    
    # Scripts
    "clean.sh"
    "test.sh"
    
    # CI/CD files
    ".gitlab-ci.yml"
    ".travis.yml"
    "appveyor.yml"
    "azure-pipelines.yml"
)

PROTECTED_DIRS=(
    "src"
    "include" 
    "docs"
    "examples"
    "test"
    "tests"
    "build"
    ".git"
    "node_modules"
    "vendor"
    "target"
    "dist"
    "assets"
    "static"
    "public"
    # Note: tmp/ is not protected to allow cleaning temporary files
)

# Function to check if a file should be protected
is_protected() {
    local file="$1"
    local basename_file=$(basename "$file")
    
    # Check against protected files list (exact matches)
    for protected in "${PROTECTED_FILES[@]}"; do
        if [[ "$basename_file" == "$protected" ]]; then
            return 0  # Protected
        fi
    done
    
    # Check if it's in a protected directory (must be an actual directory path)
    for protected_dir in "${PROTECTED_DIRS[@]}"; do
        if [[ "$file" == "./$protected_dir/"* ]]; then
            return 0  # Protected (file is inside the directory)
        elif [[ "$file" == "./$protected_dir" ]]; then
            return 0  # Protected (directory itself)
        fi
    done
    
    return 1  # Not protected
}

# Function to safely remove files matching pattern
safe_remove() {
    local pattern="$1"
    local description="$2"
    local count=0
    local skipped=0
    
    echo -e "${YELLOW}Checking for $description...${NC}"
    
    # Use find to safely locate files matching pattern
    while IFS= read -r -d '' file; do
        if [[ -n "$file" && -f "$file" ]]; then
            if is_protected "$file"; then
                echo -e "${BLUE}  Protected (skipped): $file${NC}"
                ((skipped++))
            else
                echo "  Removing: $file"
                if rm -f "$file" 2>/dev/null; then
                    ((count++))
                else
                    echo -e "${RED}  Failed to remove: $file${NC}"
                fi
            fi
        fi
    done < <(find . -maxdepth 1 -name "$pattern" -type f -print0 2>/dev/null)
    
    if [[ $count -gt 0 ]]; then
        echo -e "${GREEN}  ✓ Removed $count file(s)${NC}"
    else
        echo -e "${GREEN}  ✓ No files to remove${NC}"
    fi
    
    if [[ $skipped -gt 0 ]]; then
        echo -e "${BLUE}  ℹ  Protected $skipped file(s)${NC}"
    fi
    echo
}

# Function to safely remove directories
safe_remove_dir() {
    local pattern="$1"
    local description="$2"
    local count=0
    local skipped=0
    
    echo -e "${YELLOW}Checking for $description...${NC}"
    
    while IFS= read -r -d '' dir; do
        if [[ -d "$dir" ]]; then
            if is_protected "$dir"; then
                echo -e "${BLUE}  Protected (skipped): $dir${NC}"
                ((skipped++))
            else
                echo "  Removing directory: $dir"
                rm -rf "$dir"
                ((count++))
            fi
        fi
    done < <(find . -maxdepth 1 -name "$pattern" -type d -print0 2>/dev/null)
    
    if [[ $count -gt 0 ]]; then
        echo -e "${GREEN}  ✓ Removed $count directory(ies)${NC}"
    else
        echo -e "${GREEN}  ✓ No directories to remove${NC}"
    fi
    
    if [[ $skipped -gt 0 ]]; then
        echo -e "${BLUE}  ℹ  Protected $skipped directory(ies)${NC}"
    fi
    echo
}

# Show what will be cleaned (dry run option)
if [[ "${1:-}" == "--dry-run" || "${1:-}" == "-n" ]]; then
    echo -e "${BLUE}🔍 DRY RUN - Files that would be removed:${NC}"
    echo
    
    # Function to show files that would be processed
    show_files_for_removal() {
        local pattern="$1"
        find . -maxdepth 1 -name "$pattern" -type f 2>/dev/null | while read -r file; do
            if is_protected "$file"; then
                echo -e "${BLUE}  PROTECTED (skip): $file${NC}"
            else
                echo -e "${RED}  REMOVE: $file${NC}"
            fi
        done
    }
    
    # Function to show directories that would be processed
    show_dirs_for_removal() {
        local pattern="$1"
        find . -maxdepth 1 -name "$pattern" -type d 2>/dev/null | while read -r dir; do
            if is_protected "$dir"; then
                echo -e "${BLUE}  PROTECTED (skip): $dir${NC}"
            else
                echo -e "${RED}  REMOVE: $dir${NC}"
            fi
        done
    }
    
    # Show all file patterns that would be processed
    echo -e "${YELLOW}Test files and directories:${NC}"
    show_files_for_removal "test*.md"
    show_files_for_removal "*test*.md"
    show_files_for_removal "test_*"
    show_dirs_for_removal "test_*"
    
    echo -e "${YELLOW}Temporary files and directories:${NC}"
    show_files_for_removal "tmp_*"
    show_dirs_for_removal "tmp_*"
    
    echo -e "${YELLOW}Debug files:${NC}"
    show_files_for_removal "debug*"
    
    echo -e "${YELLOW}Trace files:${NC}"
    show_files_for_removal "*.trace"
    
    echo -e "${YELLOW}Temporary files:${NC}"
    show_files_for_removal "hello.md"
    show_files_for_removal "output.*"
    show_files_for_removal "final_test.md"
    show_files_for_removal "comprehensive_test.md"
    
    echo -e "${YELLOW}Backup files:${NC}"
    show_files_for_removal "*~"
    show_files_for_removal "*.bak"
    show_files_for_removal "*.tmp"
    show_files_for_removal "*.temp"
    
    echo -e "${YELLOW}Other temporary files:${NC}"
    show_files_for_removal "*.log"
    show_files_for_removal "*.o"
    show_files_for_removal "*.obj"
    show_files_for_removal "*.swp"
    show_files_for_removal "*.swo"
    show_files_for_removal ".DS_Store"
    show_files_for_removal "Thumbs.db"
    show_files_for_removal "core"
    show_files_for_removal "*.core"
    
    echo
    echo -e "${GREEN}✓ All important files are protected and will not be removed${NC}"
    echo -e "${YELLOW}Run without --dry-run to actually remove the non-protected files${NC}"
    exit 0
fi

# Confirm before proceeding
echo -e "${YELLOW}⚠️  This will remove temporary and test files from the current directory.${NC}"
echo -e "${YELLOW}   Source code in src/, include/, docs/ will NOT be touched.${NC}"
echo
read -p "Are you sure you want to continue? (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${RED}❌ Cleanup cancelled${NC}"
    exit 0
fi

echo
echo -e "${BLUE}🚀 Starting cleanup...${NC}"
echo

# Remove test markdown files (but preserve examples/ directory)
safe_remove "test*.md" "test markdown files"
safe_remove "*test*.md" "other test files"

# Remove debug files
safe_remove "debug*.md" "debug markdown files"
safe_remove "debug*" "debug files"

# Remove trace files
safe_remove "*.trace" "execution trace files"

# Remove temporary output files
safe_remove "output.*" "temporary output files"
safe_remove "hello.md" "hello.md test file"
safe_remove "final_test.md" "final test file"
safe_remove "comprehensive_test.md" "comprehensive test file"

# Remove backup and temporary files
safe_remove "*~" "backup files (~)"
safe_remove "*.bak" "backup files (.bak)"
safe_remove "*.tmp" "temporary files (.tmp)"
safe_remove "*.temp" "temporary files (.temp)"

# Remove editor temporary files
safe_remove ".#*" "editor lock files"
safe_remove "#*#" "editor auto-save files"
safe_remove "*.swp" "vim swap files"
safe_remove "*.swo" "vim swap files"

# Remove OS temporary files
safe_remove ".DS_Store" "macOS metadata files"
safe_remove "Thumbs.db" "Windows thumbnail cache"
safe_remove "desktop.ini" "Windows desktop files"

# Remove compiler/build temporaries (but not build/ directory itself)
safe_remove "*.o" "object files"
safe_remove "*.obj" "object files"
safe_remove "*.so" "shared library files"
safe_remove "*.dll" "dynamic library files"
safe_remove "*.dylib" "dynamic library files"
safe_remove "core" "core dump files"
safe_remove "*.core" "core dump files"

# Remove log files
safe_remove "*.log" "log files"

# Remove CMake generated files and build artifacts
safe_remove "CMakeCache.txt" "CMake cache file"
safe_remove "cmake_install.cmake" "CMake install script"
safe_remove "CPackConfig.cmake" "CPack configuration"
safe_remove "CPackSourceConfig.cmake" "CPack source configuration"
safe_remove "CTestTestfile.cmake" "CTest configuration"

# Remove test_* files and directories (but preserve test/ source directory)
safe_remove "test_*" "test executables and files"
safe_remove_dir "test_*" "test_* directories"

# Remove tmp_* files and directories (temporary files/folders)
safe_remove "tmp_*" "tmp_* files"
safe_remove_dir "tmp_*" "tmp_* directories"

# Remove main executables
safe_remove "xmd" "main XMD executable"

# Remove library files
safe_remove "*.a" "static library files"
safe_remove "libxmd_lib.a" "XMD library file"

# Remove temporary analysis files
safe_remove "analyze_codebase.js" "codebase analysis script"
safe_remove "find_orphaned_files.js" "orphaned files scanner"
safe_remove "actual_files.txt" "actual files list"
safe_remove "existing_files.txt" "existing files list"
safe_remove "correct_sources.txt" "correct sources list"

# Remove additional script files (but keep core scripts)
safe_remove "fix_*.sh" "fix scripts"
safe_remove "format.sh" "format script"
safe_remove "generate-docs.sh" "docs generation script"

# Remove simple test files
safe_remove "simple_flow_test" "simple flow test executable"
safe_remove "simple_flow_test.c" "simple flow test source"

# Remove clean executable (not the script)
safe_remove "clean" "clean executable"

# Remove CMake directories (generated build files)
safe_remove_dir "CMakeFiles" "CMake generated files directory"
safe_remove_dir "Testing" "CMake testing directory"

# Clean up tmp/ directory contents (but keep directory structure)
echo -e "${YELLOW}Cleaning tmp/ directory contents...${NC}"
if [[ -d "./tmp" ]]; then
    find ./tmp -type f -exec rm -f {} \; 2>/dev/null || true
    echo -e "${GREEN}  ✓ Cleaned tmp/ directory contents${NC}"
else
    echo -e "${GREEN}  ✓ No tmp/ directory to clean${NC}"
fi
echo

# Clean up any stray files that might have been created during testing
# These are specific files I know we created during development
safe_remove "hello-output.md" "hello output file"
safe_remove "status.md" "status test file"
safe_remove "api-status.md" "API status test file"
safe_remove "project-info.md" "project info test file"
safe_remove "test_no_exec.md" "no-exec test file"
safe_remove "test_vars.md" "variables test file"
safe_remove "test_multi_vars.md" "multi-variables test file"
safe_remove "test_ranges.md" "ranges test file"
safe_remove "test_formats.md" "formats test file"
safe_remove "test_trace.md" "trace test file"

echo -e "${GREEN}🎉 Cleanup completed successfully!${NC}"
echo
echo -e "${BLUE}📁 Protected directories (never touched by this script):${NC}"
echo "  ✓ src/ - Source code"
echo "  ✓ include/ - Header files"
echo "  ✓ docs/ - Documentation"
echo "  ✓ examples/ - Example files"
echo "  ✓ test/ - Unit tests"
echo "  ✓ build/ - Build directory"
echo "  ✓ .git/ - Git repository"
echo
echo -e "${BLUE}📋 To see what would be removed without actually removing:${NC}"
echo "  ./clean.sh --dry-run"
echo
echo -e "${GREEN}✨ Your source code is safe and sound!${NC}"