#!/bin/bash
# Final comprehensive fix for ALL comment issues

echo "=== FINAL COMPREHENSIVE COMMENT FIX ==="
echo "Finding and fixing all remaining comment issues..."

fixed_count=0

# Find all .c files in src/ast
for file in $(find src/ast -name "*.c" -type f); do
    modified=false
    
    # Create temporary file
    temp_file="${file}.tmp"
    cp "$file" "$temp_file"
    
    # Fix Pattern 1: /**\n * @file\n *\n/** (duplicate with extra newline)
    if grep -Pzo '(?s)/\*\*\n \* @file[^\n]*\n \*\n/\*\*' "$temp_file" >/dev/null 2>&1; then
        echo "Fixing Pattern 1 in: $file"
        perl -i -0pe 's|/\*\*\n( \* @file[^\n]*\n) \*\n/\*\*|/**\n$1|g' "$temp_file"
        modified=true
    fi
    
    # Fix Pattern 2: /**\n * @file\n/** (duplicate without space)
    if grep -Pzo '(?s)/\*\*\n \* @file[^\n]*\n/\*\*' "$temp_file" >/dev/null 2>&1; then
        echo "Fixing Pattern 2 in: $file"
        perl -i -0pe 's|/\*\*\n( \* @file[^\n]*\n)/\*\*|/**\n$1 \*|g' "$temp_file"
        modified=true
    fi
    
    # Fix Pattern 3: Missing /** before  * @brief (with leading space)
    if grep -q "^[[:space:]]*\* @brief" "$temp_file"; then
        line_num=$(grep -n "^[[:space:]]*\* @brief" "$temp_file" | head -1 | cut -d: -f1)
        if [ ! -z "$line_num" ] && [ $line_num -gt 1 ]; then
            prev_line=$((line_num - 1))
            prev_content=$(sed -n "${prev_line}p" "$temp_file")
            # If previous line doesn't contain /** or */
            if ! echo "$prev_content" | grep -q "/\*\*" && ! echo "$prev_content" | grep -q "\*/"; then
                echo "Fixing Pattern 3 in: $file (line $line_num)"
                sed -i "${line_num}s|^[[:space:]]*\* @brief|/**\n * @brief|" "$temp_file"
                modified=true
            fi
        fi
    fi
    
    # If file was modified, replace original
    if [ "$modified" = true ]; then
        mv "$temp_file" "$file"
        ((fixed_count++))
    else
        rm "$temp_file"
    fi
done

echo
echo "=== SUMMARY ==="
echo "Files fixed: $fixed_count"
echo

# Final build test
echo "=== FINAL BUILD TEST ==="
make -j4 2>&1 | grep -c "\\[.*%\\]" | awk '{print "Build progress: " $1 " files compiled"}'