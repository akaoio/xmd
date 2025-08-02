#!/bin/bash

# Fix duplicate /** comment pattern in C files

echo "Fixing duplicate /** comment syntax..."

# Find all C files with the problematic pattern
find src/ -name "*.c" -type f | while read -r file; do
    # Check if file has consecutive /** lines
    if grep -E "^\s*/\*\*\s*$" "$file" | head -2 | tail -1 | grep -q "/\*\*"; then
        # Create temp file
        temp_file="${file}.tmp"
        
        # Process file line by line
        awk '
        BEGIN { prev_was_comment_start = 0 }
        {
            # Check if current line is /**
            if ($0 ~ /^\s*\/\*\*\s*$/) {
                if (prev_was_comment_start) {
                    # Skip this line - it is a duplicate
                    next
                } else {
                    prev_was_comment_start = 1
                    print
                }
            } else {
                prev_was_comment_start = 0
                print
            }
        }
        ' "$file" > "$temp_file"
        
        # Replace original file
        mv "$temp_file" "$file"
        echo "Fixed: $file"
    fi
done

echo "Done fixing comment syntax!"