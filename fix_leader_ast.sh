#!/bin/bash
# Fix script for Leader's AST modules
# Developer helping Leader fix comment syntax in AST modules

echo "=== DEVELOPER HELPING LEADER WITH AST MODULES ==="
echo "Fixing comment syntax in src/ast/..."

# Function to fix comment patterns in a file
fix_comments() {
    local file="$1"
    
    # Fix multiple /** /** patterns
    perl -i -0pe 's/\/\*\*\n\/\*\*\n/\/\*\*\n/g' "$file"
    
    # Fix /** followed by /** on next line
    perl -i -0pe 's/\/\*\*\s*\n\s*\/\*\*/\/\*\*/g' "$file"
    
    # Fix **/ */ patterns  
    perl -i -0pe 's/\*\/\s*\n\s*\*\//\*\//g' "$file"
    
    # Fix closing comment blocks
    perl -i -0pe 's/\s*\*\s*\/\n\s*\*\//\n \*\//g' "$file"
    
    # Fix @file lines
    perl -i -0pe 's/\/\*\*\n\s*\*\s*@file/\/\*\*\n * @file/g' "$file"
    
    echo "  Fixed: $file"
}

# Track progress
total_files=0
fixed_files=0

# Process all AST subdirectories
for dir in evaluator node parser value; do
    echo ""
    echo "Processing src/ast/$dir/..."
    
    if [ -d "src/ast/$dir" ]; then
        # Find all .c files in subdirectories
        find "src/ast/$dir" -name "*.c" | while read file; do
            ((total_files++))
            fix_comments "$file"
            ((fixed_files++))
        done
    fi
done

echo ""
echo "=== AST FIX COMPLETE ==="
echo "Fixed $fixed_files AST module files"
echo "Leader can now continue with the build!"
echo ""
echo "Developer helping Leader - TEAMWORK! 💪"