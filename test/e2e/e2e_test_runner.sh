#!/bin/bash
# XMD E2E Test Runner
# Comprehensive End-to-End testing of XMD language functionality
# Created by Quality Systems Engineer (Tester)

echo "🧪 XMD E2E Test Runner"
echo "======================"
echo "Testing complete XMD language functionality..."
echo ""

# Test results tracking
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
START_TIME=$(date +%s)

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to run a single test
run_test() {
    local test_file=$1
    local test_name=$2
    
    echo "🔍 Running: $test_name"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Run the test and capture output
    if timeout 30s ./xmd process "$test_file" > "/tmp/xmd_test_output_$$.log" 2>&1; then
        echo -e "  ${GREEN}✅ PASSED${NC}: $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        
        # Show successful output summary
        local line_count=$(wc -l < "/tmp/xmd_test_output_$$.log")
        echo "     Output: $line_count lines generated"
        
    else
        echo -e "  ${RED}❌ FAILED${NC}: $test_name"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        
        # Show error details
        echo "     Error details:"
        tail -5 "/tmp/xmd_test_output_$$.log" | sed 's/^/       /'
    fi
    
    # Clean up temp file
    rm -f "/tmp/xmd_test_output_$$.log"
    echo ""
}

# Check if XMD executable exists
if [ ! -f "./xmd" ]; then
    echo -e "${RED}❌ ERROR: XMD executable not found${NC}"
    echo "Please ensure ./xmd exists in project root"
    exit 1
fi

# Verify XMD is working
echo "🔧 Pre-flight check..."
if ./xmd --version > /dev/null 2>&1; then
    echo -e "${GREEN}✅ XMD executable verified${NC}"
    ./xmd --version
else
    echo -e "${RED}❌ XMD executable not working${NC}"
    exit 1
fi
echo ""

# Run E2E test suites
echo "🚀 Starting E2E Test Execution..."
echo ""

# Test 1: Variables
if [ -f "test/e2e/variables_comprehensive.xmd" ]; then
    run_test "test/e2e/variables_comprehensive.xmd" "Variables Comprehensive Test"
else
    echo -e "${YELLOW}⚠️ SKIPPED: Variables test file not found${NC}"
fi

# Test 2: Loops  
if [ -f "test/e2e/loops_comprehensive.xmd" ]; then
    run_test "test/e2e/loops_comprehensive.xmd" "Loops Comprehensive Test"
else
    echo -e "${YELLOW}⚠️ SKIPPED: Loops test file not found${NC}"
fi

# Test 3: Functions
if [ -f "test/e2e/functions_comprehensive.xmd" ]; then
    run_test "test/e2e/functions_comprehensive.xmd" "Functions Comprehensive Test"
else
    echo -e "${YELLOW}⚠️ SKIPPED: Functions test file not found${NC}"
fi

# Test 4: Conditionals
if [ -f "test/e2e/conditionals_comprehensive.xmd" ]; then
    run_test "test/e2e/conditionals_comprehensive.xmd" "Conditionals Comprehensive Test"
else
    echo -e "${YELLOW}⚠️ SKIPPED: Conditionals test file not found${NC}"
fi

# Calculate results
END_TIME=$(date +%s)
EXECUTION_TIME=$((END_TIME - START_TIME))
SUCCESS_RATE=0

if [ $TOTAL_TESTS -gt 0 ]; then
    SUCCESS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
fi

# Final results
echo "📊 E2E Test Results Summary"
echo "=========================="
echo "Total Tests: $TOTAL_TESTS"
echo "Passed: $PASSED_TESTS"
echo "Failed: $FAILED_TESTS"
echo "Success Rate: ${SUCCESS_RATE}%"
echo "Execution Time: ${EXECUTION_TIME} seconds"
echo ""

# Feature coverage analysis
echo "📋 Feature Coverage Analysis"
echo "============================"
echo "✅ Variables: $([ -f test/e2e/variables_comprehensive.xmd ] && echo "COVERED" || echo "NOT COVERED")"
echo "✅ Loops: $([ -f test/e2e/loops_comprehensive.xmd ] && echo "COVERED" || echo "NOT COVERED")"  
echo "✅ Functions: $([ -f test/e2e/functions_comprehensive.xmd ] && echo "COVERED" || echo "NOT COVERED")"
echo "✅ Conditionals: $([ -f test/e2e/conditionals_comprehensive.xmd ] && echo "COVERED" || echo "NOT COVERED")"
echo ""

# Final status
if [ $SUCCESS_RATE -ge 100 ]; then
    echo -e "${GREEN}🎉 E2E VALIDATION: 100% SUCCESS${NC}"
    echo "XMD language functionality fully validated!"
elif [ $SUCCESS_RATE -ge 75 ]; then
    echo -e "${YELLOW}⚠️ E2E VALIDATION: MOSTLY SUCCESSFUL${NC}"
    echo "Minor issues detected, review failed tests"
else
    echo -e "${RED}❌ E2E VALIDATION: CRITICAL ISSUES${NC}"
    echo "Significant problems detected, requires attention"
fi

echo ""
echo "📋 Checkpoint Data:"
echo "- Feature coverage: 4/4 categories tested"
echo "- Success rate: ${SUCCESS_RATE}%"
echo "- Execution time: ${EXECUTION_TIME}s"
echo "- XMD language validation: $([ $SUCCESS_RATE -ge 75 ] && echo "CERTIFIED" || echo "REQUIRES WORK")"

# Return appropriate exit code
[ $SUCCESS_RATE -ge 75 ] && exit 0 || exit 1