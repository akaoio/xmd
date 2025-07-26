#!/bin/bash

# XMD Comprehensive Test Suite
# Tests all features, shorthand patterns, and edge cases

set -e  # Exit on any error
trap cleanup EXIT

XMD="./build/xmd"
TEST_DIR="test_output"
PASSED=0
FAILED=0
TOTAL=0

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Setup test environment
setup() {
    echo -e "${BLUE}Setting up test environment...${NC}"
    rm -rf "$TEST_DIR"
    mkdir -p "$TEST_DIR"
    cd "$TEST_DIR"
    
    # Build XMD if needed
    if [ ! -f "../build/xmd" ]; then
        echo "Building XMD..."
        cd ..
        gcc -I./include -L./build -o ./build/xmd src/main.c -lxmd_lib
        cd "$TEST_DIR"
    fi
    
    XMD="../build/xmd"
}

# Cleanup function
cleanup() {
    cd ..
    if [ -d "$TEST_DIR" ]; then
        rm -rf "$TEST_DIR"
    fi
}

# Test assertion functions
assert_equals() {
    local expected="$1"
    local actual="$2"
    local test_name="$3"
    
    TOTAL=$((TOTAL + 1))
    
    if [ "$expected" = "$actual" ]; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        echo -e "  Expected: ${YELLOW}$expected${NC}"
        echo -e "  Actual:   ${YELLOW}$actual${NC}"
        FAILED=$((FAILED + 1))
    fi
}

assert_file_exists() {
    local file="$1"
    local test_name="$2"
    
    TOTAL=$((TOTAL + 1))
    
    if [ -f "$file" ]; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        echo -e "  File not found: ${YELLOW}$file${NC}"
        FAILED=$((FAILED + 1))
    fi
}

assert_file_contains() {
    local file="$1"
    local content="$2"
    local test_name="$3"
    
    TOTAL=$((TOTAL + 1))
    
    if [ -f "$file" ] && grep -q "$content" "$file"; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        echo -e "  File: ${YELLOW}$file${NC}"
        echo -e "  Expected content: ${YELLOW}$content${NC}"
        if [ -f "$file" ]; then
            echo -e "  Actual content: ${YELLOW}$(cat "$file")${NC}"
        else
            echo -e "  File does not exist"
        fi
        FAILED=$((FAILED + 1))
    fi
}

run_test_silent() {
    local cmd="$1"
    local output_file="${2:-/tmp/xmd_test_output}"
    
    eval "$cmd" > "$output_file" 2>&1
    return $?
}

# Create test files
create_test_files() {
    echo -e "${BLUE}Creating test files...${NC}"
    
    # Basic template file
    cat > basic.md << 'EOF'
Hello {{name}}!
This is a test document.
EOF

    # Template with variables
    cat > variables.md << 'EOF'
# {{title}}
Welcome {{name}}!
Environment: {{env}}
Status: {{status}}
EOF

    # Template with for loops
    cat > for_loops.md << 'EOF'
# Server Status
<!-- xmd:for i in 1..3 -->
- Server {{i}}: {{status}}
<!-- xmd:endfor -->

# Items List  
<!-- xmd:for item in ["apple", "banana", "cherry"] -->
* {{item}}
<!-- xmd:endfor -->
EOF

    # Template with range expressions
    cat > ranges.md << 'EOF'
# Range Tests
<!-- xmd:for i in 1..5 -->
Number: {{i}}
<!-- xmd:endfor -->

<!-- xmd:for i in start..end -->
Value: {{i}}
<!-- xmd:endfor -->
EOF

    # Template with if statements
    cat > conditionals.md << 'EOF'
# Conditional Content
<!-- xmd:if env == "prod" -->
Production environment detected.
<!-- xmd:endif -->

<!-- xmd:if debug == "true" -->
Debug mode is enabled.
<!-- xmd:endif -->
EOF

    # Complex template combining features
    cat > complex.md << 'EOF'
# {{project}} - {{version}}

## Server Status
<!-- xmd:for i in 1..3 -->
<!-- xmd:if status == "online" -->
✅ Server {{i}}: Online
<!-- xmd:endif -->
<!-- xmd:if status == "offline" -->
❌ Server {{i}}: Offline  
<!-- xmd:endif -->
<!-- xmd:endfor -->

## Configuration
- Environment: {{env}}
- Debug: {{debug}}
- Region: {{region}}
EOF

    # Multiline content for stdin tests
    cat > multiline.md << 'EOF'
# Multi-line Test
Line 1: {{var1}}
Line 2: {{var2}}

<!-- xmd:for i in 1..2 -->
Loop {{i}}: {{status}}
<!-- xmd:endfor -->
EOF
}

