#!/bin/bash
# Fix files where line 5 is /**

echo "=== FIXING LINE 5 DUPLICATE /** ==="
fixed=0

for file in $(find src/ast -name "*.c" -type f); do
    # Check if line 5 is exactly /**
    if sed -n '5p' "$file" | grep -q "^/\*\*$"; then
        echo "Fixing: $file"
        # Delete line 5 if it's /**
        sed -i '5d' "$file"
        ((fixed++))
    fi
done

echo "Files fixed: $fixed"