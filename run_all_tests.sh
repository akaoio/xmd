#!/bin/bash

echo "Running all XMD tests..."
echo "========================"

TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

for test_exe in build/test_*; do
    if [[ -x "$test_exe" ]]; then
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        test_name=$(basename "$test_exe")
        echo "Running $test_name..."
        
        if timeout 30 "$test_exe" > /dev/null 2>&1; then
            echo "✅ $test_name PASSED"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo "❌ $test_name FAILED"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
done

echo
echo "========================"
echo "Test Results Summary:"
echo "Total tests: $TOTAL_TESTS"
echo "Passed: $PASSED_TESTS"
echo "Failed: $FAILED_TESTS"

if [[ $FAILED_TESTS -eq 0 ]]; then
    echo "🎉 All tests passed!"
    exit 0
else
    echo "💥 Some tests failed!"
    exit 1
fi