# Test Suite 1: Basic Command Structure
test_basic_commands() {
    echo -e "\n${BLUE}=== Testing Basic Commands ===${NC}"
    
    # Test help command
    run_test_silent "$XMD help" help_output.txt
    assert_file_contains help_output.txt "XMD - eXtended MarkDown processor" "Help command shows version"
    assert_file_contains help_output.txt "Shorthand Examples" "Help shows shorthand examples"
    
    # Test version command
    run_test_silent "$XMD version" version_output.txt
    assert_file_contains version_output.txt "XMD v1.0.0" "Version command works"
    
    # Test validate command
    run_test_silent "$XMD validate basic.md" validate_output.txt
    local validate_result=$?
    assert_equals "0" "$validate_result" "Validate command succeeds on valid file"
}

# Test Suite 2: Variable Substitution
test_variable_substitution() {
    echo -e "\n${BLUE}=== Testing Variable Substitution ===${NC}"
    
    # Test single variable
    run_test_silent "$XMD process basic.md -v name='World'" single_var.txt
    assert_file_contains single_var.txt "Hello World!" "Single variable substitution"
    
    # Test multiple variables
    run_test_silent "$XMD process variables.md -v title='Test Report' -v name='Alice' -v env='production' -v status='active'" multi_var.txt
    assert_file_contains multi_var.txt "# Test Report" "Multiple variables - title"
    assert_file_contains multi_var.txt "Welcome Alice!" "Multiple variables - name"
    assert_file_contains multi_var.txt "Environment: production" "Multiple variables - env"
    assert_file_contains multi_var.txt "Status: active" "Multiple variables - status"
}

# Test Suite 3: For Loops and Ranges
test_for_loops() {
    echo -e "\n${BLUE}=== Testing For Loops and Ranges ===${NC}"
    
    # Test simple range
    run_test_silent "$XMD process for_loops.md -v status='online'" for_simple.txt
    assert_file_contains for_simple.txt "Server 1: online" "For loop range 1..3 - item 1"
    assert_file_contains for_simple.txt "Server 2: online" "For loop range 1..3 - item 2"
    assert_file_contains for_simple.txt "Server 3: online" "For loop range 1..3 - item 3"
    
    # Test array iteration
    assert_file_contains for_simple.txt "* apple" "For loop array - apple"
    assert_file_contains for_simple.txt "* banana" "For loop array - banana"  
    assert_file_contains for_simple.txt "* cherry" "For loop array - cherry"
    
    # Test variable ranges
    run_test_silent "$XMD process ranges.md -v start='2' -v end='4'" var_ranges.txt
    assert_file_contains var_ranges.txt "Number: 1" "Range 1..5 - item 1"
    assert_file_contains var_ranges.txt "Number: 5" "Range 1..5 - item 5"
    assert_file_contains var_ranges.txt "Value: 2" "Variable range start..end - item 2"
    assert_file_contains var_ranges.txt "Value: 4" "Variable range start..end - item 4"
}

