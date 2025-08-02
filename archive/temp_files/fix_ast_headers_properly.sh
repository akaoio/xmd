#!/bin/bash
# Fix AST file headers properly using sed

echo "=== FIXING AST FILE HEADERS PROPERLY ==="
fixed=0

for file in $(find src/ast -name "*.c" -type f); do
    # Check if file has bad header pattern
    if head -10 "$file" | grep -E "^\*$|^/\*\*$.*^/\*\*$" >/dev/null 2>&1; then
        echo "Fixing: $file"
        
        # Create a temporary file
        temp_file="${file}.fixing"
        
        # Extract the file name from the path
        basename=$(basename "$file")
        
        # Use sed to fix the header in one pass
        sed -e '1,15s|^/\*\*$|STARTMARKER|' \
            -e '1,15s|^ \*$|EMPTYSTAR|' \
            -e '1,15s|^STARTMARKER$|/**|' \
            -e '1,15s|^EMPTYSTAR$||' \
            -e '/^$/d' \
            -e '1,15s|^STARTMARKER$|/**|g' \
            "$file" | sed '/^[[:space:]]*$/d' | sed '1,15{/^\/\*\*$/!b; n; /^\/\*\*$/{s|^|DELETEME|}}' | grep -v "^DELETEME" > "$temp_file"
        
        # Only replace if the temp file is valid
        if [ -s "$temp_file" ]; then
            mv "$temp_file" "$file"
            ((fixed++))
        else
            rm -f "$temp_file"
        fi
    fi
done

echo "Files fixed: $fixed"