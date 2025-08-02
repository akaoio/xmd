#!/bin/bash
# EMERGENCY XMD SAFETY TESTING SCRIPT
# Prevents Node.js crashes from infinite output
# Created by Systems Engineer for team safety

TIMEOUT_SECONDS=5
OUTPUT_LIMIT=1000  
XMD_BINARY="./build/xmd"

# Check if XMD binary exists
if [ ! -f "$XMD_BINARY" ]; then
    echo "ERROR: XMD binary not found at $XMD_BINARY"
    echo "Please run ./build.sh first to create the binary"
    exit 1
fi

# Check if test file provided
if [ $# -eq 0 ]; then
    echo "USAGE: $0 <test_file.xmd>"
    echo "SAFETY: This script prevents infinite loops and output overflow"
    echo "LIMITS: ${TIMEOUT_SECONDS}s timeout, ${OUTPUT_LIMIT} lines max output"
    exit 1
fi

TEST_FILE="$1"

# Check if test file exists
if [ ! -f "$TEST_FILE" ]; then
    echo "ERROR: Test file '$TEST_FILE' not found"
    exit 1
fi

echo "🛡️  SAFE XMD TESTING - $(date)"
echo "📁 File: $TEST_FILE"
echo "⏱️  Timeout: ${TIMEOUT_SECONDS}s"
echo "📊 Output limit: ${OUTPUT_LIMIT} lines"
echo "🚨 Emergency safety measures active"
echo "----------------------------------------"

# Safety wrapper with timeout and output limits
timeout ${TIMEOUT_SECONDS}s ${XMD_BINARY} process "$TEST_FILE" 2>&1 | head -${OUTPUT_LIMIT}
EXIT_CODE=$?

echo "----------------------------------------"

# Check exit status and provide feedback
if [ $EXIT_CODE -eq 124 ]; then
    echo "🚨 ERROR: XMD test TIMED OUT after ${TIMEOUT_SECONDS} seconds"
    echo "❌ Possible infinite loop detected - Node.js crash prevented"
    echo "🛡️  System safety measures activated successfully"
    exit 1
elif [ $EXIT_CODE -eq 0 ]; then
    echo "✅ XMD test completed successfully within safety limits"
    echo "🛡️  No infinite loops or crashes detected"
    exit 0
else
    echo "⚠️  XMD test completed with exit code: $EXIT_CODE"
    echo "🛡️  System safety maintained"
    exit $EXIT_CODE
fi