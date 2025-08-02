#!/bin/bash
# XMD Evaluation Engine Test Runner
# Tests progression from parsing to evaluation completion

echo "========================================"
echo "XMD EVALUATION ENGINE TEST SUITE"
echo "Testing evaluation engine completion"
echo "========================================"

# Test directory
TEST_DIR="test_infrastructure/evaluation_tests"
mkdir -p $TEST_DIR

# Test counters
PARSING_PASSED=0
PARSING_FAILED=0
EVALUATION_WORKING=0
EVALUATION_PENDING=0

# Function to test parsing (system doesn't crash)
test_parsing() {
    local test_name="$1"
    local test_file="$2"
    
    echo -n "Testing $test_name (parsing)... "
    
    # Run XMD on test file, capture both stdout and stderr
    actual_output=$(./build/xmd process "$test_file" 2>&1)
    exit_code=$?
    
    # Check if it didn't crash (no segfault, no abort)
    if [[ $exit_code -eq 0 && "$actual_output" != *"Aborted"* && "$actual_output" != *"Segmentation fault"* ]]; then
        echo "✅ PASSED - Syntax parsing works"
        ((PARSING_PASSED++))
        return 0
    else
        echo "❌ FAILED - Parsing broken"
        echo "  Output: $actual_output"
        echo "  Exit code: $exit_code"
        ((PARSING_FAILED++))
        return 1
    fi
}

# Function to test evaluation completion
test_evaluation() {
    local test_name="$1"
    local test_file="$2"
    local expected_clean_output="$3"
    
    echo -n "Testing $test_name (evaluation)... "
    
    # Run XMD and extract only the content output (remove debug lines)
    raw_output=$(./build/xmd process "$test_file" 2>&1)
    # Remove DEBUG lines and the "true" prefix from assignments
    clean_output=$(echo "$raw_output" | grep -v "DEBUG:" | sed 's/^true//' | sed 's/^[[:space:]]*//' | tr -d '\n')
    
    if [ "$clean_output" = "$expected_clean_output" ]; then
        echo "✅ PASSED - Evaluation engine working!"
        ((EVALUATION_WORKING++))
        return 0
    else
        echo "⚠️  PENDING - Evaluation engine not yet complete"
        echo "  Current output: '$clean_output'"
        echo "  Expected output: '$expected_clean_output'"
        echo "  Raw output: $raw_output"
        ((EVALUATION_PENDING++))
        return 1
    fi
}

echo ""
echo "PHASE 1: Basic Variable Operations"
echo "---------------------------------"

# Test 1: Simple variable assignment and substitution
cat > $TEST_DIR/variable_basic.xmd << 'EOF'
set name "Genesis"
{{name}}
EOF

test_parsing "Variable Assignment" "$TEST_DIR/variable_basic.xmd"
test_evaluation "Variable Assignment" "$TEST_DIR/variable_basic.xmd" "Genesis"

echo ""
echo "PHASE 2: Mathematical Expression Evaluation"
echo "------------------------------------------"

# Test 2: Basic arithmetic
cat > $TEST_DIR/math_basic.xmd << 'EOF'
set result 2 + 3
{{result}}
EOF

test_parsing "Math Basic Addition" "$TEST_DIR/math_basic.xmd"
test_evaluation "Math Basic Addition" "$TEST_DIR/math_basic.xmd" "5"

# Test 3: Multiple operations
cat > $TEST_DIR/math_complex.xmd << 'EOF'
set x 10
set y 5
set sum x + y
set diff x - y
set prod x * y
Sum: {{sum}}, Diff: {{diff}}, Product: {{prod}}
EOF

test_parsing "Math Complex Operations" "$TEST_DIR/math_complex.xmd"
test_evaluation "Math Complex Operations" "$TEST_DIR/math_complex.xmd" "Sum: 15, Diff: 5, Product: 50"

echo ""
echo "PHASE 3: Conditional Logic Evaluation"
echo "------------------------------------"

# Test 4: Simple if statement (Genesis syntax with =)
cat > $TEST_DIR/conditional_simple.xmd << 'EOF'
set score 100
if score = 100
    Perfect score!
endif
EOF

test_parsing "Conditional Simple If" "$TEST_DIR/conditional_simple.xmd"
test_evaluation "Conditional Simple If" "$TEST_DIR/conditional_simple.xmd" "Perfect score!"

