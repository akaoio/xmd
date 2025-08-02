#\!/bin/bash

# Fix unterminated comments in misc files
echo 'Fixing misc module unterminated comments...'

for file in src/misc/ast_evaluate_block.c src/misc/ast_evaluate_break.c src/misc/ast_evaluate_continue.c src/misc/ast_evaluator_create.c; do
    if [ -f "$file" ]; then
        echo "Fixing: $file"
        # Add newline before /** if needed
        sed -i '/^\/\*\*$/i\\' "$file"
        # Ensure newline at end of file
        if [ -n "$(tail -c 1 "$file")" ]; then
            echo "" >> "$file"
        fi
    fi
done

echo 'Misc comment fixes complete\!'
