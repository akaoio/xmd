#!/bin/bash
# Loop Test Runner for XMD v2.0 - Created by Tester per Leader instructions
# Tests corrected .. syntax after build fixes

echo "================================================"
echo "XMD v2.0 LOOP SYNTAX VALIDATION SUITE"
echo "Testing corrected '..' syntax implementation"
echo "================================================"

# Check if XMD executable exists
if [ ! -f "../xmd" ]; then
    echo "❌ ERROR: XMD executable not found"
    echo "   Please build XMD first: cmake -B build-<name> -S . && cd build-<name> && make"
    exit 1
fi

echo "✅ XMD executable found"
echo ""

# Test cases in order of complexity
test_files=(
    "test_minimal_loop.xmd"
    "test_for.xmd" 
    "test_comprehensive_loops.xmd"
    "test_loops.xmd"
    "test_stress.xmd"
)

passed=0
failed=0

for test_file in "${test_files[@]}"; do
    echo "🧪 Testing: $test_file"
    
    if [ ! -f "$test_file" ]; then
        echo "   ❌ File not found: $test_file"
        ((failed++))
        continue
    fi
    
    # Run test with timeout to handle hanging
    timeout 30s ../xmd process "$test_file" > "${test_file}.output" 2>&1
    exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo "   ✅ PASSED"
        ((passed++))
    elif [ $exit_code -eq 124 ]; then
        echo "   ⏰ TIMEOUT (30s) - likely hanging"
        ((failed++))
    else
        echo "   ❌ FAILED (exit code: $exit_code)"
        ((failed++))
    fi
    
    echo ""
done

echo "================================================"
echo "LOOP SYNTAX TEST RESULTS"
echo "================================================"
echo "✅ Passed: $passed"
echo "❌ Failed: $failed"
echo "📊 Total:  $((passed + failed))"

if [ $failed -eq 0 ]; then
    echo ""
    echo "🎉 ALL LOOP TESTS PASSED!"
    echo "   XMD '..' syntax working correctly!"
else
    echo ""
    echo "⚠️  Some tests failed - see individual .output files"
    echo "   Focus on minimal_loop test for debugging"
fi

echo "================================================"