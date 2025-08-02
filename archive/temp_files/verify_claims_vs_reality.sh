#!/bin/bash
# VERIFY CLAIMS VS REALITY - Cross-check Developer's work
echo "=== VERIFYING DEVELOPER CLAIMS VS ACTUAL RESULTS ==="
echo "Independent verification of progress claims..."

cd /data/data/com.termux/files/home/xmd

# Count what Developer claims is fixed vs what actually works
echo "🔍 INDEPENDENT PROGRESS VERIFICATION:"

# Files that should have proper /** structure
CLAIMED_FIXED=$(find src/ast src/misc -name "*.c" -exec grep -l "^/\*\*$" {} \; 2>/dev/null | wc -l)

# Files that actually compile without errors
ACTUALLY_COMPILE=0
find src/ast src/misc -name "*.c" | while read -r file; do
    if gcc -c -Iinclude "$file" -o /tmp/verify_$$.o 2>/dev/null; then
        ((ACTUALLY_COMPILE++))
        rm -f /tmp/verify_$$.o
    fi
done

echo "Claimed fixed (/** structure): $CLAIMED_FIXED"
echo "Actually compiling: Testing..."

# Test specific files Developer worked on
RECENT_FILES=(
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
    "src/misc/ast_parse_single_value.c"
    "src/ast/parser/statement/ast_parse_statement.c"
    "src/ast/evaluator/expression/ast_evaluate_binary_op.c"
    "src/ast/evaluator/control/ast_evaluate_conditional.c"
)

VERIFIED_COUNT=0
TOTAL_TESTED=0

echo
echo "🧪 SPOT CHECKS ON RECENT WORK:"
for file in "${RECENT_FILES[@]}"; do
    if [ -f "$file" ]; then
        ((TOTAL_TESTED++))
        echo -n "Testing $file: "
        if gcc -c -Iinclude "$file" -o /tmp/spot_$$.o 2>/dev/null; then
            echo "✅ VERIFIED"
            rm -f /tmp/spot_$$.o
            ((VERIFIED_COUNT++))
        else
            echo "❌ COMPILATION FAILED"
            echo "   Error: $(gcc -c -Iinclude "$file" 2>&1 | head -1)"
        fi
    fi
done

echo
echo "=== VERIFICATION RESULTS ==="
echo "Spot check success rate: $VERIFIED_COUNT/$TOTAL_TESTED"

if [ $VERIFIED_COUNT -eq $TOTAL_TESTED ]; then
    echo "✅ Developer's recent work verified as correct"
else
    echo "⚠️  Some of Developer's work has issues"
fi

echo
echo "SYSTEMS ENGINEER: Independent verification complete"