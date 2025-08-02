#!/bin/bash

echo "Searching for all C files with brace mismatches..."

# Find all C files and check for brace mismatches
find src -name "*.c" -type f | while read file; do
    if [ -f "$file" ]; then
        open_count=$(grep -c '{' "$file" 2>/dev/null || echo 0)
        close_count=$(grep -c '}' "$file" 2>/dev/null || echo 0)
        
        if [ "$open_count" -gt "$close_count" ]; then
            echo "Fixing $file (open: $open_count, close: $close_count)"
            
            # Common patterns to fix:
            # 1. Missing closing brace after free(var); return NULL
            # 2. Missing closing brace at end of file
            
            # Add missing braces
            missing=$((open_count - close_count))
            
            # Add the missing closing braces at the end
            for ((i=0; i<missing; i++)); do
                echo "}" >> "$file"
            done
        fi
    fi
done

echo "Brace fixing complete!"