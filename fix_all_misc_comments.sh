#!/bin/bash

echo "🔧 GENESIS LEADER - Fixing all misc file comment issues..."

# Fix files with missing */ after @return
for file in src/misc/*.c; do
    if [ -f "$file" ]; then
        # Check if file has /** without proper closing */
        if grep -q "^/\*\*$" "$file"; then
            # Count /** and */ in the file
            opens=$(grep -c "^/\*\*$" "$file")
            closes=$(grep -c "^\s*\*/$" "$file")
            
            if [ "$opens" -gt "$closes" ]; then
                echo "Fixing: $file (opens: $opens, closes: $closes)"
                
                # Add */ after @return lines that don't have it
                perl -i -pe '
                    if (/@return.*$/ && !/\*\/$/) {
                        $_ .= "\n */\n";
                    }
                ' "$file"
                
                # Ensure file ends with newline
                if [ -n "$(tail -c 1 "$file")" ]; then
                    echo "" >> "$file"
                fi
            fi
        fi
    fi
done

echo "✅ All misc file comment issues fixed"