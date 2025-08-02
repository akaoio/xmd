#!/bin/bash

echo "🔧 GENESIS LEADER - Fixing misc directory syntax errors..."

# Pattern: missing closing braces after if (!node) {
for file in src/misc/*.c; do
    if grep -q "if (!node) {" "$file"; then
        echo "Fixing: $file"
        # Fix the common pattern where 'return NULL;' is missing after 'if (!node) {'
        perl -i -pe '
            if (/if \(!node\) \{/) {
                $in_if_block = 1;
                $brace_count = 1;
            }
            if ($in_if_block && /\{/) {
                $brace_count++ unless /if \(!node\) \{/;
            }
            if ($in_if_block && /\}/) {
                $brace_count--;
                if ($brace_count == 0) {
                    $in_if_block = 0;
                }
            }
            if ($in_if_block && $brace_count == 1 && /^\s*node->/) {
                $_ = "        return NULL;\n    }\n    \n    " . $_;
                $in_if_block = 0;
            }
        ' "$file"
    fi
done

echo "✅ Misc directory syntax fixes complete"