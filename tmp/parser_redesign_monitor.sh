#!/bin/bash
# Parser Redesign Monitor - DevOps Support Tool
# Monitors parser changes and build stability during emergency redesign

echo "🚨 PARSER REDESIGN MONITOR - DevOps Support Tool"
echo "================================================"
echo "Monitoring parser changes for Genesis compliance"
echo ""

# Key files to monitor for parser changes
PARSER_FILES=(
    "src/ast_consolidated.c"
    "src/native_xmd_consolidated.c"
    "src/lexer_consolidated.c"
    "src/parser_utils.c"
)

# Function to check build status
check_build() {
    echo "🔧 Checking build status..."
    if ./build.sh >/dev/null 2>&1; then
        echo "✅ Build SUCCESS - No compilation errors"
        return 0
    else
        echo "❌ Build FAILED - Parser changes broke compilation"
        return 1
    fi
}

# Function to check parser syntax compliance
check_genesis_syntax() {
    echo ""
    echo "📋 Checking Genesis syntax compliance..."
    
    # Check for parentheses in function calls (WRONG)
    if grep -r "File\.read(" src/ 2>/dev/null | grep -v "// WRONG" > /dev/null; then
        echo "❌ VIOLATION: Found File.read() with parentheses - Should be File.read \"path\""
    fi
    
    if grep -r "greet(" src/ 2>/dev/null | grep -v "// WRONG" > /dev/null; then
        echo "❌ VIOLATION: Found function calls with parentheses - Should be space-separated"
    fi
    
    # Check for correct patterns
    echo ""
    echo "🎯 Looking for correct Genesis patterns:"
    echo "- set a 1, b 2 → Multiple variable assignment"
    echo "- set user name \"Alice\", age 30 → Object creation"
    echo "- set scores 1, 2, 3 → Array creation"
    echo "- File.read \"path\" → NO parentheses"
}

# Monitor loop
echo ""
echo "Starting continuous monitoring..."
echo "Press Ctrl+C to stop"
echo ""

LAST_HASH=""
while true; do
    # Get current state hash
    CURRENT_HASH=$(find src/ -name "*.c" -exec md5sum {} \; | sort | md5sum | cut -d' ' -f1)
    
    if [ "$CURRENT_HASH" != "$LAST_HASH" ]; then
        echo ""
        echo "🔄 Parser files changed! Checking status..."
        echo "Time: $(date '+%Y-%m-%d %H:%M:%S')"
        echo "----------------------------------------"
        
        # Check build
        if check_build; then
            # Check syntax compliance
            check_genesis_syntax
            
            # Show parser redesign priorities
            echo ""
            echo "📊 Parser Redesign Priorities:"
            echo "1. NO PARENTHESES in function/method calls"
            echo "2. Disambiguate three comma patterns:"
            echo "   - identifier value, identifier value → Multiple vars"
            echo "   - identifier key value, key value → Object"
            echo "   - identifier value, value, value → Array"
            echo "3. Complete architectural redesign needed"
        fi
        
        LAST_HASH="$CURRENT_HASH"
    fi
    
    # Brief status every 30 seconds
    echo -n "."
    sleep 5
done