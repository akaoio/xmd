#!/bin/bash
# Build Status Verification - Immediate accurate status reporting
# DevOps assignment: Report actual compilation status (verified, not claimed)

echo "========================================"
echo "🔍 BUILD STATUS VERIFICATION"
echo "DevOps verified status report"
echo "========================================"

timestamp=$(date '+%Y-%m-%d %H:%M:%S')
echo "Verification Time: $timestamp"
echo ""

# Clear, rebuild to ensure accurate status
echo "🔄 PERFORMING CLEAN BUILD FOR ACCURATE STATUS..."
cmake --build build --target clean >/dev/null 2>&1

# Build and capture everything
build_output=$(cmake --build build 2>&1)
build_exit_code=$?

# Detailed analysis
error_count=$(echo "$build_output" | grep -c "error:" 2>/dev/null || echo 0)
warning_count=$(echo "$build_output" | grep -c "warning:" 2>/dev/null || echo 0)
binary_exists=$([ -f "build/xmd" ] && echo "YES" || echo "NO")

echo "📊 VERIFIED BUILD STATUS REPORT"
echo "==============================="
echo "Build Exit Code: $build_exit_code"
echo "Compilation Errors: $error_count"
echo "Compilation Warnings: $warning_count"
echo "Binary Created: $binary_exists"

if [ -f "build/xmd" ]; then
    binary_size=$(ls -lh build/xmd | awk '{print $5}')
    echo "Binary Size: $binary_size"
fi

echo ""

# Status interpretation
if [ $build_exit_code -eq 0 ] && [ $error_count -eq 0 ]; then
    echo "✅ BUILD STATUS: SUCCESS"
    echo "✅ VERIFICATION: Build claims are ACCURATE"
    echo "✅ READY FOR: Phase development can proceed"
    
    # Test functionality if binary exists
    if [ -f "build/xmd" ]; then
        echo ""
        echo "🧪 FUNCTIONALITY VERIFICATION:"
        version_output=$(./build/xmd --version 2>&1)
        version_exit_code=$?
        
        if [ $version_exit_code -eq 0 ]; then
            echo "✅ Basic functionality: WORKING"
            echo "Version: $(echo "$version_output" | head -1)"
        else
            echo "❌ Basic functionality: BROKEN"
            echo "Error: $version_output"
        fi
    fi
    
elif [ $build_exit_code -ne 0 ] || [ $error_count -gt 0 ]; then
    echo "❌ BUILD STATUS: FAILED"
    echo "❌ VERIFICATION: Any success claims are FALSE"
    echo "❌ BLOCKING: All phase development blocked"
    
    echo ""
    echo "🚨 CRITICAL ERRORS (Top 5):"
    echo "$build_output" | grep "error:" | head -5 | nl -v1 -w2 -s'. '
    
    echo ""
    echo "📋 SPECIFIC ISSUES FOR DEVELOPER2:"
    
    # Analyze error types
    if echo "$build_output" | grep -q "undeclared function"; then
        echo "- Missing function implementations needed"
        echo "- Functions called but not defined"
    fi
    
    if echo "$build_output" | grep -q "redefinition"; then
        echo "- Duplicate function definitions to remove"
        echo "- Violates Genesis 'single source of truth'"
    fi
    
    if echo "$build_output" | grep -q "conflicting types"; then
        echo "- Function signature mismatches to fix"
        echo "- Header/implementation inconsistencies"
    fi
    
    if echo "$build_output" | grep -q "no member named"; then
        echo "- Struct member issues to resolve"
        echo "- Missing fields in data structures"
    fi
fi

echo ""
echo "🎯 PHASE READINESS STATUS:"
if [ $build_exit_code -eq 0 ] && [ $error_count -eq 0 ]; then
    echo "Phase 1 (Functions & Classes): ✅ Ready"
    echo "Phase 2 (Data Types): ✅ Ready"  
    echo "Phase 3 (I/O & Modules): ✅ Ready"
else
    echo "Phase 1 (Functions & Classes): ❌ Blocked"
    echo "Phase 2 (Data Types): ❌ Blocked"
    echo "Phase 3 (I/O & Modules): ❌ Blocked"
fi

echo ""
echo "📝 DEVOPS ACCOUNTABILITY:"
echo "- Status verified by actual compilation attempt"
echo "- No false claims or assumptions made"
echo "- Report based on measurable results only"

# Save status to file for team reference
status_file="test_infrastructure/logs/verified_build_status_$(date +%Y%m%d_%H%M%S).txt"
echo "Saving detailed status to: $status_file"

cat > $status_file << EOF
XMD BUILD STATUS VERIFICATION REPORT
====================================
Timestamp: $timestamp
DevOps Verified: ACTUAL compilation status

Build Results:
- Exit Code: $build_exit_code
- Errors: $error_count  
- Warnings: $warning_count
- Binary: $binary_exists

Status: $([ $build_exit_code -eq 0 ] && [ $error_count -eq 0 ] && echo "SUCCESS" || echo "FAILED")

Phase Readiness: $([ $build_exit_code -eq 0 ] && [ $error_count -eq 0 ] && echo "ALL PHASES READY" || echo "ALL PHASES BLOCKED")

EOF

if [ $error_count -gt 0 ]; then
    echo "" >> $status_file
    echo "Critical Errors:" >> $status_file
    echo "$build_output" | grep "error:" | head -10 >> $status_file
fi

echo ""
exit $build_exit_code