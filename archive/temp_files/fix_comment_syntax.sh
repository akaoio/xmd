#!/bin/bash
# Script to fix systematic C comment syntax errors in AST files

echo "=== FIXING C COMMENT SYNTAX ERRORS ==="
echo "Pattern: Missing /** before * @brief"
echo

# Counter for fixed files
fixed=0

# Find all .c files under src/ast/
for file in $(find src/ast -name "*.c" -type f); do
    # Check if file has the error pattern (missing /** before * @brief)
    if grep -q "^[[:space:]]*\* @brief" "$file"; then
        # Check if it's NOT already inside a proper comment block
        if ! grep -B1 "^[[:space:]]*\* @brief" "$file" | grep -q "/\*\*"; then
            echo "Fixing: $file"
            
            # Create temp file with fix
            temp_file="${file}.tmp"
            
            # Process the file line by line
            in_header=true
            found_brief=false
            
            while IFS= read -r line; do
                # If we find " * @brief" at start of line (with optional leading spaces)
                if [[ "$line" =~ ^[[:space:]]*\*[[:space:]]@brief ]] && ! $found_brief; then
                    # Insert /** before it
                    echo "/**" >> "$temp_file"
                    echo "$line" >> "$temp_file"
                    found_brief=true
                else
                    echo "$line" >> "$temp_file"
                fi
            done < "$file"
            
            # Replace original file
            mv "$temp_file" "$file"
            ((fixed++))
        fi
    fi
done

echo
echo "=== SUMMARY ==="
echo "Files fixed: $fixed"
echo

# Now compile again to check progress
echo "=== TESTING BUILD ==="
make -j4 2>&1 | grep -c "error:"