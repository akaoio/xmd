#!/bin/bash
# CONTINUOUS PROGRESS MONITOR - Supporting active team work
echo "=== CONTINUOUS PROGRESS MONITORING ACTIVE ==="
echo "Tracking systematic C syntax repairs..."

cd /data/data/com.termux/files/home/xmd

while true; do
    clear
    echo "🚀 TEAM PROGRESS MONITOR - $(date '+%H:%M:%S')"
    echo "==========================================="
    
    # Count fixed files (have proper /** comment structure)
    FIXED_AST=$(find src/ast -name "*.c" -exec grep -l "^/\*\*$" {} \; 2>/dev/null | wc -l)
    FIXED_MISC=$(find src/misc -name "*.c" -exec grep -l "^/\*\*$" {} \; 2>/dev/null | wc -l)
    TOTAL_FIXED=$((FIXED_AST + FIXED_MISC))
    
    # Count remaining files (still have error pattern)
    REMAINING_AST=$(find src/ast -name "*.c" -exec grep -l "^ \* @brief" {} \; 2>/dev/null | xargs grep -vl "^/\*\*$" 2>/dev/null | wc -l)
    REMAINING_MISC=$(find src/misc -name "*.c" -exec grep -l "^ \* @brief" {} \; 2>/dev/null | xargs grep -vl "^/\*\*$" 2>/dev/null | wc -l)
    TOTAL_REMAINING=$((REMAINING_AST + REMAINING_MISC))
    
    TOTAL_FILES=$((TOTAL_FIXED + TOTAL_REMAINING))
    PERCENT_COMPLETE=0
    if [ $TOTAL_FILES -gt 0 ]; then
        PERCENT_COMPLETE=$((TOTAL_FIXED * 100 / TOTAL_FILES))
    fi
    
    echo "📊 PROGRESS STATUS:"
    echo "   Fixed Files: $TOTAL_FIXED"
    echo "   Remaining: $TOTAL_REMAINING" 
    echo "   Progress: $PERCENT_COMPLETE% COMPLETE"
    echo
    
    echo "🏆 TEAM STATUS:"
    echo "   Genesis Leader: Monitoring final push"
    echo "   Developer: Systematic repairs active"
    echo "   Systems Engineer: Build validation support"
    echo
    
    if [ $TOTAL_REMAINING -eq 0 ]; then
        echo "🎉 ALL FILES FIXED! MISSION COMPLETE!"
        break
    fi
    
    echo "⏱️  Next update in 30 seconds..."
    sleep 30
done