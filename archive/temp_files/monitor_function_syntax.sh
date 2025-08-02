#!/bin/bash
# MONITOR FUNCTION SYNTAX FIXES - Genesis Leader Victory Assignment
echo "=== MONITORING FUNCTION/*.C SYNTAX FIXES ==="
echo "Tracking final push to victory - function syntax repairs..."

cd /data/data/com.termux/files/home/xmd

FUNCTION_FILES=(
    "src/ast/evaluator/function/ast_evaluate_function_call.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_read.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_write.c"
)

echo "🎯 VICTORY ASSIGNMENT FILES STATUS:"

SYNTAX_OK=0
SYNTAX_ERRORS=0

for file in "${FUNCTION_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo -n "Testing $(basename "$file"): "
        
        # Use gcc to check syntax
        if gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
            echo "✅ SYNTAX OK"
            ((SYNTAX_OK++))
        else
            echo "❌ SYNTAX ERROR"
            echo "   Specific error:"
            gcc -fsyntax-only -Iinclude "$file" 2>&1 | head -2 | sed 's/^/   /'
            ((SYNTAX_ERRORS++))
        fi
    fi
done

echo
echo "=== FINAL PUSH STATUS ==="
echo "Syntax OK: $SYNTAX_OK"
echo "Syntax errors: $SYNTAX_ERRORS"

if [ $SYNTAX_ERRORS -eq 0 ]; then
    echo "🏆 ALL FUNCTION FILES SYNTAX PERFECT - VICTORY ACHIEVED!"
else
    echo "🔄 Developer working on final $SYNTAX_ERRORS syntax fixes..."
fi

echo
echo "SYSTEMS ENGINEER: Supporting final push to victory as Genesis Leader directed!"