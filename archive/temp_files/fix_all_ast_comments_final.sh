#!/bin/bash
# Final fix for all AST comment issues - handles all patterns correctly

echo "=== FINAL AST COMMENT FIX ==="
fixed=0

# Process each file individually
for file in $(find src/ast -name "*.c" -type f); do
    # Read the first 20 lines of the file
    head -20 "$file" > temp_header.txt
    
    # Check if file has any comment issues
    if grep -E "(^/\*\*$.*^/\*\*$|^\s*\* @brief)" temp_header.txt >/dev/null 2>&1; then
        echo "Fixing: $file"
        
        # Use perl to fix the file in one pass
        perl -i -pe '
            # State variables
            BEGIN { 
                $in_file_header = 1; 
                $fixed_header = 0;
                $line_num = 0;
            }
            
            $line_num++;
            
            # Fix duplicate /** in file header (lines 1-10)
            if ($line_num <= 10 && !$fixed_header) {
                if (/^\s*\*\s*$/ && $next_is_second_comment) {
                    $next_is_second_comment = 0;
                    next; # Skip the line
                }
                if (/^\/\*\*$/ && $saw_first_comment) {
                    $_ = " *\n";
                    $fixed_header = 1;
                }
                if (/^\/\*\*$/ && !$saw_first_comment) {
                    $saw_first_comment = 1;
                }
            }
            
            # Fix missing /** before * @brief anywhere in file
            if (/^\s*\* \@brief/ && $prev_line !~ /\/\*\*/ && $prev_line !~ /\*\//) {
                $_ = "/**\n" . $_;
            }
            
            $prev_line = $_;
        ' "$file"
        
        ((fixed++))
    fi
    
    rm -f temp_header.txt
done

echo "Files fixed: $fixed"

# Now let\'s verify by checking a few files
echo -e "\n=== VERIFYING FIXES ==="
for file in src/ast/node/create/ast_create_assignment.c src/ast/node/create/ast_create_binary_op.c src/ast/node/create/ast_create_function_call.c; do
    if [ -f "$file" ]; then
        echo -e "\n$file (first 8 lines):"
        head -8 "$file" | cat -n
    fi
done