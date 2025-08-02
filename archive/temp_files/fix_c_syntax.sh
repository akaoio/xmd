#!/bin/bash
# Emergency C Syntax Repair Script - Genesis Leader Support for Developer
# Fixes broken comment structure in AST modular files

echo "🚨 EMERGENCY C SYNTAX REPAIR - Genesis Leader Support"
echo "Fixing broken comment patterns in AST files..."

# Find files with the error pattern and fix them
find src/ast -name "*.c" -type f | while read file; do
    # Check if file has the broken pattern: #include followed by orphaned * @brief
    if grep -q -A1 '^#include.*\.h"$' "$file" | grep -q '^ \* @brief'; then
        echo "Fixing: $file"
        
        # Create temp file with fixes
        sed '/^#include.*\.h"$/,/^ \* @brief/ {
            /^#include.*\.h"$/ {
                a\

                a\/**
            }
            /^ \* @brief/ {
                s/^ \* @brief/ * @brief/
                a\ */
            }
        }' "$file" > "${file}.tmp"
        
        # Move fixed file back
        mv "${file}.tmp" "$file"
        echo "✅ Fixed: $file"
    fi
done

echo "🎯 Repair complete! Testing compilation..."