#!/bin/bash
# System Health Monitor for XMD Project
# DevOps continuous monitoring during bug fix phase

echo "=== XMD SYSTEM HEALTH CHECK ==="
echo "Date: $(date)"
echo ""

# Build Status
echo "## BUILD STATUS ##"
if ./build.sh > /dev/null 2>&1; then
    echo "✅ Build: SUCCESS"
    SIZE=$(stat -c%s build/xmd 2>/dev/null || stat -f%z build/xmd 2>/dev/null)
    echo "   Binary size: $SIZE bytes"
else
    echo "❌ Build: FAILED"
fi

# Test Feature Status
echo ""
echo "## FEATURE STATUS (Based on Tester Reports) ##"
echo "✅ File I/O: 100% working (all 5 operations)"
echo "✅ Variables: Storage and substitution working"
echo "✅ Math: Basic expressions (2 + 3 = 5) working"
echo "✅ Functions: Parse and call (NO PARENTHESES)"
echo "✅ Arrays: Creation and display working"
echo ""
echo "❌ Control Flow: NOT EXECUTING (treated as functions)"
echo "❌ String Concat: Broken in functions"
echo "❌ Conditionals: Both branches execute"
echo "❌ Loops: No iteration happening"

# Memory Usage
echo ""
echo "## RESOURCE USAGE ##"
if command -v free >/dev/null 2>&1; then
    echo "Memory:"
    free -h | grep -E "^(Mem|Swap):" | awk '{print "  " $1 " Used: " $3 " / " $2}'
fi

# Recent Changes
echo ""
echo "## RECENT CHANGES ##"
echo "- File I/O integration complete (DevOps)"
echo "- Parser disambiguation implemented (Developer2)"
echo "- Control flow parsing added (Developer)"
echo "- Array display reportedly fixed (Architect)"

# Current Issues
echo ""
echo "## MONITORING FOCUS ##"
echo "1. Control flow execution gap"
echo "2. String concatenation bug"
echo "3. Developer2 health concerns"
echo "4. Array element access missing"

echo ""
echo "=== END HEALTH CHECK ==="