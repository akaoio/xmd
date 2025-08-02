#!/bin/bash
# Genesis Specification Compliance Test
# Tests exact examples from Genesis leader specification

echo "============================================"
echo "GENESIS SPECIFICATION COMPLIANCE TEST"
echo "Testing exact Genesis language examples"
echo "============================================"
echo ""

# Test configuration
TEST_DIR="test_infrastructure/genesis_tests"
mkdir -p $TEST_DIR

# Test counters
TESTS_PASSED=0
TESTS_FAILED=0

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to run a test
run_genesis_test() {
    local test_name="$1"
    local test_file="$2"
    local expected_output="$3"
    local should_error="$4"
    
    echo -n "Testing $test_name... "
    
    # Run XMD on test file
    actual_output=$(./build/xmd process "$test_file" 2>&1)
    exit_code=$?
    
    if [ "$should_error" = "true" ]; then
        # Test should produce error
        if [ $exit_code -ne 0 ] || echo "$actual_output" | grep -qi "error"; then
            echo -e "${GREEN}✅ PASSED (correctly rejected)${NC}"
            ((TESTS_PASSED++))
        else
            echo -e "${RED}❌ FAILED (should have errored)${NC}"
            echo "  Expected: Error"
            echo "  Actual:   $actual_output"
            ((TESTS_FAILED++))
        fi
    else
        # Test should succeed
        if [ "$actual_output" = "$expected_output" ]; then
            echo -e "${GREEN}✅ PASSED${NC}"
            ((TESTS_PASSED++))
        else
            echo -e "${RED}❌ FAILED${NC}"
            echo "  Expected: $expected_output"
            echo "  Actual:   $actual_output"
            ((TESTS_FAILED++))
        fi
    fi
}

echo "Testing Genesis specification compliance..."
echo ""

# SECTION 1: CORRECT SYNTAX TESTS
echo "=========================================="
echo "SECTION 1: Correct Genesis Syntax"
echo "=========================================="

# Test 1.1: Genesis assignment example
cat > $TEST_DIR/genesis_assignment.xmd << 'EOF'
set score 95
{{score}}
EOF
run_genesis_test "Genesis assignment syntax" "$TEST_DIR/genesis_assignment.xmd" "95"

# Test 1.2: Genesis comparison example
cat > $TEST_DIR/genesis_comparison.xmd << 'EOF'
set score 100
if score = 100
    Perfect
endif
EOF
run_genesis_test "Genesis comparison syntax" "$TEST_DIR/genesis_comparison.xmd" "Perfect"

# Test 1.3: Genesis exact "Wowww" example
cat > $TEST_DIR/genesis_wowww.xmd << 'EOF'
set score 100
if score = 100 then print "Wowww"
EOF
run_genesis_test "Genesis Wowww example" "$TEST_DIR/genesis_wowww.xmd" "Wowww" # Will likely fail until print/then implemented

# Test 1.4: Genesis loop break example
cat > $TEST_DIR/genesis_break.xmd << 'EOF'
for i in 1..5
    if i = 4 then break
    Item {{i}}
endfor
EOF
run_genesis_test "Genesis loop break" "$TEST_DIR/genesis_break.xmd" "Item 1\nItem 2\nItem 3" # Will fail until loops implemented

# Test 1.5: Genesis ternary example
cat > $TEST_DIR/genesis_ternary.xmd << 'EOF'
set age 20
set result age >= 18 ? "adult" : "minor"
{{result}}
EOF
run_genesis_test "Genesis ternary operator" "$TEST_DIR/genesis_ternary.xmd" "adult" # Will fail until ternary implemented

# SECTION 2: WRONG SYNTAX TESTS (SHOULD FAIL)
echo ""
echo "=========================================="
echo "SECTION 2: Wrong Syntax (Should Reject)"
echo "=========================================="

# Test 2.1: Wrong assignment syntax
cat > $TEST_DIR/wrong_assignment.xmd << 'EOF'
score = 100
{{score}}
EOF
run_genesis_test "Wrong assignment (score = 100)" "$TEST_DIR/wrong_assignment.xmd" "" true

# Test 2.2: Wrong set syntax
cat > $TEST_DIR/wrong_set.xmd << 'EOF'
set score = 100
{{score}}
EOF
run_genesis_test "Wrong set syntax (set score = 100)" "$TEST_DIR/wrong_set.xmd" "" true

# Test 2.3: Wrong comparison operator
cat > $TEST_DIR/wrong_comparison.xmd << 'EOF'
set score 100
if score == 100
    Wrong
endif
EOF
run_genesis_test "Wrong comparison (==)" "$TEST_DIR/wrong_comparison.xmd" "" true

# Test 2.4: Wrong equality syntax
cat > $TEST_DIR/wrong_equality.xmd << 'EOF'
set score 100
if score === 100
    Wrong
endif
EOF
run_genesis_test "Wrong equality (===)" "$TEST_DIR/wrong_equality.xmd" "" true

# SECTION 3: GENESIS SPECIFICATION EDGE CASES
echo ""
echo "=========================================="
echo "SECTION 3: Genesis Edge Cases"
echo "=========================================="

# Test 3.1: Multiple assignments
cat > $TEST_DIR/multiple_assignments.xmd << 'EOF'
set a 1
set b 2
set c 3
if a = 1
    if b = 2
        if c = 3
            All correct
        endif
    endif
endif
EOF
run_genesis_test "Multiple assignments and comparisons" "$TEST_DIR/multiple_assignments.xmd" "All correct"

# Test 3.2: Comparison with strings
cat > $TEST_DIR/string_comparison.xmd << 'EOF'
set name "Genesis"
if name = "Genesis"
    Correct name
endif
EOF
run_genesis_test "String comparison" "$TEST_DIR/string_comparison.xmd" "Correct name"

# Test 3.3: Comparison with variables
cat > $TEST_DIR/variable_comparison.xmd << 'EOF'
set x 5
set y 5
if x = y
    Variables equal
endif
EOF
run_genesis_test "Variable comparison" "$TEST_DIR/variable_comparison.xmd" "Variables equal"

# SUMMARY
echo ""
echo "============================================"
echo "GENESIS COMPLIANCE SUMMARY"
echo "============================================"
echo -e "Tests Passed:  ${GREEN}$TESTS_PASSED${NC}"
echo -e "Tests Failed:  ${RED}$TESTS_FAILED${NC}"
echo -e "Total Tests:   $((TESTS_PASSED + TESTS_FAILED))"
echo ""

# Calculate compliance percentage
if [ $((TESTS_PASSED + TESTS_FAILED)) -gt 0 ]; then
    COMPLIANCE=$((TESTS_PASSED * 100 / (TESTS_PASSED + TESTS_FAILED)))
    echo "Genesis Compliance: $COMPLIANCE%"
else
    echo "Genesis Compliance: 0%"
fi

echo ""

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 FULL GENESIS COMPLIANCE ACHIEVED!${NC}"
    echo "All Genesis specification examples work correctly."
    exit 0
else
    echo -e "${RED}❌ Genesis compliance issues found.${NC}"
    echo "Please fix failing tests to achieve full Genesis compliance."
    
    # Show specific guidance
    echo ""
    echo "Remember Genesis specification:"
    echo "  ✅ Assignment: set name \"value\""
    echo "  ✅ Comparison: if name = \"value\""
    echo "  ❌ Wrong: name = \"value\""
    echo "  ❌ Wrong: if name == \"value\""
    
    exit 1
fi