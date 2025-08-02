#!/bin/bash
# Fix remaining parser errors systematically

echo "=== FIXING REMAINING PARSER ERRORS ==="

# Find all parser files with potential brace issues
parser_files=$(find src/ast/parser -name "*.c" -exec grep -l "if (.*{$" {} \; 2>/dev/null)

for file in $parser_files; do
    echo "Checking: $file"
    
    # Count open and close braces
    open_count=$(grep -c "{" "$file" 2>/dev/null || echo 0)
    close_count=$(grep -c "}" "$file" 2>/dev/null || echo 0)
    
    if [ $open_count -ne $close_count ]; then
        echo "  WARNING: Brace mismatch in $file (open: $open_count, close: $close_count)"
    fi
done

# Fix specific files we know have issues
echo -e "\nFixing known problematic files..."

# Fix ast_parse_method.c
if [ -f "src/ast/parser/class/ast_parse_method.c" ]; then
    echo "Fixing ast_parse_method.c..."
    # Add missing closing braces at specific locations
    sed -i '54a\        }' src/ast/parser/class/ast_parse_method.c
    sed -i '59a\    }' src/ast/parser/class/ast_parse_method.c  
    sed -i '61a\    }' src/ast/parser/class/ast_parse_method.c
    sed -i '67a\    }' src/ast/parser/class/ast_parse_method.c
    sed -i '76a\        }' src/ast/parser/class/ast_parse_method.c
    sed -i '92a\                }' src/ast/parser/class/ast_parse_method.c
    sed -i '96a\        }' src/ast/parser/class/ast_parse_method.c
    sed -i '98a\    }' src/ast/parser/class/ast_parse_method.c
fi

echo "Done fixing parser files"