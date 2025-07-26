#!/bin/bash

# INSTRUCTIONS.md Compliance Checker
# Scans the codebase for violations of the 18 rules defined in docs/dev/INSTRUCTIONS.md

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
VIOLATIONS=0
WARNINGS=0
TOTAL_FILES=0

# Directories and files to ignore
IGNORE_DIRS=".git build node_modules .vscode .idea CMakeFiles Testing"
IGNORE_ROOT_PATTERNS="test_*.c debug_*.c *_debug.c"

echo -e "${BLUE}🔍 INSTRUCTIONS.md Compliance Checker${NC}"
echo "=========================================="
echo "Checking project compliance with docs/dev/INSTRUCTIONS.md rules..."
echo

# Function to check if path should be ignored
should_ignore() {
    local path="$1"
    for ignore_dir in $IGNORE_DIRS; do
        if [[ "$path" == *"/$ignore_dir/"* ]] || [[ "$path" == "$ignore_dir/"* ]]; then
            return 0
        fi
    done
    return 1
}

# Function to report violation
report_violation() {
    local rule="$1"
    local file="$2"
    local message="$3"
    echo -e "${RED}❌ RULE $rule VIOLATION:${NC} $file"
    echo "   $message"
    ((VIOLATIONS++))
}

# Function to report warning
report_warning() {
    local rule="$1"
    local file="$2"
    local message="$3"
    echo -e "${YELLOW}⚠️  RULE $rule WARNING:${NC} $file"
    echo "   $message"
    ((WARNINGS++))
}

echo -e "${BLUE}📋 Checking Rules:${NC}"

# RULE 1: One file per folder (check for multiple .c files in same directory)
echo "1. Checking Rule 1: One file per folder..."
while IFS= read -r -d '' dir; do
    if should_ignore "$dir"; then continue; fi
    
    # Get .c files, excluding ignored patterns in root directory
    if [ "$dir" = "." ]; then
        c_files=$(find "$dir" -maxdepth 1 -name "*.c" ! -name "test_*" ! -name "debug_*" ! -name "*_debug.c" 2>/dev/null | wc -l)
        if [ "$c_files" -gt 1 ]; then
            files=$(find "$dir" -maxdepth 1 -name "*.c" ! -name "test_*" ! -name "debug_*" ! -name "*_debug.c" | tr '\n' ' ')
            report_violation "1" "$dir" "Multiple .c files in directory: $files"
        fi
    else
        c_files=$(find "$dir" -maxdepth 1 -name "*.c" 2>/dev/null | wc -l)
        if [ "$c_files" -gt 1 ]; then
            files=$(find "$dir" -maxdepth 1 -name "*.c" | tr '\n' ' ')
            report_violation "1" "$dir" "Multiple .c files in directory: $files"
        fi
    fi
done < <(find . -type d -print0 2>/dev/null)

# RULE 2: One function per file (check for multiple function definitions)
echo "2. Checking Rule 2: One function per file..."
while IFS= read -r -d '' file; do
    if should_ignore "$file"; then continue; fi
    
    # Count function definitions (simple heuristic: lines with function signature pattern)
    func_count=$(grep -cE '^[a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^)]*\)\s*\{' "$file" 2>/dev/null || echo 0)
    
    if [ "$func_count" -gt 1 ]; then
        report_violation "2" "$file" "Multiple functions found ($func_count functions)"
    fi
    
    ((TOTAL_FILES++))
done < <(find . -name "*.c" -type f -print0 2>/dev/null)

# RULE 3: File/folder naming convention (snake_case/snake_case.c)
echo "3. Checking Rule 3: snake_case naming convention..."
while IFS= read -r -d '' file; do
    if should_ignore "$file"; then continue; fi
    
    # Extract directory and filename
    dir=$(dirname "$file")
    basename_file=$(basename "$file" .c)
    parent_dir=$(basename "$dir")
    
    # Skip if in root or special directories
    if [[ "$dir" == "." ]] || [[ "$parent_dir" == "src" ]] || [[ "$parent_dir" == "test" ]]; then
        continue
    fi
    
    # Check if folder name matches file name
    if [[ "$parent_dir" != "$basename_file" ]]; then
        report_violation "3" "$file" "Folder name '$parent_dir' doesn't match file name '$basename_file'"
    fi
    
    # Check snake_case pattern
    if ! [[ "$basename_file" =~ ^[a-z][a-z0-9_]*$ ]]; then
        report_violation "3" "$file" "File name '$basename_file' is not snake_case"
    fi
    
    if ! [[ "$parent_dir" =~ ^[a-z][a-z0-9_]*$ ]]; then
        report_violation "3" "$file" "Folder name '$parent_dir' is not snake_case"
    fi
done < <(find . -name "*.c" -type f -print0 2>/dev/null)

# RULE 5: Maximum 200 lines per file
echo "5. Checking Rule 5: Maximum 200 lines per file..."
while IFS= read -r -d '' file; do
    if should_ignore "$file"; then continue; fi
    
    line_count=$(wc -l < "$file")
    if [ "$line_count" -gt 200 ]; then
        report_violation "5" "$file" "File has $line_count lines (exceeds 200 line limit)"
    fi
done < <(find . -name "*.c" -o -name "*.h" -type f -print0 2>/dev/null)

