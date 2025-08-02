#!/bin/bash
# Comprehensive fix for all comment syntax issues

echo "=== COMPREHENSIVE COMMENT SYNTAX FIX ==="
echo "Scanning all AST files for comment issues..."

fixed=0
errors=0

# Pattern 1: Files with " * @brief" at start of line (missing /**)
echo -e "\n[Pattern 1] Fixing missing /** before * @brief..."
for file in $(find src/ast -name "*.c" -type f); do
    # Check if file has " * @brief" without /** before it
    if grep -q "^[[:space:]]*\* @brief" "$file"; then
        # Check the line before to see if it has /**
        line_num=$(grep -n "^[[:space:]]*\* @brief" "$file" | head -1 | cut -d: -f1)
        if [ ! -z "$line_num" ] && [ $line_num -gt 1 ]; then
            prev_line=$((line_num - 1))
            prev_content=$(sed -n "${prev_line}p" "$file")
            # If previous line doesn't contain /**, we need to add it
            if ! echo "$prev_content" | grep -q "/\*\*"; then
                echo "  Fixing: $file (line $line_num)"
                # Insert /** before the * @brief line
                sed -i "${line_num}s|^[[:space:]]*\* @brief|/**\n * @brief|" "$file"
                ((fixed++))
            fi
        fi
    fi
done

# Pattern 2: Files with duplicate /** on consecutive lines
echo -e "\n[Pattern 2] Fixing duplicate /** markers..."
for file in $(find src/ast -name "*.c" -type f); do
    # Look for /**\n/**
    if grep -Pzo '(?s)/\*\*\n/\*\*' "$file" >/dev/null 2>&1; then
        echo "  Fixing: $file"
        # Replace second /** with  *
        perl -i -0pe 's|/\*\*\n/\*\*|/**\n *|g' "$file"
        ((fixed++))
    fi
done

# Pattern 3: Check for */ without matching /**
echo -e "\n[Pattern 3] Checking for unmatched */ closers..."
for file in $(find src/ast -name "*.c" -type f); do
    # Count /** and */ occurrences
    open_count=$(grep -c "/\*\*" "$file" 2>/dev/null || echo 0)
    close_count=$(grep -c "\*/" "$file" 2>/dev/null || echo 0)
    if [ $close_count -gt $open_count ]; then
        echo "  Warning: $file has more */ than /** ($close_count vs $open_count)"
        ((errors++))
    fi
done

echo -e "\n=== SUMMARY ==="
echo "Files fixed: $fixed"
echo "Potential errors found: $errors"

# Test compilation
echo -e "\n=== TESTING BUILD ==="
make -j4 2>&1 | grep -E "(error:|Building C)" | grep -c "error:" || echo "0 errors"