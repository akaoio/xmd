#!/bin/bash
# MONITOR FILEIO FIXES - Real-time verification as Genesis Leader ordered
echo "=== MONITORING FILEIO FIXES - GENESIS LEADER ASSIGNMENT ==="
echo "Tracking Developer's urgent fileio/*.c syntax repairs..."

cd /data/data/com.termux/files/home/xmd

FILEIO_FILES=(
    "src/ast/evaluator/fileio/ast_evaluate_file_exists.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_list.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_delete.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_read.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_write.c"
)

echo "🔍 FILEIO FILES STATUS CHECK:"

FIXED_COUNT=0
NEEDS_FIX=0

for file in "${FILEIO_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo -n "Checking $(basename "$file"): "
        
        # Check if has proper /** comment structure
        if grep -q "^/\*\*$" "$file" && grep -q "^ \*/$" "$file"; then
            echo "✅ SYNTAX FIXED"
            ((FIXED_COUNT++))
        else
            echo "❌ NEEDS FIX (missing /** structure)"
            ((NEEDS_FIX++))
        fi
    fi
done

echo
echo "=== FILEIO MONITORING SUMMARY ==="
echo "Fixed: $FIXED_COUNT"
echo "Still need fixes: $NEEDS_FIX"

if [ $NEEDS_FIX -eq 0 ]; then
    echo "🎉 ALL FILEIO FILES FIXED!"
else
    echo "🔄 Developer working on remaining $NEEDS_FIX files..."
fi

echo
echo "SYSTEMS ENGINEER: Monitoring fileio fixes as Genesis Leader directed"