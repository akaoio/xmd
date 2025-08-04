#!/bin/bash
# XMD Swarm Compliance Enforcement Script
# ENFORCING ALL DEVELOPMENT PRINCIPLES

set -e

echo "🚨 XMD SWARM COMPLIANCE ENFORCEMENT STARTING..."
echo "Enforcing: One function, one file, one folder principle"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

VIOLATIONS=0

echo -e "\n📋 CHECKING PRINCIPLE: One Function Per File"

# Find all C files and check for multiple function definitions
echo "Scanning source files for multiple functions..."

find src -name "*.c" -type f | while read -r file; do
    # Count function definitions (looking for pattern: type funcname(...) {)
    func_count=$(grep -c '^[a-zA-Z_][a-zA-Z0-9_]*.*(' "$file" 2>/dev/null || echo 0)
    
    if [ "$func_count" -gt 1 ]; then
        echo -e "${RED}❌ VIOLATION${NC}: $file contains $func_count functions"
        VIOLATIONS=$((VIOLATIONS + 1))
        
        # Show the function names
        echo "   Functions found:"
        grep '^[a-zA-Z_][a-zA-Z0-9_]*.*(' "$file" | head -5 | sed 's/^/     /'
        
        if [ "$func_count" -gt 5 ]; then
            echo "     ... and $((func_count - 5)) more"
        fi
        echo
    fi
done

echo -e "\n📋 CHECKING PRINCIPLE: Test-Driven Development"

# Count C source files
src_files=$(find src -name "*.c" -type f | wc -l)
test_files=$(find tests -name "test_*.c" -type f 2>/dev/null | wc -l || echo 0)

echo "Source files: $src_files"
echo "Test files: $test_files"

if [ "$test_files" -eq 0 ]; then
    echo -e "${RED}❌ CRITICAL VIOLATION${NC}: No test files found!"
    echo "REQUIRED: Every source file must have corresponding tests"
    VIOLATIONS=$((VIOLATIONS + 1))
elif [ "$test_files" -lt $((src_files / 10)) ]; then
    echo -e "${YELLOW}⚠️  WARNING${NC}: Very low test coverage ($test_files tests for $src_files source files)"
fi

echo -e "\n📋 CHECKING PRINCIPLE: Keep Root Folder Clean"

# Check root directory
root_files=$(find . -maxdepth 1 -type f | wc -l)
if [ "$root_files" -gt 10 ]; then
    echo -e "${YELLOW}⚠️  WARNING${NC}: Root directory has $root_files files (should be < 10)"
    echo "Consider moving some files to subdirectories:"
    find . -maxdepth 1 -type f | head -5 | sed 's/^/  /'
fi

echo -e "\n📋 CHECKING PRINCIPLE: Use tmp/ for Temporary Files"

# Check for temp files outside tmp/
temp_violations=$(find src include -name "*.tmp*" -o -name "*.temp*" -o -name "*~" -o -name "*.bak" 2>/dev/null | wc -l || echo 0)

if [ "$temp_violations" -gt 0 ]; then
    echo -e "${RED}❌ VIOLATION${NC}: Found temporary files outside tmp/ directory:"
    find src include -name "*.tmp*" -o -name "*.temp*" -o -name "*~" -o -name "*.bak" 2>/dev/null | sed 's/^/  /' || true
    VIOLATIONS=$((VIOLATIONS + 1))
else
    echo -e "${GREEN}✅ PASS${NC}: No temporary files found outside tmp/"
fi

echo -e "\n📋 CHECKING PRINCIPLE: No Duplication"

# Basic duplication check (simplified)
echo "Running basic duplication analysis..."

# Check for duplicate function names (simple check)
duplicate_funcs=$(find src -name "*.c" -exec grep -h '^[a-zA-Z_][a-zA-Z0-9_]*.*(' {} \; | sort | uniq -d | wc -l)

if [ "$duplicate_funcs" -gt 0 ]; then
    echo -e "${RED}❌ VIOLATION${NC}: Found $duplicate_funcs potentially duplicate function signatures"
    VIOLATIONS=$((VIOLATIONS + 1))
else
    echo -e "${GREEN}✅ PASS${NC}: No obvious function name duplications found"
fi

echo -e "\n📊 COMPLIANCE SUMMARY"
echo "======================"

if [ "$VIOLATIONS" -eq 0 ]; then
    echo -e "${GREEN}🎉 EXCELLENT! All major principles compliant${NC}"
    echo -e "${GREEN}Swarm can proceed with development${NC}"
    exit 0
else
    echo -e "${RED}💥 COMPLIANCE FAILURES: $VIOLATIONS violations found${NC}"
    echo -e "${RED}Swarm must fix these violations before proceeding${NC}"
    echo ""
    echo "IMMEDIATE ACTIONS REQUIRED:"
    echo "1. Split all multi-function files"
    echo "2. Create test files for major functions"
    echo "3. Move temporary files to tmp/ directory"
    echo "4. Review duplication issues"
    echo ""
    echo "Use: make test    (to run tests)"
    echo "Use: ./scripts/split_files.sh  (to split multi-function files)"
    exit 1
fi