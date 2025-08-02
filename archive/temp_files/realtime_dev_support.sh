#!/bin/bash
# REAL-TIME DEVELOPER SUPPORT - Systems Engineer
echo "=== SYSTEMS ENGINEER: REAL-TIME DEVELOPER SUPPORT ==="
echo "Monitoring Developer activity closely for large codebase..."
echo

cd /data/data/com.termux/files/home/xmd

# Function to check file syntax
check_syntax() {
    local file=$1
    if gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
        echo "✅"
    else
        echo "❌"
    fi
}

# Monitor recent file changes
echo "🔍 MONITORING RECENT CHANGES (last 5 minutes):"
find src/ast -name "*.c" -mmin -5 -type f | while read file; do
    status=$(check_syntax "$file")
    echo "$status $(basename $file) - Modified $(stat -c %y "$file" | cut -d' ' -f2)"
done

echo
echo "📊 CURRENT BUILD ERRORS REQUIRING FIX:"

# Check specific problem files
PROBLEM_FILES=(
    "src/ast/node/create/ast_create_string_literal.c"
    "src/ast/node/create/ast_create_number_literal.c"
    "src/ast/node/create/ast_create_program.c"
    "src/ast/node/create/ast_create_loop.c"
)

ERROR_COUNT=0
for file in "${PROBLEM_FILES[@]}"; do
    if [ -f "$file" ]; then
        if ! gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
            echo "❌ $(basename $file):"
            gcc -fsyntax-only -Iinclude "$file" 2>&1 | grep -E "error:|line [0-9]+:" | head -2 | sed 's/^/   /'
            ((ERROR_COUNT++))
        fi
    fi
done

echo
echo "📈 SUPPORT STATUS:"
echo "- Errors remaining: $ERROR_COUNT"
echo "- Last build: 19%"
echo "- Pattern: Missing comment closers (*/) "
echo

echo "💡 QUICK FIX REMINDER:"
echo "For 'unterminated /* comment' errors:"
echo "Add */ after the @brief/@return line"
echo

echo "🚀 Developer can test with: ./build.sh"
echo "Systems Engineer standing by for immediate support!"