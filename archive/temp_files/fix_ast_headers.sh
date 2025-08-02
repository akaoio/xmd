#!/bin/bash

# Fix missing headers in AST modular files
# Genesis Leader - Phase 4 header dependency resolution

echo "🔧 Genesis Header Dependency Fix - Phase 4"
echo "=========================================="

# Files that need string.h
STRING_FILES=(
    "src/ast/parser/loop/ast_parse_while_simple.c"
    "src/ast/parser/loop/ast_parse_range_loop.c"
    "src/ast/parser/expression/ast_parse_expression_simple.c"
    "src/ast/parser/expression/ast_parse_math_expression.c"
    "src/ast/parser/expression/ast_parse_comparison_expression.c"
    "src/ast/parser/control/ast_parse_if_then_simple.c"
    "src/ast/parser/statement/ast_parse_statement_simple.c"
)

# Files that need stdio.h (using printf/sprintf/fprintf)
STDIO_FILES=(
    "src/ast/parser/function/ast_parse_function_simple.c"
    "src/ast/parser/class/ast_parse_class_simple.c"
    "src/ast/parser/class/ast_parse_method_simple.c"
    "src/ast/parser/expression/ast_parse_math_expression.c"
    "src/ast/parser/expression/ast_parse_comparison_expression.c"
    "src/ast/parser/control/ast_parse_if_then_simple.c"
    "src/ast/parser/literal/ast_parse_array_assignment.c"
    "src/ast/value/ast_value_to_string.c"
    "src/ast/value/ast_value_to_variable.c"
    "src/ast/evaluator/function/ast_evaluate_function_call.c"
    "src/ast/evaluator/function/ast_evaluate_function_def.c"
    "src/ast/evaluator/control/ast_evaluate_conditional.c"
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c"
    "src/ast/evaluator/loop/ast_evaluate_loop.c"
    "src/ast/evaluator/fileio/ast_evaluate_file_write.c"
    "src/ast/evaluator/expression/ast_evaluate_binary_op.c"
    "src/ast/evaluator/expression/ast_evaluate_identifier.c"
)

# Add string.h to files that need it
echo "Step 1: Adding #include <string.h> to files using strstr..."
for file in "${STRING_FILES[@]}"; do
    if [ -f "$file" ]; then
        # Check if string.h is already included
        if ! grep -q "#include <string.h>" "$file"; then
            echo "  ✅ Adding string.h to $file"
            # Add string.h after stdlib.h if it exists
            if grep -q "#include <stdlib.h>" "$file"; then
                sed -i 's/#include <stdlib.h>/#include <stdlib.h>\n#include <string.h>/' "$file"
            else
                # Add at top after initial comment block
                sed -i '/^#include/i #include <string.h>' "$file"
            fi
        else
            echo "  ⚪ $file already has string.h"
        fi
    else
        echo "  ❌ File not found: $file"
    fi
done

# Add stdio.h to files that need it
echo ""
echo "Step 2: Adding #include <stdio.h> to files using printf functions..."
for file in "${STDIO_FILES[@]}"; do
    if [ -f "$file" ]; then
        # Check if stdio.h is already included
        if ! grep -q "#include <stdio.h>" "$file"; then
            echo "  ✅ Adding stdio.h to $file"
            # Add stdio.h after stdlib.h if it exists
            if grep -q "#include <stdlib.h>" "$file"; then
                sed -i 's/#include <stdlib.h>/#include <stdlib.h>\n#include <stdio.h>/' "$file"
            else
                # Add at top after initial comment block
                sed -i '/^#include/i #include <stdio.h>' "$file"
            fi
        else
            echo "  ⚪ $file already has stdio.h"
        fi
    else
        echo "  ❌ File not found: $file"
    fi
done

# Add final newlines to all AST files
echo ""
echo "Step 3: Adding final newlines to all AST files..."
find src/ast/ -name "*.c" | while read file; do
    # Check if file ends with newline
    if [ -n "$(tail -c1 "$file")" ]; then
        echo "  ✅ Adding newline to $file"
        echo "" >> "$file"
    fi
done

echo ""
echo "🎉 Header dependency fix complete!"
echo "Next: Run build test to verify fixes"