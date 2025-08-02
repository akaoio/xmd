#!/bin/bash

# Fix duplicate comment blocks in resource module files

echo "Fixing comment syntax in resource module..."

# Find all .c files in resource module
for file in $(find src/resource -name "*.c" -type f); do
    echo "Processing: $file"
    
    # Create temporary file
    temp_file="${file}.tmp"
    
    # Process the file to remove duplicate comment blocks
    awk '
    BEGIN { in_comment = 0; skip_next = 0 }
    
    # If we see /** and we are already in a comment block, skip it
    /^\/\*\*$/ {
        if (in_comment == 1) {
            skip_next = 3  # Skip this and next 3 lines
            next
        } else {
            in_comment = 1
            print
            next
        }
    }
    
    # Track end of comment blocks
    /^\*\/$/ {
        if (skip_next > 0) {
            skip_next--
            next
        } else {
            in_comment = 0
            print
            next
        }
    }
    
    # Skip lines if needed
    {
        if (skip_next > 0) {
            skip_next--
            next
        } else {
            print
        }
    }
    ' "$file" > "$temp_file"
    
    # Replace original file
    mv "$temp_file" "$file"
done

echo "Comment syntax fixed in resource module!"