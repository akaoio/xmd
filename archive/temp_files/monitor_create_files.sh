#!/bin/bash
# Monitor ast/node/create files with syntax errors
echo "=== MONITORING AST/NODE/CREATE SYNTAX FIXES ==="
echo "Build currently at 10% - tracking 4 problematic files..."

cd /data/data/com.termux/files/home/xmd

PROBLEM_FILES=(
    "src/ast/node/create/ast_create_array_access.c"
    "src/ast/node/create/ast_create_array_literal.c"
    "src/ast/node/create/ast_create_assignment.c"
    "src/ast/evaluator/program/ast_evaluate_program_node.c"
)

echo "🔍 CHECKING SYNTAX STATUS:"

SYNTAX_OK=0
SYNTAX_ERRORS=0

for file in "${PROBLEM_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo -n "$(basename "$file"): "
        
        # Quick syntax check
        if gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
            echo "✅ FIXED"
            ((SYNTAX_OK++))
        else
            echo "❌ STILL HAS ERRORS"
            # Show specific error
            gcc -fsyntax-only -Iinclude "$file" 2>&1 | grep -E "(error:|line [0-9]+:)" | head -1 | sed 's/^/   /'
            ((SYNTAX_ERRORS++))
        fi
    fi
done

echo
echo "=== PROGRESS STATUS ==="
echo "Fixed: $SYNTAX_OK/4"
echo "Remaining: $SYNTAX_ERRORS"

if [ $SYNTAX_ERRORS -eq 0 ]; then
    echo "🎉 ALL 4 FILES FIXED - Ready for next build phase!"
else
    echo "🔄 Developer working on remaining $SYNTAX_ERRORS files..."
fi

echo
echo "SYSTEMS ENGINEER: Monitoring AST node creation files as Genesis Leader directed!"