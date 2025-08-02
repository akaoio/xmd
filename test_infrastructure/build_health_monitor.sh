#!/bin/bash
# Build Health Monitor for Phase Development
# Tracks build stability across development phases

echo "========================================"
echo "XMD BUILD HEALTH MONITOR"
echo "Tracking build stability for phase development"
echo "========================================"

MONITOR_LOG="test_infrastructure/logs/build_health.log"
mkdir -p test_infrastructure/logs

# Initialize log
echo "=== XMD Build Health Monitor Started $(date) ===" >> $MONITOR_LOG

# Build and capture results
echo "Building XMD system..."
build_output=$(cmake --build build 2>&1)
build_exit_code=$?

# Extract error information
error_count=$(echo "$build_output" | grep -c "error:" || echo 0)
warning_count=$(echo "$build_output" | grep -c "warning:" || echo 0)

# Log results
timestamp=$(date '+%Y-%m-%d %H:%M:%S')
echo "[$timestamp] Build Status: Exit=$build_exit_code | Errors=$error_count | Warnings=$warning_count" >> $MONITOR_LOG

echo ""
echo "BUILD HEALTH REPORT"
echo "==================="
echo "Exit Code: $build_exit_code"
echo "Errors: $error_count"
echo "Warnings: $warning_count"
echo ""

if [ $build_exit_code -eq 0 ]; then
    echo "✅ BUILD SUCCESS - System ready for testing!"
    
    # Check if binary exists
    if [ -f "build/xmd" ]; then
        echo "✅ BINARY EXISTS - $(ls -lh build/xmd | awk '{print $5}')"
        
        # Test basic functionality
        echo "Testing basic functionality..."
        version_output=$(./build/xmd --version 2>&1)
        if [ $? -eq 0 ]; then
            echo "✅ BASIC FUNCTIONALITY - Version command works"
            echo "$version_output"
        else
            echo "❌ BASIC FUNCTIONALITY - Version command fails"
            echo "$version_output"
        fi
        
        echo ""
        echo "🚀 PHASE READINESS STATUS:"
        echo "Phase 1 (Functions & Classes): ✅ Build ready"
        echo "Phase 2 (Data Types): ✅ Build ready" 
        echo "Phase 3 (I/O & Modules): ✅ Build ready"
        
    else
        echo "❌ BINARY MISSING - Build succeeded but no executable created"
        echo "Phase readiness: ❌ Not ready"
    fi
    
else
    echo "❌ BUILD FAILED - Compilation errors prevent phase development"
    echo ""
    echo "CRITICAL BUILD ERRORS:"
    echo "====================="
    echo "$build_output" | grep "error:" | head -10
    echo ""
    echo "🚨 PHASE READINESS STATUS:"
    echo "Phase 1 (Functions & Classes): ❌ Build fixes needed"
    echo "Phase 2 (Data Types): ❌ Build fixes needed"
    echo "Phase 3 (I/O & Modules): ❌ Build fixes needed"
    echo ""
    echo "BUILD FIX RECOMMENDATIONS:"
    echo "========================="
    
    # Analyze common build issues
    if echo "$build_output" | grep -q "undeclared function"; then
        echo "- Add missing function declarations to header files"
        echo "- Implement missing function definitions"
    fi
    
    if echo "$build_output" | grep -q "redefinition"; then
        echo "- Remove duplicate function definitions"
        echo "- Ensure single source of truth per Genesis directive"
    fi
    
    if echo "$build_output" | grep -q "conflicting types"; then
        echo "- Fix function signature mismatches"
        echo "- Ensure header declarations match implementations"
    fi
fi

echo ""
echo "DEVELOPER SUPPORT:"
echo "=================="
echo "- Build log: $MONITOR_LOG"
echo "- Architecture docs: PHASE3_IO_MODULES_ARCHITECTURE.md"
echo "- Test infrastructure: test_infrastructure/"
echo ""

if [ $build_exit_code -eq 0 ]; then
    echo "🎉 READY FOR PHASE DEVELOPMENT!"
    exit 0
else
    echo "🔧 BUILD FIXES NEEDED BEFORE PHASE WORK"
    exit 1
fi