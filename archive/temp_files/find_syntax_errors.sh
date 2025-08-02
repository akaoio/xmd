#!/bin/bash
# EMERGENCY: Find C syntax error pattern in AST files
# Pattern: Missing /** and */ around @brief comments after #include lines

echo "=== SEARCHING FOR C SYNTAX ERROR PATTERN ==="
echo "Pattern: Missing /** comment openers after #include lines"
echo

TOTAL_ERRORS=0

# Search in AST directory
find src/ast -name "*.c" -type f | while read -r file; do
    # Look for lines with " * @brief" not preceded by "/**"
    if grep -n "^ \* @brief" "$file" | head -1 | grep -q "@brief"; then
        echo "❌ SYNTAX ERROR: $file"
        echo "   Missing /** comment opener before @brief"
        ((TOTAL_ERRORS++))
    fi
done

# Search in misc directory  
find src/misc -name "*.c" -type f | while read -r file; do
    if grep -n "^ \* @brief" "$file" | head -1 | grep -q "@brief"; then
        echo "❌ SYNTAX ERROR: $file" 
        echo "   Missing /** comment opener before @brief"
        ((TOTAL_ERRORS++))
    fi
done

echo
echo "Total files with syntax errors: $TOTAL_ERRORS"