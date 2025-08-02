#!/bin/bash
# Fix duplicate /** pattern in AST files

echo "🔧 Fixing duplicate /** pattern..."

# Find all files with the pattern:
# /**
# * @file ...
# /**
# * @brief ...

find src/ast -name "*.c" -type f | while read file; do
    # Check if line 3 has /**
    if sed -n '3p' "$file" | grep -q "^/\*\*$"; then
        echo "Fixing: $file"
        # Delete line 3 if it's /**
        sed -i '3d' "$file"
    fi
done

echo "✅ Duplicate /** pattern fixed!"
echo "🏗️ Testing build..."
./build.sh 2>&1 | grep -E "(Built target xmd|error:|%])" | tail -20