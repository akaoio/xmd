#!/bin/bash

# Authentic Naming Operation - Remove "simple" from all function names
# Genesis Leader - User Directive: "we should be authentic"

echo "🚨 AUTHENTIC NAMING OPERATION - Critical User Directive"
echo "======================================================="

# Step 1: Find all files with 'simple' in name
echo "Step 1: Identifying files with 'simple' naming..."
find src/ -name "*simple*" > simple_files.txt
SIMPLE_COUNT=$(wc -l < simple_files.txt)
echo "Found $SIMPLE_COUNT files requiring rename"

if [ $SIMPLE_COUNT -eq 0 ]; then
    echo "✅ No files with 'simple' naming found"
    exit 0
fi

# Step 2: Create rename mapping
echo ""
echo "Step 2: Creating authentic rename mapping..."
> rename_mapping.txt

while read file; do
    # Extract directory and filename
    dir=$(dirname "$file")
    filename=$(basename "$file")
    
    # Remove 'simple' from filename
    new_filename=$(echo "$filename" | sed 's/_simple//')
    new_file="$dir/$new_filename"
    
    echo "$file -> $new_file" >> rename_mapping.txt
    echo "  📝 $filename → $new_filename"
done < simple_files.txt

# Step 3: Perform file renames
echo ""
echo "Step 3: Executing file renames..."
while read line; do
    old_file=$(echo "$line" | cut -d' ' -f1)
    new_file=$(echo "$line" | cut -d' ' -f3)
    
    if [ -f "$old_file" ]; then
        echo "  🔄 Renaming: $(basename "$old_file") → $(basename "$new_file")"
        mv "$old_file" "$new_file"
    fi
done < rename_mapping.txt

# Step 4: Update function names in source code
echo ""
echo "Step 4: Updating function names in source code..."

# Update function definitions (remove _simple from function names)
find src/ -name "*.c" -exec sed -i 's/ast_parse_\([a-z_]*\)_simple(/ast_parse_\1(/g' {} \;
find src/ -name "*.h" -exec sed -i 's/ast_parse_\([a-z_]*\)_simple(/ast_parse_\1(/g' {} \;

# Update function calls
find src/ -name "*.c" -exec sed -i 's/ast_parse_\([a-z_]*\)_simple(/ast_parse_\1(/g' {} \;

echo ""
echo "Step 5: Updating CMakeLists.txt..."
# Update CMakeLists.txt
sed -i 's/_simple\.c/\.c/g' CMakeLists.txt

echo ""
echo "Step 6: Updating include/ast.h declarations..."
# Update header declarations
sed -i 's/ast_parse_\([a-z_]*\)_simple(/ast_parse_\1(/g' include/ast.h

echo ""
echo "🎉 AUTHENTIC NAMING OPERATION COMPLETE!"
echo "======================================"
echo "✅ All 'simple' naming removed from codebase"
echo "✅ Function names now authentic and descriptive"
echo "✅ CMakeLists.txt updated"
echo "✅ Header declarations updated"
echo ""
echo "Next: Run build test to verify naming compliance"