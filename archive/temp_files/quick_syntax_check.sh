#!/bin/bash
# Quick syntax check for AST files
echo "Testing C syntax errors in AST files..."

# Test a few sample files
TEST_FILES=(
    "src/ast/parser/statement/ast_parse_statement.c"
    "src/ast/evaluator/assignment/ast_evaluate_assignment.c" 
    "src/ast/node/create/ast_create_program.c"
)

for file in "${TEST_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo -n "Testing $file: "
        if gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
            echo "✅ OK"
        else
            echo "❌ SYNTAX ERROR"
            gcc -fsyntax-only -Iinclude "$file" 2>&1 | head -2
        fi
    fi
done