# Test 5: If-else statement
cat > $TEST_DIR/conditional_ifelse.xmd << 'EOF'
set score 85
if score = 100
    Perfect!
else
    Good job!
endif
EOF

test_parsing "Conditional If-Else" "$TEST_DIR/conditional_ifelse.xmd"
test_evaluation "Conditional If-Else" "$TEST_DIR/conditional_ifelse.xmd" "Good job!"

# Test 6: Genesis example from specification
cat > $TEST_DIR/genesis_example.xmd << 'EOF'
set score 100
if score = 100 then print "Wowww"
EOF

test_parsing "Genesis Example" "$TEST_DIR/genesis_example.xmd"
test_evaluation "Genesis Example" "$TEST_DIR/genesis_example.xmd" "Wowww"

echo ""
echo "PHASE 4: Advanced Expression Evaluation"
echo "--------------------------------------"

# Test 7: Variable-to-variable comparison
cat > $TEST_DIR/variable_comparison.xmd << 'EOF'
set x 5
set y 5
if x = y
    Variables are equal
else
    Variables are different
endif
EOF

test_parsing "Variable Comparison" "$TEST_DIR/variable_comparison.xmd"
test_evaluation "Variable Comparison" "$TEST_DIR/variable_comparison.xmd" "Variables are equal"

# Test 8: Nested expressions
cat > $TEST_DIR/nested_expressions.xmd << 'EOF'
set a 3
set b 4
set c a + b * 2
Result: {{c}}
EOF

test_parsing "Nested Expressions" "$TEST_DIR/nested_expressions.xmd"
test_evaluation "Nested Expressions" "$TEST_DIR/nested_expressions.xmd" "Result: 11"

echo ""
echo "========================================"
echo "EVALUATION ENGINE TEST SUMMARY"
echo "========================================"
echo "Parsing Tests:"
echo "  ✅ Passed: $PARSING_PASSED"
echo "  ❌ Failed: $PARSING_FAILED"
echo ""
echo "Evaluation Tests:"
echo "  ✅ Working: $EVALUATION_WORKING" 
echo "  ⚠️  Pending: $EVALUATION_PENDING"
echo ""

# Calculate completion percentage
total_evaluation_tests=$((EVALUATION_WORKING + EVALUATION_PENDING))
if [ $total_evaluation_tests -gt 0 ]; then
    completion_percent=$((EVALUATION_WORKING * 100 / total_evaluation_tests))
    echo "Evaluation Engine Completion: $completion_percent%"
else
    echo "Evaluation Engine Completion: 0%"
fi

echo ""
echo "STATUS INTERPRETATION:"
echo "----------------------"
if [ $PARSING_FAILED -eq 0 ]; then
    echo "✅ PARSING: All syntax recognition working - AST parser operational"
else
    echo "❌ PARSING: Some syntax parsing broken - AST parser needs fixes"
fi

if [ $EVALUATION_WORKING -eq $total_evaluation_tests ] && [ $total_evaluation_tests -gt 0 ]; then
    echo "✅ EVALUATION: All evaluation tests passing - evaluation engine complete!"
elif [ $EVALUATION_WORKING -gt 0 ]; then
    echo "⚠️  EVALUATION: Partial evaluation working - evaluation engine in progress"
else
    echo "❌ EVALUATION: No evaluation working - evaluation engine needs implementation"
fi

echo ""
echo "NEXT STEPS FOR DEVELOPERS:"
echo "-------------------------"
if [ $PARSING_FAILED -gt 0 ]; then
    echo "1. Fix AST parser syntax recognition issues"
fi
if [ $EVALUATION_PENDING -gt 0 ]; then
    echo "2. Complete evaluation engine in ast_evaluate() function"
    echo "3. Fix mathematical expression computation"
    echo "4. Fix conditional execution (if/then/else)"
    echo "5. Remove 'true' prefix from assignment outputs"
fi

echo ""
if [ $PARSING_FAILED -eq 0 ] && [ $EVALUATION_WORKING -eq $total_evaluation_tests ]; then
    echo "🎉 EVALUATION ENGINE COMPLETE! Ready for advanced features!"
    exit 0
else
    echo "🔧 EVALUATION ENGINE NEEDS WORK - See results above"
    exit 1
fi