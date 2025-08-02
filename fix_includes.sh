#!/bin/bash

echo "🔧 Fixing include paths for Genesis principle structure..."

# Fix include paths based on directory depth
find src/ -name "*.c" -exec bash -c '
    file="$1"
    depth=$(echo "$file" | tr "/" "\n" | wc -l)
    depth=$((depth - 1))  # Subtract 1 for src
    
    # Calculate relative path to include directory
    if [ $depth -eq 2 ]; then
        rel_path="../../include/"
    elif [ $depth -eq 3 ]; then
        rel_path="../../../include/"
    elif [ $depth -eq 4 ]; then
        rel_path="../../../../include/"
    elif [ $depth -eq 5 ]; then
        rel_path="../../../../../include/"
    elif [ $depth -eq 6 ]; then
        rel_path="../../../../../../include/"
    else
        rel_path="../../../../include/"  # fallback
    fi
    
    # Fix common include patterns
    sed -i "s|#include \"../../include/|#include \"${rel_path}|g" "$file"
    sed -i "s|#include \"../../../include/|#include \"${rel_path}|g" "$file"
    sed -i "s|#include \"../../../../include/|#include \"${rel_path}|g" "$file"
    sed -i "s|#include \"../../../../../include/|#include \"${rel_path}|g" "$file"
    sed -i "s|#include \"../../../../../../include/|#include \"${rel_path}|g" "$file"
    
    echo "Fixed: $file (depth: $depth, path: $rel_path)"
' _ {} \;

echo "✅ Include paths fixed for Genesis compliance!"