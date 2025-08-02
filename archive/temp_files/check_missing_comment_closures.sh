#!/bin/bash
# Check for files with missing */ comment closures

echo "=== CHECKING FOR MISSING COMMENT CLOSURES ==="
found=0

for file in $(find src/ast -name "*.c" -type f); do
    # Count /** and */ in the file
    open_count=$(grep -c "/\*\*" "$file" 2>/dev/null || echo 0)
    close_count=$(grep -c "\*/" "$file" 2>/dev/null || echo 0)
    
    if [ $open_count -gt $close_count ]; then
        echo "Missing closure in: $file (/** count: $open_count, */ count: $close_count)"
        # Show the lines around function declarations
        grep -n -B2 -A2 "^[a-zA-Z].*(" "$file" | grep -E "(^[0-9]+-|/\*\*|\*/)" | head -10
        echo "---"
        ((found++))
    fi
done

echo -e "\nTotal files with missing closures: $found"