# RULE 7: No TODO, mock, simplified, tech debts
echo "7. Checking Rule 7: No TODO, mock, simplified, tech debts..."
while IFS= read -r -d '' file; do
    if should_ignore "$file"; then continue; fi
    
    # Check for TODO comments
    if grep -qi "TODO\|FIXME\|HACK\|XXX" "$file" 2>/dev/null; then
        todos=$(grep -ni "TODO\|FIXME\|HACK\|XXX" "$file" | head -3)
        report_violation "7" "$file" "Contains TODO/FIXME/HACK/XXX: $(echo "$todos" | tr '\n' '; ')"
    fi
    
    # Check for mock/simplified mentions
    if grep -qi "mock\|simplified\|placeholder" "$file" 2>/dev/null; then
        mocks=$(grep -ni "mock\|simplified\|placeholder" "$file" | head -2)
        report_warning "7" "$file" "Contains mock/simplified/placeholder: $(echo "$mocks" | tr '\n' '; ')"
    fi
done < <(find . -name "*.c" -o -name "*.h" -type f -print0 2>/dev/null)

# RULE 9: No external dependencies (check includes and CMakeLists)
echo "9. Checking Rule 9: No external dependencies..."
while IFS= read -r -d '' file; do
    if should_ignore "$file"; then continue; fi
    
    # Check for suspicious external library includes
    external_libs=$(grep -E "#include\s*[<\"]curl|boost|json|xml|openssl|sqlite" "$file" 2>/dev/null || true)
    if [ -n "$external_libs" ]; then
        report_warning "9" "$file" "Potential external dependency: $external_libs"
    fi
done < <(find . -name "*.c" -o -name "*.h" -type f -print0 2>/dev/null)

# Check CMakeLists.txt for external dependencies
if [ -f "CMakeLists.txt" ]; then
    external_deps=$(grep -E "find_package|target_link_libraries.*[^m pthread dl]" CMakeLists.txt 2>/dev/null || true)
    if [ -n "$external_deps" ]; then
        report_warning "9" "CMakeLists.txt" "Potential external dependencies in build system"
    fi
fi

# RULE 10: Doxygen documentation style
echo "10. Checking Rule 10: Doxygen documentation style..."
missing_docs=0
while IFS= read -r -d '' file; do
    if should_ignore "$file"; then continue; fi
    
    # Check for functions without Doxygen comments
    func_lines=$(grep -n "^[a-zA-Z_][a-zA-Z0-9_]*\s\+[a-zA-Z_][a-zA-Z0-9_]*\s*(" "$file" 2>/dev/null || true)
    if [ -n "$func_lines" ]; then
        while IFS= read -r line; do
            line_num=$(echo "$line" | cut -d: -f1)
            
            # Check if there's a /** comment within 10 lines before the function
            doc_found=false
            for ((i=line_num-10; i<line_num; i++)); do
                if [ $i -gt 0 ]; then
                    line_content=$(sed -n "${i}p" "$file" 2>/dev/null || true)
                    if [[ "$line_content" == *"/**"* ]] && [[ "$line_content" == *"@brief"* ]]; then
                        doc_found=true
                        break
                    fi
                fi
            done
            
            if [ "$doc_found" = false ]; then
                ((missing_docs++))
            fi
        done <<< "$func_lines"
        
        if [ $missing_docs -gt 0 ]; then
            report_warning "10" "$file" "$missing_docs functions missing Doxygen @brief documentation"
        fi
    fi
done < <(find . -name "*.c" -type f -print0 2>/dev/null)

# RULE 15: CMake usage (check for manual Makefiles)
echo "15. Checking Rule 15: CMake usage, no manual Makefiles..."
manual_makefiles=$(find . -name "Makefile" -not -path "./build/*" 2>/dev/null || true)
if [ -n "$manual_makefiles" ]; then
    report_violation "15" "$manual_makefiles" "Manual Makefile found (should use CMake only)"
fi

# RULE 16: Build artifacts in build/
echo "16. Checking Rule 16: Build artifacts in build/ directory..."
artifacts=$(find . -name "*.o" -o -name "*.a" -o -name "*.so" 2>/dev/null | grep -v "./build/" || true)
if [ -n "$artifacts" ]; then
    report_violation "16" "$artifacts" "Build artifacts found outside build/ directory"
fi

# RULE 17: Official tests in test/
echo "17. Checking Rule 17: Official tests in test/ directory..."
test_files_outside=$(find . -name "test_*.c" -not -path "./test/*" -not -path "./build/*" 2>/dev/null || true)
if [ -n "$test_files_outside" ]; then
    report_warning "17" "$test_files_outside" "Test files found outside test/ directory"
fi

# Summary
echo
echo "=========================================="
echo -e "${BLUE}📊 COMPLIANCE SUMMARY${NC}"
echo "=========================================="
echo "Total files scanned: $TOTAL_FILES"
echo -e "Violations: ${RED}$VIOLATIONS${NC}"
echo -e "Warnings: ${YELLOW}$WARNINGS${NC}"

if [ $VIOLATIONS -eq 0 ] && [ $WARNINGS -eq 0 ]; then
    echo -e "${GREEN}🎉 Perfect compliance! All INSTRUCTIONS.md rules followed.${NC}"
    exit 0
elif [ $VIOLATIONS -eq 0 ]; then
    echo -e "${YELLOW}✅ No violations found, but $WARNINGS warnings to review.${NC}"
    exit 0
else
    echo -e "${RED}❌ Found $VIOLATIONS violations that need to be fixed.${NC}"
    exit 1
fi