#!/bin/bash

echo "🔧 GENESIS LEADER - Fixing misc directory brace issues..."

# Find and fix files with the pattern
for file in src/misc/ast_create_*.c; do
    if [ -f "$file" ]; then
        # Check if file has missing closing braces
        if grep -q "free(node);" "$file" && ! grep -A1 "free(node);" "$file" | grep -q "return NULL;"; then
            echo "Fixing: $file"
            
            # Fix the pattern where free(node); is not followed by return NULL;
            perl -i -pe '
                if (/^\s*free\(node\);/) {
                    $_ .= "        return NULL;\n    }\n    \n";
                }
            ' "$file"
            
            # Remove duplicate lines
            perl -i -0pe 's/return node;\s*return node;/return node;/g' "$file"
        fi
    fi
done

echo "✅ Misc directory brace fixes complete"