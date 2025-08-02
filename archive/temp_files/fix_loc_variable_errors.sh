#!/bin/bash
# Fix missing 'loc' variable in parser files
# Systems Engineer - Automated Fix for 29% → 35%

echo "=== FIXING MISSING 'loc' VARIABLE ERRORS ==="

# Files that need source_location loc = {1, 1, "input"}; added
FILES_NEEDING_LOC=(
    "src/ast/parser/expression/ast_parse_math_expression.c"
    "src/ast/parser/expression/ast_parse_primary.c"
)

for file in "${FILES_NEEDING_LOC[@]}"; do
    if [ -f "$file" ]; then
        echo "Processing: $file"
        
        # Backup
        cp "$file" "$file.bak"
        
        # Add source_location after the function start
        sed -i '/^ast_node\* ast_parse_.*({/a\    source_location loc = {1, 1, "input"};' "$file"
        
        echo "✓ Added loc variable to $file"
    else
        echo "Warning: $file not found"
    fi
done

echo
echo "=== LOC VARIABLE FIX COMPLETE ==="
echo "Testing affected files..."

# Test compile just these files
cd /data/data/com.termux/files/home/xmd/build
for file in "${FILES_NEEDING_LOC[@]}"; do
    echo "Testing: $file"
    make CMakeFiles/xmd_lib.dir/${file}.o 2>&1 | grep -E "(error:|warning:|Building)" | head -3
done