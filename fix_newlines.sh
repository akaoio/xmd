#!/bin/bash

# Script to add newlines to all C files that are missing them

echo "Fixing missing newlines in C files..."

# Find all C files and add newline if missing
find src/ -name "*.c" -type f -exec sh -c '
    for file do
        if [ -s "$file" ] && [ "$(tail -c 1 "$file" | wc -l)" -eq 0 ]; then
            echo >> "$file"
            echo "Fixed: $file"
        fi
    done
' sh {} +

echo "Done fixing newlines!"