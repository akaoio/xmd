#!/bin/bash
# EMERGENCY AST SYNTAX VALIDATION SCRIPT
# Tests compilation of fixed AST files incrementally
# Usage: ./validate_ast_fixes.sh [directory]

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
AST_DIR="${1:-${SCRIPT_DIR}/src/ast}"
MISC_DIR="${SCRIPT_DIR}/src/misc"
INCLUDE_DIR="${SCRIPT_DIR}/include"

echo "=== AST SYNTAX VALIDATION SCRIPT ==="
echo "AST Directory: $AST_DIR"
echo "Misc Directory: $MISC_DIR"
echo "Include Directory: $INCLUDE_DIR"
echo

# Counter for results
TOTAL_FILES=0
SYNTAX_OK=0
SYNTAX_ERRORS=0

# Function to test C syntax of a file
test_c_syntax() {
    local file="$1"
    echo -n "Testing: $(basename "$file")... "
    
    # Use gcc to check syntax only
    if gcc -fsyntax-only -I"$INCLUDE_DIR" "$file" 2>/dev/null; then
        echo "✅ OK"
        ((SYNTAX_OK++))
    else
        echo "❌ SYNTAX ERROR"
        # Show the specific error
        gcc -fsyntax-only -I"$INCLUDE_DIR" "$file" 2>&1 | head -3
        ((SYNTAX_ERRORS++))
    fi
    ((TOTAL_FILES++))
}

# Test all AST files
if [ -d "$AST_DIR" ]; then
    echo "--- Testing AST Files ---"
    find "$AST_DIR" -name "*.c" -type f | while read -r file; do
        test_c_syntax "$file"
    done
    echo
fi

# Test misc files  
if [ -d "$MISC_DIR" ]; then
    echo "--- Testing Misc Files ---"
    find "$MISC_DIR" -name "*.c" -type f | while read -r file; do
        test_c_syntax "$file"
    done
    echo
fi

echo "=== VALIDATION SUMMARY ==="
echo "Total files tested: $TOTAL_FILES"  
echo "Syntax OK: $SYNTAX_OK"
echo "Syntax errors: $SYNTAX_ERRORS"

if [ $SYNTAX_ERRORS -eq 0 ]; then
    echo "✅ ALL FILES HAVE CORRECT C SYNTAX"
    exit 0
else
    echo "❌ $SYNTAX_ERRORS FILES HAVE SYNTAX ERRORS"
    exit 1
fi