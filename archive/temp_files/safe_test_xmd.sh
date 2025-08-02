#!/bin/bash
# EMERGENCY XMD SAFETY TESTING SCRIPT - SYSTEMS ENGINEER
# Prevents Node.js crashes from infinite output generation
# Created per Genesis Leader absolute priority directive

# Safety Configuration
TIMEOUT_SECONDS=5           # Maximum execution time  
OUTPUT_LIMIT=1000          # Maximum output lines
XMD_BINARY="./build/xmd"   # XMD executable path

# Verify XMD binary exists
if [ ! -f "$XMD_BINARY" ]; then
    echo "ERROR: XMD binary not found at $XMD_BINARY"
    echo "Please run ./build.sh first to compile XMD"
    exit 1
fi

# Verify input file provided
if [ $# -eq 0 ]; then
    echo "ERROR: No XMD file specified"
    echo "Usage: $0 <test_file.xmd>"
    echo "Example: $0 test_simple.xmd"
    exit 1
fi

TEST_FILE="$1"

# Verify test file exists
if [ ! -f "$TEST_FILE" ]; then
    echo "ERROR: Test file '$TEST_FILE' not found"
    exit 1
fi

echo "🛡️ SAFE XMD TESTING - Systems Engineer Emergency Safety Protocol"
echo "📁 Testing file: $TEST_FILE"
echo "⏱️ Timeout: ${TIMEOUT_SECONDS} seconds"
echo "📄 Output limit: ${OUTPUT_LIMIT} lines"
echo "---"

# Safety wrapper with timeout and output limits
# This prevents infinite loops from overwhelming Node.js
timeout ${TIMEOUT_SECONDS}s ${XMD_BINARY} process "$TEST_FILE" 2>&1 | head -${OUTPUT_LIMIT}

# Capture exit status
EXIT_STATUS=$?

echo "---"

# Check if process was killed by timeout
if [ $EXIT_STATUS -eq 124 ]; then
    echo "🚨 ERROR: XMD test timed out after ${TIMEOUT_SECONDS} seconds"
    echo "⚠️  POSSIBLE INFINITE LOOP DETECTED"
    echo "🛡️ Safety system prevented Node.js crash"
    exit 124
elif [ $EXIT_STATUS -ne 0 ]; then
    echo "⚠️  XMD process exited with error code: $EXIT_STATUS"
    exit $EXIT_STATUS
else
    echo "✅ XMD test completed safely"
    exit 0
fi