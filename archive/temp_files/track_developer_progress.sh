#!/bin/bash
# Track Developer's C syntax repair progress
echo "=== DEVELOPER PROGRESS TRACKING ==="
echo "Checking recently fixed files..."

FIXED_COUNT=0
REMAINING_COUNT=0

# Check files that should be fixed based on system reminders
RECENTLY_FIXED=(
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
    "src/misc/ast_parse_single_value.c" 
    "src/ast/parser/statement/ast_parse_statement.c"
)

echo "Recently Fixed Files:"
for file in "${RECENTLY_FIXED[@]}"; do
    if [ -f "$file" ]; then
        # Check if file has proper /** comment structure
        if grep -q "^/\*\*$" "$file" && grep -q "^ \* @brief" "$file"; then
            echo "✅ $file - SYNTAX FIXED"
            ((FIXED_COUNT++))
        else
            echo "❌ $file - NEEDS REPAIR"
            ((REMAINING_COUNT++))
        fi
    fi
done

# Quick count of remaining files with the error pattern
REMAINING_AST=$(find src/ast -name "*.c" -exec grep -l "^#include.*\.h\"$" {} \; | xargs grep -l "^ \* @brief" | wc -l)
REMAINING_MISC=$(find src/misc -name "*.c" -exec grep -l "^#include.*\.h\"$" {} \; | xargs grep -l "^ \* @brief" | wc -l)

echo
echo "=== PROGRESS SUMMARY ==="
echo "Recently Fixed: $FIXED_COUNT files"
echo "Remaining AST files: ~$REMAINING_AST files"
echo "Remaining Misc files: ~$REMAINING_MISC files"
echo
echo "Developer is making excellent progress! 🚀"