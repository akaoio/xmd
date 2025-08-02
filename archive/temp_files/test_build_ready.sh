#!/bin/bash
# Build Readiness Test - Genesis Leader preparation for completion

echo "🚀 BUILD READINESS CHECK"
echo "======================="

# Count progress
fixed=$(find src/ast -name "*.c" -exec grep -L "^ \* @brief" {} \; 2>/dev/null | tail -n +15 | wc -l)
total=65
remaining=$((total - fixed))

echo "Fixed files: $fixed"
echo "Remaining: $remaining"
echo "Progress: $((fixed * 100 / total))%"

# Test compilation of a few key files
echo ""
echo "🔧 TESTING KEY FILE COMPILATION:"

key_files=(
    "src/ast/evaluator/expression/ast_evaluate_binary_op.c"
    "src/ast/evaluator/control/ast_evaluate_conditional.c" 
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
)

success=0
for file in "${key_files[@]}"; do
    if [ -f "$file" ]; then
        echo "Testing: $file"
        if gcc -c "$file" -I include/ >/dev/null 2>&1; then
            echo "✅ COMPILES: $file"
            success=$((success + 1))
        else
            echo "❌ FAILS: $file"
        fi
    fi
done

echo ""
echo "Compilation test: $success/3 key files passing"

if [ $remaining -le 10 ]; then
    echo "🎯 APPROACHING COMPLETION! Prepare for full build test."
fi