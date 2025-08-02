#!/bin/bash
# Fix missing braces in ast/node/util files

echo "=== FIXING AST/NODE/UTIL BRACE ERRORS ==="
fixed=0

for file in src/ast/node/util/ast_add_*.c; do
    if [ -f "$file" ]; then
        echo "Checking: $file"
        
        # Create temp file
        temp_file="${file}.fixing"
        
        # Process line by line
        in_if_block=false
        
        while IFS= read -r line; do
            # Check if this is an if statement without opening brace
            if [[ "$line" =~ ^[[:space:]]*if[[:space:]]*\(.*\)[[:space:]]*\{?[[:space:]]*$ ]]; then
                # Check if it has opening brace
                if [[ ! "$line" =~ \{[[:space:]]*$ ]]; then
                    echo "$line {" >> "$temp_file"
                    in_if_block=true
                else
                    echo "$line" >> "$temp_file"
                fi
            # Check for lines that should have "return -1;" 
            elif $in_if_block && [[ "$line" =~ ^[[:space:]]*[a-zA-Z_] ]]; then
                # This line after if without brace should be indented and have return
                echo "        return -1;" >> "$temp_file"
                echo "    }" >> "$temp_file"
                echo "" >> "$temp_file"
                echo "$line" >> "$temp_file"
                in_if_block=false
            else
                echo "$line" >> "$temp_file"
            fi
        done < "$file"
        
        # Replace file
        mv "$temp_file" "$file"
        ((fixed++))
    fi
done

echo "Files processed: $fixed"