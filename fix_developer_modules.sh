#!/bin/bash
# Developer's module fix script

echo "=== DEVELOPER: Fixing assigned modules ==="

# Function to fix comment patterns
fix_comments() {
    local file="$1"
    
    # Fix multiple /** on consecutive lines
    perl -i -0pe 's/\/\*\*\n\/\*\*\n/\/\*\*\n/g' "$file"
    
    # Fix /** followed by another /** after a few lines
    perl -i -0pe 's/\/\*\*\n([^\n]*\n){0,3}\/\*\*/ \/**\n\1/g' "$file"
    
    # Fix orphaned comment parameters
    perl -i -0pe 's/\n\s*\*\/\n\s*\*\s*@(brief|param|return)/\n\/**\n * @\1/g' "$file"
    
    # Remove duplicate */ lines
    perl -i -pe 's/^\s*\*\/\s*$//g if $prev =~ /^\s*\*\/\s*$/; $prev = $_' "$file"
    
    # Ensure proper comment closure before function declarations
    perl -i -0pe 's/\*\s*@return([^\*]*)\n([a-zA-Z_][a-zA-Z0-9_*\s]+\([^)]*\)\s*{)/ * @return\1\n *\/\n\2/g' "$file"
    
    echo "  Fixed: $file"
}

# Priority 1: Fix bindings module
echo "Fixing bindings module..."
find src/bindings -name "*.c" | while read file; do
    fix_comments "$file"
done

# Priority 2: Fix config module  
echo "Fixing config module..."
find src/config -name "*.c" | while read file; do
    fix_comments "$file"
done

# Priority 3: Fix conditional module
echo "Fixing conditional module..."
find src/conditional -name "*.c" | while read file; do
    fix_comments "$file"
done

# Priority 4: Fix devtools module
echo "Fixing devtools module..."
find src/devtools -name "*.c" | while read file; do
    fix_comments "$file"
done

echo "=== DEVELOPER: Module fixes complete ===""