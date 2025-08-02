#!/bin/bash

echo "🔧 GENESIS LEADER - Fixing AST module comments..."

# Fix AST module comments
for dir in src/ast/evaluator src/ast/node src/ast/parser src/ast/value; do
    if [ -d "$dir" ]; then
        echo "📁 Processing $dir..."
        find "$dir" -name "*.c" -o -name "*.h" | while read file; do
            if [ -f "$file" ]; then
                # Create backup
                cp "$file" "${file}.bak"
                
                # Fix multiple /** patterns
                perl -i -0pe 's/\/\*\*\n\/\*\*\n/\/\*\*\n/g' "$file"
                perl -i -0pe 's/\/\*\*\n\s*\/\*\*/\/\*\*/g' "$file"
                perl -i -0pe 's/\/\*\*\n(\s*\*\s*@)/\/\*\*\n\1/g' "$file"
                
                # Fix broken comment blocks
                perl -i -0pe 's/\*\/\s*\n\s*\*\s/@/g' "$file"
                perl -i -0pe 's/@\/\n/\*\/\n/g' "$file"
                
                echo "  ✅ Fixed: $file"
            fi
        done
    fi
done

echo "✨ AST module comment fix complete!"