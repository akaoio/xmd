#!/bin/bash
# Script to help Developer fix the comment pattern quickly

echo "🔧 Fixing comment pattern in AST files..."

# Pattern 1: Fix duplicate /** on consecutive lines
find src/ast -name "*.c" -type f | while read file; do
    # Check if file has the problem pattern
    if grep -q "^\*\*$" "$file" && grep -A1 "^\*\*$" "$file" | grep -q "^\*\*$"; then
        echo "Fixing duplicate /** in: $file"
        # Use sed to fix: line with /** followed by another /** becomes single /**
        sed -i '/^\/\*\*$/N;s/^\/\*\*\n\/\*\*$/\/\*\*/' "$file"
    fi
done

# Pattern 2: Fix orphaned * @brief (missing /**)
find src/ast -name "*.c" -type f | while read file; do
    if grep -q "^ \* @brief" "$file"; then
        # Check if there's a /** before it
        if ! grep -B1 "^ \* @brief" "$file" | head -1 | grep -q "^/\*\*"; then
            echo "Fixing orphaned comment in: $file"
            # Add /** before orphaned comments
            sed -i '/^ \* @brief/{s/^ \*/\/\*\*\n \*/}' "$file"
        fi
    fi
done

echo "✅ Comment pattern fixes applied!"
echo "🏗️ Now running build to check progress..."
./build.sh 2>&1 | grep -E "(Built|error:|%])" | tail -10