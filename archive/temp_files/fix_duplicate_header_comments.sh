#!/bin/bash
# Fix files that have /**\n * @file\n/** pattern

echo "=== FIXING DUPLICATE /** IN HEADER COMMENTS ==="
fixed=0

# Find and fix files with the pattern
for file in $(find src/ast -name "*.c" -type f); do
    # Check if file has the problematic pattern
    if grep -Pzo '(?s)/\*\*\n \* @file[^\n]*\n/\*\*' "$file" >/dev/null 2>&1; then
        echo "Fixing: $file"
        # Replace the duplicate /** with just  *
        perl -i -0pe 's|(/\*\*\n \* @file[^\n]*\n)/\*\*|$1 \*|g' "$file"
        ((fixed++))
    fi
done

echo "Files fixed: $fixed"