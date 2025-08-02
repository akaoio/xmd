#!/bin/bash
# Fix all files with missing */ closures before function declarations

echo "=== FIXING MISSING COMMENT CLOSURES ==="
fixed=0

for file in $(find src/ast -name "*.c" -type f); do
    # Create temp file
    temp_file="${file}.fixing"
    
    # Process file line by line
    in_comment=false
    needs_closure=false
    
    while IFS= read -r line; do
        # Check if we're starting a /** comment
        if [[ "$line" =~ ^/\*\* ]]; then
            in_comment=true
            echo "$line" >> "$temp_file"
        # Check if we see a function declaration while in comment
        elif $in_comment && [[ "$line" =~ ^[a-zA-Z_][a-zA-Z0-9_]*\*?[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*\( ]]; then
            # Missing */ - add it
            echo " */" >> "$temp_file"
            echo "$line" >> "$temp_file"
            in_comment=false
            needs_closure=true
        # Check if we found */
        elif [[ "$line" =~ \*/ ]]; then
            in_comment=false
            echo "$line" >> "$temp_file"
        else
            echo "$line" >> "$temp_file"
        fi
    done < "$file"
    
    # Only replace if we made changes
    if $needs_closure; then
        echo "Fixed: $file"
        mv "$temp_file" "$file"
        ((fixed++))
    else
        rm -f "$temp_file"
    fi
done

echo "Files fixed: $fixed"