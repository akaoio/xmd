#!/bin/bash
# Fix files where line 4 is empty (extra blank line)

echo "=== FIXING EMPTY LINE 4 ==="
fixed=0

for file in $(find src/ast -name "*.c" -type f); do
    # Check if line 4 is empty
    if [ "$(sed -n '4p' "$file")" = "" ]; then
        # Also check if line 3 has content (not empty)
        if [ "$(sed -n '3p' "$file")" != "" ]; then
            echo "Fixing: $file"
            # Delete line 4 if it's empty
            sed -i '4d' "$file"
            ((fixed++))
        fi
    fi
done

echo "Files fixed: $fixed"