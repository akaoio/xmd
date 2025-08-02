#!/bin/bash

# Fix comment syntax in core modules assigned to Systems Engineer
echo "Systems Engineer fixing core modules..."

# Function to fix comment patterns
fix_comments() {
    local file="$1"
    if [ -f "$file" ]; then
        # Fix double /** patterns
        perl -i -0pe 's/\/\*\*\n\/\*\*\n/\/\*\*\n/g' "$file"
        
        # Fix missing space after *
        perl -i -0pe 's/\/\*\*\n\s*\*\s*@/\/\*\*\n * @/g' "$file"
        
        # Fix other common patterns
        perl -i -pe 's/^\*([^\/\s])/* \1/g' "$file"
        
        # Ensure newline at end of file
        if [ -n "$(tail -c 1 "$file")" ]; then
            echo "" >> "$file"
        fi
    fi
}

# Process each module
for module in token utils store variable; do
    echo "Processing $module module..."
    find "src/$module" -name "*.c" -o -name "*.h" 2>/dev/null | while read file; do
        echo "  Fixing: $file"
        fix_comments "$file"
    done
done

echo "Core modules comment fix complete!"