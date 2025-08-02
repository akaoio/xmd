#!/bin/bash
# XMD Deployment Readiness Checker
# Verifies system is ready for production deployment

echo "============================================"
echo "XMD DEPLOYMENT READINESS CHECK"
echo "============================================"
echo ""

# Initialize status
READY=true

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Function to check a requirement
check_requirement() {
    local name="$1"
    local command="$2"
    local required="$3"
    
    echo -n "Checking $name... "
    
    if eval "$command" > /dev/null 2>&1; then
        echo -e "${GREEN}✅ PASSED${NC}"
    else
        echo -e "${RED}❌ FAILED${NC}"
        if [ "$required" = "true" ]; then
            READY=false
        fi
    fi
}

# 1. BUILD SYSTEM CHECKS
echo "1. BUILD SYSTEM CHECKS"
echo "----------------------"

check_requirement "XMD binary exists" "[ -f ./build/xmd ]" true
check_requirement "Binary is executable" "[ -x ./build/xmd ]" true
check_requirement "Build completes successfully" "./build.sh" true
check_requirement "No compilation errors" "! ./build.sh 2>&1 | grep -i error" true

echo ""

# 2. RUNTIME CHECKS
echo "2. RUNTIME CHECKS"
echo "-----------------"

check_requirement "Version command works" "./build/xmd --version" true
check_requirement "Help command works" "./build/xmd --help" true

# Create a simple test file
echo 'set test "working"' > /tmp/deployment_test.xmd
echo '{{test}}' >> /tmp/deployment_test.xmd

check_requirement "Process simple file" "./build/xmd process /tmp/deployment_test.xmd | grep -q working" true
check_requirement "No segmentation faults" "! ./build/xmd process /tmp/deployment_test.xmd 2>&1 | grep -i 'segmentation fault'" true

echo ""

# 3. CORE FEATURE CHECKS
echo "3. CORE FEATURE CHECKS"
echo "----------------------"

# Test variable assignment
echo 'set x 42' > /tmp/test_var.xmd
echo '{{x}}' >> /tmp/test_var.xmd
check_requirement "Variable assignment" "./build/xmd process /tmp/test_var.xmd | grep -q 42" true

# Test math expressions
echo 'set result 2 + 3' > /tmp/test_math.xmd
echo '{{result}}' >> /tmp/test_math.xmd
check_requirement "Math expressions" "./build/xmd process /tmp/test_math.xmd | grep -q 5" false

# Test conditionals
echo 'set x 5' > /tmp/test_if.xmd
echo 'if x = 5' >> /tmp/test_if.xmd
echo '    Success' >> /tmp/test_if.xmd
echo 'endif' >> /tmp/test_if.xmd
check_requirement "Conditional statements" "./build/xmd process /tmp/test_if.xmd | grep -q Success" false

echo ""

# 4. MEMORY SAFETY CHECKS
echo "4. MEMORY SAFETY CHECKS"
echo "-----------------------"

if command -v valgrind > /dev/null 2>&1; then
    check_requirement "No memory leaks" "valgrind --leak-check=full --error-exitcode=1 ./build/xmd --version 2>&1 | grep -q 'no leaks are possible'" false
else
    echo -e "Valgrind not installed - ${YELLOW}⚠️  SKIPPED${NC}"
fi

echo ""

# 5. DOCUMENTATION CHECKS
echo "5. DOCUMENTATION CHECKS"
echo "-----------------------"

check_requirement "README.md exists" "[ -f README.md ]" true
check_requirement "CHANGELOG.md exists" "[ -f CHANGELOG.md ]" true
check_requirement "LICENSE exists" "[ -f LICENSE ]" true
check_requirement "Release notes exist" "[ -f RELEASE_NOTES.md ]" true

echo ""

# 6. TEST SUITE CHECKS
echo "6. TEST SUITE CHECKS"
echo "--------------------"

check_requirement "Test runner exists" "[ -f test_infrastructure/test_runner.sh ]" true
check_requirement "Comprehensive tests exist" "[ -f test_infrastructure/comprehensive_test_suite.sh ]" true
check_requirement "Basic test suite passes" "./test_infrastructure/test_runner.sh" false

echo ""

# 7. CI/CD CHECKS
echo "7. CI/CD CHECKS"
echo "---------------"

check_requirement "GitHub Actions workflow" "[ -f .github/workflows/ci.yml ] || [ -f .github/workflows/test.yml ]" true
check_requirement "Deployment script exists" "[ -f deploy.sh ]" true

echo ""

# 8. GENESIS COMPLIANCE
echo "8. GENESIS COMPLIANCE CHECKS"
echo "----------------------------"

check_requirement "No stub implementations" "! grep -r 'STUB' src/ 2>/dev/null | grep -v '//' | grep -v '*'" true
check_requirement "No mock implementations" "! grep -r 'MOCK' src/ 2>/dev/null | grep -v '//' | grep -v '*'" true
check_requirement "AST parser implemented" "grep -q 'ast_parse_program' src/ast_consolidated.c" true
check_requirement "No string parser" "! grep -q 'xmd_dispatch_process' src/native_xmd_consolidated.c" true
check_requirement "Genesis compliance tests exist" "[ -f test_infrastructure/genesis_compliance_test.sh ]" true

# Test Genesis syntax compliance
echo 'set x 5' > /tmp/test_genesis_syntax.xmd
echo 'if x = 5' >> /tmp/test_genesis_syntax.xmd
echo '    Success' >> /tmp/test_genesis_syntax.xmd
echo 'endif' >> /tmp/test_genesis_syntax.xmd
check_requirement "Genesis syntax (= comparison)" "./build/xmd process /tmp/test_genesis_syntax.xmd | grep -q Success" false

echo ""

# FINAL SUMMARY
echo "============================================"
echo "DEPLOYMENT READINESS SUMMARY"
echo "============================================"
echo ""

if [ "$READY" = true ]; then
    echo -e "${GREEN}✅ SYSTEM IS READY FOR DEPLOYMENT!${NC}"
    echo ""
    echo "All critical checks passed. XMD can be deployed to production."
    echo ""
    echo "Recommended next steps:"
    echo "1. Run './deploy.sh' to deploy to production"
    echo "2. Monitor system performance after deployment"
    echo "3. Set up automated monitoring and alerts"
    exit 0
else
    echo -e "${RED}❌ SYSTEM NOT READY FOR DEPLOYMENT${NC}"
    echo ""
    echo "Critical issues must be resolved before deployment."
    echo "Please fix all failed checks marked as required."
    exit 1
fi

# Cleanup
rm -f /tmp/deployment_test.xmd /tmp/test_var.xmd /tmp/test_math.xmd /tmp/test_if.xmd