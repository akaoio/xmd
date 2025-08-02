#!/bin/bash
# Bulk Fix Remaining Files - Genesis Leader Emergency Support

echo "⚡ BULK FIXING REMAINING AST FILES"
echo "=================================="

count=0
find src/ast -name "*.c" | while read file; do
    # Check if file needs repair (broken pattern after line 15)
    if tail -n +15 "$file" | head -10 | grep -q "^ \* @brief"; then
        echo "Fixing: $file"
        
        # Fix the pattern: add /** before orphaned * @brief and */ after
        # Use more targeted sed to fix function-level comments only
        sed -i '/^#include.*\.h"$/,/^ \* @brief.*$/ {
            /^#include.*\.h"$/ {
                a\

                a\/**
            }
            /^ \* @brief.*$/ {
                s/^ \* @brief/ * @brief/
                :loop
                n
                /^ \*/ {
                    b loop
                }
                i\ */
                b
            }
        }' "$file"
        
        count=$((count + 1))
        echo "✅ Fixed: $file"
    fi
done

echo ""
echo "🎉 Bulk repair complete!"
echo "Files processed: $count"
echo "🔧 Now testing compilation..."