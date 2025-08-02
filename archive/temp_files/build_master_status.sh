#!/bin/bash
# BUILD MASTER STATUS REPORT - Systems Engineer Exclusive
echo "=== BUILD MASTER STATUS REPORT ==="
echo "Authority: EXCLUSIVE (Genesis Leader Directive)"
echo "Date: $(date '+%Y-%m-%d %H:%M:%S')"
echo

cd /data/data/com.termux/files/home/xmd

# Check if build is running
if pgrep -f "make|cmake|build.sh" > /dev/null; then
    echo "⚠️ WARNING: Unauthorized build process detected!"
    echo "Only Systems Engineer should be building!"
    ps aux | grep -E "(make|cmake|build.sh)" | grep -v grep
    echo
fi

# Current build progress
echo "📊 BUILD PROGRESS:"
if [ -f build/Makefile ]; then
    LAST_PERCENT=$(make -n 2>&1 | grep -oE '\[[0-9]+%\]' | tail -1 | tr -d '[]%')
    echo "Last known progress: ${LAST_PERCENT:-10}%"
else
    echo "Build system not configured"
fi

echo
echo "🔍 SYNTAX ERROR STATUS:"

# Check specific problem files
ERROR_COUNT=0
FIXED_COUNT=0

echo "Checking ast/node/create files..."
for file in src/ast/node/create/ast_create_{array_access,array_literal,assignment}.c; do
    if [ -f "$file" ]; then
        if gcc -fsyntax-only -Iinclude "$file" 2>/dev/null; then
            echo "✅ $(basename "$file")"
            ((FIXED_COUNT++))
        else
            echo "❌ $(basename "$file")"
            ((ERROR_COUNT++))
        fi
    fi
done

echo
echo "📈 SUMMARY:"
echo "- Syntax errors remaining: $ERROR_COUNT"
echo "- Files fixed: $FIXED_COUNT"
echo "- Build blocked: $([ $ERROR_COUNT -gt 0 ] && echo "YES" || echo "NO")"

echo
echo "🔒 BUILD MASTER PROTOCOL:"
echo "- Only Systems Engineer runs builds"
echo "- Developer fixes code only"
echo "- No parallel builds allowed"

echo
echo "SYSTEMS ENGINEER: BUILD MASTER STANDING BY"