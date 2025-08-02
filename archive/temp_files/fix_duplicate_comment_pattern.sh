#!/bin/bash
# Fix duplicate /** patterns in AST files

echo "=== FIXING DUPLICATE /** PATTERNS ==="
fixed=0

# Find all files with the pattern where line contains /** at position 3 or 5
for file in $(find src/ast -name "*.c" -type f); do
    # Check if file has the duplicate /** pattern
    if awk 'NR==3 && /^\/\*\*$/ {found3=1} NR==5 && /^\/\*\*$/ && found3 {exit 0} END {exit 1}' "$file" 2>/dev/null; then
        echo "Fixing: $file"
        # Remove line 3 if it's /**
        sed -i '3s|^/\*\*$||; /^$/d' "$file"
        ((fixed++))
    elif awk 'NR==3 && /^\/\*\*$/ {exit 0} END {exit 1}' "$file" 2>/dev/null; then
        # Check if there's a pattern like /**\n * @file\n/**
        if grep -A1 "^/\*\*$" "$file" | grep -q "^ \* @file"; then
            echo "Fixing file header: $file"
            # This file likely has /**\n * @file\n/** pattern - keep first, remove second
            awk 'NR==3 && /^\/\*\*$/ {next} {print}' "$file" > "${file}.tmp" && mv "${file}.tmp" "$file"
            ((fixed++))
        fi
    fi
done

echo "Files fixed: $fixed"

# Also fix files with empty lines 3-4
echo -e "\n=== CLEANING UP EMPTY LINES ==="
cleaned=0
for file in $(find src/ast -name "*.c" -type f); do
    # Remove multiple empty lines in the header area
    if awk 'NR<=10 && /^$/ && prev_empty {modified=1} {prev_empty=(/^$/)} END {exit modified?0:1}' "$file" 2>/dev/null; then
        echo "Cleaning: $file"
        awk 'NR<=10 && /^$/ && prev_empty {next} {prev_empty=(/^$/); print}' "$file" > "${file}.tmp" && mv "${file}.tmp" "$file"
        ((cleaned++))
    fi
done

echo "Files cleaned: $cleaned"