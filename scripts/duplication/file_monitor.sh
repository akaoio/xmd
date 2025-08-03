#!/bin/bash
# File Change Monitor - Zero Duplication Campaign
# Monitors file changes and estimates impact during build-blocked period
# Tester (Duplication Validation Lead)

echo "📂 FILE CHANGE MONITOR - Campaign Active Despite Build Block"
echo "Timestamp: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""

# Track file modification times and sizes
echo "🔍 MONITORING FILE CHANGES:"

# Count current files
CURRENT_FILES=$(find src -name "*.c" -type f | wc -l)
echo "Current C files: $CURRENT_FILES"

# Check for recently modified files (last 10 minutes)
RECENT_CHANGES=$(find src -name "*.c" -type f -mmin -10 | wc -l)
echo "Recently changed files (10 min): $RECENT_CHANGES"

if [ $RECENT_CHANGES -gt 0 ]; then
    echo ""
    echo "📝 RECENT MODIFICATIONS:"
    find src -name "*.c" -type f -mmin -10 -exec ls -la {} \; | while read line; do
        echo "   $line"
    done
fi

# Check for empty files (potential editing in progress)
EMPTY_FILES=$(find src -name "*.c" -type f -size 0 | wc -l)
if [ $EMPTY_FILES -gt 0 ]; then
    echo ""
    echo "⚠️  EMPTY FILES DETECTED (editing in progress): $EMPTY_FILES"
    find src -name "*.c" -type f -size 0 | while read file; do
        echo "   - $file"
    done
fi

# Check for ast_macros.h availability
echo ""
echo "🔧 BUILD BLOCKER STATUS:"
if [ -f "include/ast_macros.h" ]; then
    echo "   ✅ ast_macros.h: EXISTS"
    echo "   📏 File size: $(stat -c%s include/ast_macros.h) bytes"
else
    echo "   ❌ ast_macros.h: MISSING (blocking build)"
fi

# Check for core_macros.h (Leader's work)
if [ -f "include/core_macros.h" ]; then
    echo "   ✅ core_macros.h: EXISTS (Leader's infrastructure work)"
    echo "   📏 File size: $(stat -c%s include/core_macros.h) bytes"
else
    echo "   ❓ core_macros.h: Status unknown"
fi

# Estimate team activity level
echo ""
echo "📊 TEAM ACTIVITY INDICATORS:"
echo "   - Files being actively edited: $EMPTY_FILES"
echo "   - Recent modifications: $RECENT_CHANGES"
echo "   - Total files tracked: $CURRENT_FILES"

# Activity assessment
if [ $RECENT_CHANGES -gt 5 ]; then
    echo "   🔥 HIGH ACTIVITY - Team optimization in progress"
elif [ $RECENT_CHANGES -gt 2 ]; then
    echo "   🟡 MODERATE ACTIVITY - Steady optimization work"
elif [ $RECENT_CHANGES -gt 0 ]; then
    echo "   🟢 LOW ACTIVITY - Some changes detected"
else
    echo "   ⏸️  NO RECENT ACTIVITY - Possibly blocked"
fi

echo ""
echo "⏰ CAMPAIGN STATUS:"
echo "   - Monitoring: ✅ ACTIVE (build-independent tracking)"
echo "   - Build health: 🔴 BLOCKED (waiting for ast_macros.h)"
echo "   - Team coordination: ✅ ACTIVE"
echo "   - Next full measurement: After build restoration"

echo ""
echo "🎯 Standing by for build fix - monitoring continues!"