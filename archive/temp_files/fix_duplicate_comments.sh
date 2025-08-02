#!/bin/bash
# Fix duplicate /** pattern in AST files

echo "=== FIXING DUPLICATE /** COMMENTS ==="
fixed=0

# Find files with the specific pattern: /**\n * @file\n/**
for file in $(find src/ast -name "*.c" -type f); do
    if grep -Pzo '(?s)/\*\*\n \* @file[^\n]*\n/\*\*' "$file" >/dev/null 2>&1; then
        echo "Fixing duplicate /** in: $file"
        # Use sed to fix the pattern
        sed -i '3s/^\/\*\*$/ \*/' "$file"
        ((fixed++))
    fi
done

echo "Files fixed: $fixed"