# Test Suite 4: Conditional Statements
test_conditionals() {
    echo -e "\n${BLUE}=== Testing Conditional Statements ===${NC}"
    
    # Test if condition true
    run_test_silent "$XMD process conditionals.md -v env='prod' -v debug='true'" cond_true.txt
    assert_file_contains cond_true.txt "Production environment detected" "If condition true - env"
    assert_file_contains cond_true.txt "Debug mode is enabled" "If condition true - debug"
    
    # Test if condition false
    run_test_silent "$XMD process conditionals.md -v env='dev' -v debug='false'" cond_false.txt
    # Should NOT contain production message
    if grep -q "Production environment detected" cond_false.txt; then
        echo -e "${RED}✗ FAIL${NC}: If condition false - should not show production message"
        FAILED=$((FAILED + 1))
    else
        echo -e "${GREEN}✓ PASS${NC}: If condition false - correctly hides production message"
        PASSED=$((PASSED + 1))
    fi
    TOTAL=$((TOTAL + 1))
}

# Test Suite 5: Output Formats
test_output_formats() {
    echo -e "\n${BLUE}=== Testing Output Formats ===${NC}"
    
    # Test markdown format (default)
    run_test_silent "$XMD process basic.md -v name='World' --format markdown" format_md.txt
    assert_file_contains format_md.txt "Hello World!" "Markdown format output"
    
    # Test HTML format
    run_test_silent "$XMD process basic.md -v name='World' --format html" format_html.txt
    assert_file_contains format_html.txt "<!DOCTYPE html>" "HTML format has doctype"
    assert_file_contains format_html.txt "Hello World!" "HTML format contains content"
    assert_file_contains format_html.txt "</html>" "HTML format is complete"
    
    # Test JSON format
    run_test_silent "$XMD process basic.md -v name='World' --format json" format_json.txt
    assert_file_contains format_json.txt '"status": "success"' "JSON format has status"
    assert_file_contains format_json.txt '"processor": "XMD v1.0.0"' "JSON format has processor info"
    assert_file_contains format_json.txt "Hello World" "JSON format contains content"
}

# Test Suite 6: Shorthand Patterns
test_shorthand_patterns() {
    echo -e "\n${BLUE}=== Testing Shorthand Patterns ===${NC}"
    
    # Test single file shorthand
    run_test_silent "$XMD basic.md -v name='World'" shorthand_single.txt
    assert_file_contains shorthand_single.txt "Hello World!" "Single file shorthand"
    
    # Test stdin processing shorthand
    echo "Hello {{name}}!" | $XMD -v name='World' > shorthand_stdin.txt 2>&1
    assert_file_contains shorthand_stdin.txt "Hello World!" "Stdin shorthand"
    
    # Test stdin to file shorthand
    echo "Status: {{status}}" | $XMD shorthand_output.md -v status='OK' 2>/dev/null
    assert_file_exists "shorthand_output.md" "Stdin to file creates output file"
    assert_file_contains shorthand_output.md "Status: OK" "Stdin to file shorthand content"
    
    # Test pipe shorthand
    echo "Test {{var}}" | $XMD -v var='value' > shorthand_pipe.txt 2>&1
    assert_file_contains shorthand_pipe.txt "Test value" "Pipe shorthand"
}

# Test Suite 7: File Operations
test_file_operations() {
    echo -e "\n${BLUE}=== Testing File Operations ===${NC}"
    
    # Test input file processing
    run_test_silent "$XMD process basic.md -v name='FileTest'" file_input.txt
    assert_file_contains file_input.txt "Hello FileTest!" "File input processing"
    
    # Test output to file with -o option
    $XMD process basic.md -v name='OutputTest' -o file_output.md 2>/dev/null
    assert_file_exists "file_output.md" "Output file creation with -o"
    
    # Test that file contains expected content
    if [ -f "file_output.md" ] && [ -s "file_output.md" ]; then
        echo -e "${GREEN}✓ PASS${NC}: Output file has content"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: Output file is empty or missing"
        FAILED=$((FAILED + 1))
    fi
    TOTAL=$((TOTAL + 1))
}

