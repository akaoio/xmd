#!/bin/bash

echo "Fixing broken printf remnants..."

# Find all lines that look like broken printf remnants (orphaned arguments)
find src/ -type f -name "*.c" -exec grep -l "value\." {} \; | while read file; do
    # Remove lines that are just orphaned printf arguments
    sed -i '/^[[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*->value\.[a-zA-Z_]*[,;)]*$/d' "$file"
    sed -i '/^[[:space:]]*[a-zA-Z_][a-zA-Z0-9_]* ? .*: .*);$/d' "$file"
    sed -i '/^[[:space:]]*".*",.*;$/d' "$file"
done

echo "Fixed broken printf remnants"