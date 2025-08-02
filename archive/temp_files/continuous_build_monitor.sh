#!/bin/bash
# Continuous Build Monitor - Systems Engineer
echo "=== CONTINUOUS BUILD MONITORING FOR LARGE CODEBASE ==="
echo "Supporting Developer's rapid fixes..."
echo

while true; do
    # Quick build test
    echo -n "$(date +%H:%M:%S) - Testing build... "
    
    # Run make and capture percentage
    BUILD_OUTPUT=$(cd /data/data/com.termux/files/home/xmd/build && make -j4 2>&1)
    LAST_PERCENT=$(echo "$BUILD_OUTPUT" | grep -oE '\[[0-9]+%\]' | tail -1 | tr -d '[]%')
    ERROR_COUNT=$(echo "$BUILD_OUTPUT" | grep -c "error:")
    
    if [ -n "$LAST_PERCENT" ]; then
        echo "Progress: ${LAST_PERCENT}% | Errors: $ERROR_COUNT"
        
        # Show first error if any
        if [ $ERROR_COUNT -gt 0 ]; then
            echo "  First error:"
            echo "$BUILD_OUTPUT" | grep -A2 "error:" | head -3 | sed 's/^/    /'
        fi
    else
        echo "Build configuration issue"
    fi
    
    # Check recent file changes
    RECENT_COUNT=$(find /data/data/com.termux/files/home/xmd/src -name "*.c" -mmin -2 -type f | wc -l)
    if [ $RECENT_COUNT -gt 0 ]; then
        echo "  Files modified in last 2 min: $RECENT_COUNT"
    fi
    
    sleep 10
done