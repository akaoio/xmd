#!/bin/bash

echo "=== Testing XMD Watch Nested Import Fix ==="
echo

# Start watch in background
echo "Starting watch command..."
./build/xmd watch teamwork --verbose &
WATCH_PID=$!

# Give watch time to start
sleep 2

echo
echo "Initial state - checking dashboard output:"
echo "========================================="
./build/xmd process teamwork/index/dashboard.md

echo
echo "Now updating core/update/comment.md..."
echo "# Core Comment" > teamwork/core/update/comment.md
echo "This is the UPDATED comment content - it should appear in dashboard!" >> teamwork/core/update/comment.md

# Give watch time to detect and process
sleep 2

echo
echo "After update - checking dashboard output:"
echo "========================================="
./build/xmd process teamwork/index/dashboard.md

# Kill watch process
kill $WATCH_PID 2>/dev/null

echo
echo "Test complete!"