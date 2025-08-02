#!/bin/bash
# Progress Check Script - Genesis Leader monitoring Developer progress

echo "📊 C SYNTAX REPAIR PROGRESS CHECK"
echo "=================================="

# Count total AST files
total_files=$(find src/ast -name "*.c" | wc -l)
echo "Total AST files: $total_files"

# Count files still needing repair
broken_files=$(find src/ast -name "*.c" -exec grep -l "^ \* @brief" {} \; 2>/dev/null | wc -l)
echo "Files still needing repair: $broken_files"

# Count files already fixed
fixed_files=$((total_files - broken_files))
echo "Files already fixed: $fixed_files"

# Calculate progress percentage
if [ $total_files -gt 0 ]; then
    progress=$((fixed_files * 100 / total_files))
    echo "Progress: $progress% complete"
fi

echo ""
echo "🔧 Quick compilation test of fixed files:"
if [ $fixed_files -gt 0 ]; then
    echo "Testing sample fixed file..."
    # Test one fixed file compilation
    fixed_file=$(find src/ast -name "*.c" -exec grep -L "^ \* @brief" {} \; 2>/dev/null | head -1)
    if [ -n "$fixed_file" ]; then
        echo "Testing: $fixed_file"
        gcc -c "$fixed_file" -I include/ 2>&1 | head -3
    fi
fi