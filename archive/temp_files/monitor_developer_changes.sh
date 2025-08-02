#!/bin/bash
# Continuous monitoring for Developer changes
echo "=== MONITORING FOR DEVELOPER CHANGES ==="
echo "Will auto-detect file modifications and offer build support..."
echo

# Store initial checksums
declare -A initial_sums
for file in src/ast/node/create/ast_create_{assignment,binary_op,block,boolean_literal}.c; do
    if [ -f "$file" ]; then
        initial_sums["$file"]=$(md5sum "$file" | cut -d' ' -f1)
    fi
done

echo "Monitoring 4 error files for changes..."
echo "Press Ctrl+C to stop monitoring"
echo

while true; do
    for file in src/ast/node/create/ast_create_{assignment,binary_op,block,boolean_literal}.c; do
        if [ -f "$file" ]; then
            current_sum=$(md5sum "$file" | cut -d' ' -f1)
            if [ "${initial_sums[$file]}" != "$current_sum" ]; then
                echo "🔔 CHANGE DETECTED: $(basename $file)"
                echo "   Modified at: $(date '+%H:%M:%S')"
                
                # Quick syntax check
                if gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
                    echo "   ✅ Syntax looks good!"
                else
                    echo "   ❌ Still has syntax errors"
                fi
                
                # Update checksum
                initial_sums["$file"]="$current_sum"
                
                echo "   💡 Ready to run full build test? Just say 'build'!"
                echo
            fi
        fi
    done
    sleep 2
done