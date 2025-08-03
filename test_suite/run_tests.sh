#!/bin/bash
# XMD Runtime Test Suite Runner
# Executes all test files and captures results

XMD_BIN="../build-tester/xmd"
TEST_DIR="."
RESULTS_FILE="test_results.md"

echo "# XMD Runtime Test Results" > $RESULTS_FILE
echo "Date: $(date)" >> $RESULTS_FILE
echo "" >> $RESULTS_FILE

# Function to run a test
run_test() {
    local test_file=$1
    local test_name=$(basename $test_file .xmd)
    
    echo "Running test: $test_name"
    echo "## Test: $test_name" >> $RESULTS_FILE
    echo '```' >> $RESULTS_FILE
    
    # Run test and capture both stdout and stderr
    $XMD_BIN process $test_file >> $RESULTS_FILE 2>&1
    local exit_code=$?
    
    echo '```' >> $RESULTS_FILE
    
    if [ $exit_code -eq 0 ]; then
        echo "✅ Status: SUCCESS (exit code: $exit_code)" >> $RESULTS_FILE
    else
        echo "❌ Status: FAILED (exit code: $exit_code)" >> $RESULTS_FILE
    fi
    
    echo "" >> $RESULTS_FILE
}

# Run all tests
for test_file in $TEST_DIR/test_*.xmd; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

echo "## Summary" >> $RESULTS_FILE
echo "" >> $RESULTS_FILE

# Count results
total=$(ls -1 test_*.xmd 2>/dev/null | wc -l)
echo "Total tests: $total" >> $RESULTS_FILE

echo ""
echo "Test execution complete. Results saved to $RESULTS_FILE"
cat $RESULTS_FILE