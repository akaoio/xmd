#!/bin/bash
# TEST KEY FILES - Genesis Leader verified files
echo "=== TESTING KEY FILES MENTIONED BY GENESIS LEADER ==="
echo "Validating compilation of enhanced and fixed files..."

cd /data/data/com.termux/files/home/xmd

# Files specifically mentioned by Genesis Leader as successfully compiling
KEY_FILES=(
    "src/ast/evaluator/expression/ast_evaluate_binary_op.c"
    "src/ast/evaluator/control/ast_evaluate_conditional.c"
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
)

SUCCESS_COUNT=0
TOTAL_COUNT=0

for file in "${KEY_FILES[@]}"; do
    ((TOTAL_COUNT++))
    if [ -f "$file" ]; then
        echo -n "Testing $(basename "$file"): "
        if gcc -c -Iinclude "$file" -o /tmp/key_test_$$.o 2>/dev/null; then
            echo "✅ COMPILES SUCCESSFULLY"
            rm -f /tmp/key_test_$$.o
            ((SUCCESS_COUNT++))
        else
            echo "❌ COMPILATION ERROR"
            gcc -c -Iinclude "$file" 2>&1 | head -3
        fi
    else
        echo "⚠️  File not found: $file"
    fi
done

echo
echo "=== KEY FILES VALIDATION SUMMARY ==="
echo "Successfully compiling: $SUCCESS_COUNT/$TOTAL_COUNT"

if [ $SUCCESS_COUNT -eq $TOTAL_COUNT ]; then
    echo "🎉 ALL KEY FILES COMPILE SUCCESSFULLY!"
    echo "Genesis Leader's quality verification CONFIRMED ✅"
else
    echo "⚠️  Some key files need attention"
fi

echo
echo "Supporting continued excellent team execution! 🚀"