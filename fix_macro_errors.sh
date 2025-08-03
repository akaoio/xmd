#!/bin/bash

# Find all C files that have both a variable declaration and XMD_CREATE_VALIDATED macro
find src/ -name "*.c" -exec grep -l "XMD_CREATE_VALIDATED" {} \; | while read file; do
    echo "Checking: $file"
    
    # Look for pattern: type* var; followed by XMD_CREATE_VALIDATED(var, ...)
    if grep -q -P '^\s*\w+\*\s+\w+;\s*$' "$file" && grep -q "XMD_CREATE_VALIDATED" "$file"; then
        echo "Found potential duplicate declaration in: $file"
        
        # Extract the variable name from XMD_CREATE_VALIDATED line
        var_name=$(grep "XMD_CREATE_VALIDATED" "$file" | sed 's/.*XMD_CREATE_VALIDATED(\s*\([^,]*\).*/\1/' | tr -d ' ')
        
        if [ ! -z "$var_name" ]; then
            echo "Variable name: $var_name"
            
            # Remove the duplicate declaration line
            sed -i "/^\s*\w\+\*\s\+${var_name};\s*$/d" "$file"
            echo "Fixed: $file"
        fi
    fi
done