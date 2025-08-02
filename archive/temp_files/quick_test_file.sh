#!/bin/bash
# Quick test a specific file - for Developer use
if [ $# -eq 0 ]; then
    echo "Usage: ./quick_test_file.sh <filename>"
    echo "Example: ./quick_test_file.sh ast_create_assignment.c"
    exit 1
fi

FILE="$1"
FULLPATH=""

# Find the file
if [ -f "$FILE" ]; then
    FULLPATH="$FILE"
elif [ -f "src/ast/node/create/$FILE" ]; then
    FULLPATH="src/ast/node/create/$FILE"
else
    echo "❌ File not found: $FILE"
    exit 1
fi

echo "=== TESTING: $(basename $FULLPATH) ==="
echo

# Syntax check
if gcc -fsyntax-only -Iinclude "$FULLPATH" 2>/dev/null; then
    echo "✅ SYNTAX OK! File compiles cleanly."
    echo
    echo "🎉 Great job Developer! Ready for full build test?"
    echo "   Systems Engineer can run full build now!"
else
    echo "❌ SYNTAX ERRORS found:"
    gcc -fsyntax-only -Iinclude "$FULLPATH" 2>&1 | grep -E "error:|note:" | head -10
    echo
    echo "💡 Keep working on it! I'm here when you need another test."
fi