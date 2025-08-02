#!/bin/bash
# Test parser with timeout to catch infinite loops

echo "Testing parser disambiguation with timeout..."
echo 'set a 1, b 2, c 3' > test_infinite.xmd
echo 'print "Variables: a={{a}}, b={{b}}, c={{c}}"' >> test_infinite.xmd

# Run with 5 second timeout
timeout 5s ./build/xmd process test_infinite.xmd

EXIT_CODE=$?
if [ $EXIT_CODE -eq 124 ]; then
    echo "❌ CRITICAL: Parser hit timeout - INFINITE LOOP detected!"
elif [ $EXIT_CODE -eq 0 ]; then
    echo "✅ Parser completed successfully"
else
    echo "⚠️ Parser failed with exit code: $EXIT_CODE"
fi

# Cleanup
rm -f test_infinite.xmd