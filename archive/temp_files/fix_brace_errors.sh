#!/bin/bash
# Script to automatically fix missing braces in parser files
# Systems Engineer - Emergency Fix Tool

echo "=== AUTOMATIC BRACE FIX SCRIPT ==="
echo "Targeting parser files with missing braces..."
echo

# Function to add missing braces to common patterns
fix_missing_braces() {
    local file=$1
    echo "Processing: $file"
    
    # Create backup
    cp "$file" "$file.bak"
    
    # Pattern 1: Missing return after else
    sed -i '/} else {$/,/^[[:space:]]*$/{
        /} else {$/{
            N
            s/} else {\n[[:space:]]*$/} else {\n        return -1;\n    }\n/
        }
    }' "$file"
    
    # Pattern 2: Missing return after if (!something)
    sed -i '/if (!.*) {$/,/^[[:space:]]*$/{
        /if (!.*) {$/{
            N
            s/if \(.*\) {\n[[:space:]]*$/if \1 {\n        return -1;\n    }\n/
        }
    }' "$file"
    
    # Pattern 3: Missing closing brace before else
    sed -i '/^[[:space:]]*} else {/{
        i\    }
    }' "$file"
    
    # Check if file was modified
    if ! diff -q "$file" "$file.bak" > /dev/null; then
        echo "  ✓ Fixed braces in $file"
        rm "$file.bak"
    else
        echo "  - No changes needed in $file"
        rm "$file.bak"
    fi
}

# Target files with known brace errors
TARGET_FILES=(
    "src/ast/parser/class/ast_parse_class.c"
    "src/ast/parser/class/ast_parse_method.c"
    "src/ast/parser/control/ast_parse_elif.c"
    "src/ast/parser/control/ast_parse_else.c"
    "src/ast/parser/control/ast_parse_if.c"
    "src/ast/parser/control/ast_parse_while.c"
)

# Process each file
for file in "${TARGET_FILES[@]}"; do
    if [ -f "$file" ]; then
        fix_missing_braces "$file"
    else
        echo "Warning: $file not found"
    fi
done

echo
echo "=== BRACE FIX COMPLETE ==="
echo "Now testing build..."

# Test build
cd /data/data/com.termux/files/home/xmd/build
make 2>&1 | grep -E "(\[.*%\]|error:)" | tail -10