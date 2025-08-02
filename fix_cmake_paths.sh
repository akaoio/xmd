#!/bin/bash

# Fix CMakeLists.txt paths to match Genesis principle structure
echo "🔧 Fixing CMakeLists.txt paths for Genesis principle compliance..."

# Get all .c files and their actual paths
find src/ -name "*.c" > actual_files.txt

# Process CMakeLists.txt
cp CMakeLists.txt CMakeLists.txt.backup

# Fix each source file path by finding the actual Genesis-compliant path
while IFS= read -r line; do
    if [[ $line =~ \"src/.*\.c\" ]]; then
        # Extract the file path
        file_path=$(echo "$line" | grep -o 'src/[^"]*\.c')
        base_name=$(basename "$file_path" .c)
        
        # Find the actual path with Genesis structure
        actual_path=$(grep "/${base_name}\.c$" actual_files.txt | head -1)
        
        if [[ -n "$actual_path" && "$actual_path" != "$file_path" ]]; then
            echo "Fixing: $file_path -> $actual_path"
            sed -i "s|$file_path|$actual_path|g" CMakeLists.txt
        fi
    fi
done < CMakeLists.txt.backup

rm actual_files.txt
echo "✅ CMakeLists.txt paths fixed for Genesis compliance!"