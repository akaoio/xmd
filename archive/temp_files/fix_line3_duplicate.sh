#!/bin/bash
# Fix files where line 3 is /**

echo "=== FIXING LINE 3 DUPLICATE /** ==="
fixed=0

for file in $(find src/ast -name "*.c" -type f); do
    # Check if line 3 is exactly /**
    if sed -n '3p' "$file" | grep -q "^/\*\*$"; then
        echo "Fixing: $file"
        # Delete line 3 if it's /**
        sed -i '3d' "$file"
        ((fixed++))
    fi
done

echo "Files fixed: $fixed"