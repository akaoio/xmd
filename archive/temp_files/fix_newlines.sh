#!/bin/bash
# Fix missing newlines at end of files - Supporting Developer's work
echo "=== FIXING MISSING NEWLINES ==="
echo "Adding newlines to files that need them..."

FIXED_COUNT=0

# Fix the files that system reminders showed need newlines
FILES_NEEDING_NEWLINES=(
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
    "src/misc/ast_parse_single_value.c"
    "src/ast/parser/statement/ast_parse_statement.c"
)

for file in "${FILES_NEEDING_NEWLINES[@]}"; do
    if [ -f "$file" ]; then
        # Check if file ends with newline
        if [ "$(tail -c1 "$file" | wc -l)" -eq 0 ]; then
            echo "Fixing: $file"
            echo "" >> "$file"
            ((FIXED_COUNT++))
        else
            echo "OK: $file (already has newline)"
        fi
    fi
done

echo "Fixed $FIXED_COUNT files with missing newlines"