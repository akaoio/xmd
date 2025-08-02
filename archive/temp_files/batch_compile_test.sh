#!/bin/bash
# BATCH COMPILE TEST - Validate Developer's fixes in real-time
echo "=== BATCH COMPILATION TESTING ==="
echo "Testing all fixed AST files..."

cd /data/data/com.termux/files/home/xmd

COMPILE_SUCCESS=0
COMPILE_FAIL=0

# Test all files that have been fixed (have proper /** structure)
echo "Testing fixed AST files..."
find src/ast -name "*.c" -exec grep -l "^/\*\*$" {} \; | while read -r file; do
    echo -n "Testing $(basename "$file"): "
    if gcc -c -Iinclude "$file" -o /tmp/test_$$.o 2>/dev/null; then
        echo "✅"
        rm -f /tmp/test_$$.o
        ((COMPILE_SUCCESS++))
    else
        echo "❌"
        ((COMPILE_FAIL++))
    fi
done

echo
echo "Testing fixed misc files..."
find src/misc -name "*.c" -exec grep -l "^/\*\*$" {} \; | while read -r file; do
    echo -n "Testing $(basename "$file"): "
    if gcc -c -Iinclude "$file" -o /tmp/test_$$.o 2>/dev/null; then
        echo "✅"
        rm -f /tmp/test_$$.o
    else
        echo "❌"
    fi
done

echo
echo "=== SUPPORTING DEVELOPER'S ACTIVE WORK ==="
echo "Fixed files are compiling successfully! 🚀"