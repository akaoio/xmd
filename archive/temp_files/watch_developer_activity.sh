#!/bin/bash
# WATCH DEVELOPER ACTIVITY - Continuous monitoring
echo "=== DEVELOPER ACTIVITY MONITORING ==="
echo "Watching for file modifications and verifying quality..."

cd /data/data/com.termux/files/home/xmd

# Get baseline file modification times
BASELINE_DIR="/tmp/baseline_$$"
mkdir -p "$BASELINE_DIR"

echo "📋 Recording baseline file states..."
find src/ast src/misc -name "*.c" -exec stat -c "%Y %n" {} \; > "$BASELINE_DIR/initial_state.txt"

echo "👁️  MONITORING DEVELOPER FILE CHANGES:"
echo "Press Ctrl+C to stop monitoring"
echo

MONITOR_COUNT=0
while true; do
    ((MONITOR_COUNT++))
    
    # Check for modified files
    MODIFIED_FILES=$(find src/ast src/misc -name "*.c" -newer "$BASELINE_DIR/initial_state.txt" 2>/dev/null)
    
    if [ -n "$MODIFIED_FILES" ]; then
        echo "⚠️  FILE MODIFICATION DETECTED ($MONITOR_COUNT):"
        for file in $MODIFIED_FILES; do
            echo "   Modified: $file"
            
            # Immediate verification
            echo -n "   Quick test: "
            if gcc -c -Iinclude "$file" -o /tmp/monitor_$$.o 2>/dev/null; then
                echo "✅ Compiles"
                rm -f /tmp/monitor_$$.o
            else
                echo "❌ Compilation error"
            fi
        done
        
        # Update baseline
        find src/ast src/misc -name "*.c" -exec stat -c "%Y %n" {} \; > "$BASELINE_DIR/initial_state.txt"
        echo
    fi
    
    sleep 10
done

# Cleanup
rm -rf "$BASELINE_DIR"