# Test Suite 8: Complex Scenarios
test_complex_scenarios() {
    echo -e "\n${BLUE}=== Testing Complex Scenarios ===${NC}"
    
    # Test complex template with multiple features
    run_test_silent "$XMD process complex.md -v project='MyApp' -v version='1.0' -v status='online' -v env='prod' -v debug='false' -v region='us-east'" complex_output.txt
    assert_file_contains complex_output.txt "# MyApp - 1.0" "Complex template - title"
    assert_file_contains complex_output.txt "✅ Server 1: Online" "Complex template - server status"
    assert_file_contains complex_output.txt "Environment: prod" "Complex template - environment"
    
    # Test multiline with stdin
    cat multiline.md | $XMD -v var1='Value1' -v var2='Value2' -v status='ready' > complex_stdin.txt 2>&1
    assert_file_contains complex_stdin.txt "Line 1: Value1" "Multiline stdin - var1"
    assert_file_contains complex_stdin.txt "Line 2: Value2" "Multiline stdin - var2"
    assert_file_contains complex_stdin.txt "Loop 1: ready" "Multiline stdin - loop"
}

# Test Suite 9: Error Handling
test_error_handling() {
    echo -e "\n${BLUE}=== Testing Error Handling ===${NC}"
    
    # Test non-existent file
    run_test_silent "$XMD process nonexistent.md" error_nofile.txt
    local result=$?
    if [ $result -ne 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: Non-existent file returns error code"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: Non-existent file should return error code"
        FAILED=$((FAILED + 1))
    fi
    TOTAL=$((TOTAL + 1))
    
    # Test invalid format
    run_test_silent "$XMD process basic.md --format invalid" error_format.txt
    local result=$?
    if [ $result -ne 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: Invalid format returns error code"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: Invalid format should return error code"
        FAILED=$((FAILED + 1))
    fi
    TOTAL=$((TOTAL + 1))
    
    # Test malformed variable
    run_test_silent "$XMD process basic.md -v malformed" error_var.txt
    local result=$?
    if [ $result -ne 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: Malformed variable returns error code"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: Malformed variable should return error code"
        FAILED=$((FAILED + 1))
    fi
    TOTAL=$((TOTAL + 1))
}

# Test Suite 10: Advanced Options
test_advanced_options() {
    echo -e "\n${BLUE}=== Testing Advanced Options ===${NC}"
    
    # Test debug mode
    run_test_silent "$XMD process basic.md -v name='Debug' --debug" debug_output.txt
    assert_file_contains debug_output.txt "Hello Debug!" "Debug mode processes content"
    
    # Test no-exec mode
    run_test_silent "$XMD process basic.md -v name='NoExec' --no-exec" noexec_output.txt
    assert_file_contains noexec_output.txt "Hello NoExec!" "No-exec mode processes content"
    
    # Test trace mode (if file exists)
    $XMD process basic.md -v name='Trace' --trace > trace_output.txt 2>&1
    # Trace might create additional files, just check that command doesn't crash
    local result=$?
    if [ $result -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: Trace mode doesn't crash"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: Trace mode crashed"
        FAILED=$((FAILED + 1))
    fi
    TOTAL=$((TOTAL + 1))
}

# Main test runner
run_all_tests() {
    echo -e "${BLUE}XMD Comprehensive Test Suite${NC}"
    echo -e "${BLUE}=============================${NC}"
    
    setup
    create_test_files
    
    test_basic_commands
    test_variable_substitution
    test_for_loops
    test_conditionals
    test_output_formats
    test_shorthand_patterns
    test_file_operations
    test_complex_scenarios
    test_error_handling
    test_advanced_options
    
    # Summary
    echo -e "\n${BLUE}=== Test Summary ===${NC}"
    echo -e "Total tests: $TOTAL"
    echo -e "${GREEN}Passed: $PASSED${NC}"
    echo -e "${RED}Failed: $FAILED${NC}"
    
    if [ $FAILED -eq 0 ]; then
        echo -e "\n${GREEN}🎉 All tests passed!${NC}"
        exit 0
    else
        echo -e "\n${RED}❌ Some tests failed.${NC}"
        exit 1
    fi
}

# Run the test suite
run_all_tests