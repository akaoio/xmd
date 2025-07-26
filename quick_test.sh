#!/bin/bash

# Quick focused test to verify fixes
XMD="./build/xmd"

echo "=== Quick Test Results ==="

# Test 1: Basic variable substitution (stdin)
echo -n "1. Stdin variable substitution: "
result=$(echo "Hello {{name}}!" | $XMD -v name="World" 2>/dev/null)
if [[ "$result" == "Hello World!" ]]; then
    echo "✓ PASS"
else
    echo "✗ FAIL - got: $result"
fi

# Test 2: File variable substitution
echo "Hello {{name}}!" > test_file.md
echo -n "2. File variable substitution: "
result=$($XMD process test_file.md -v name="World" 2>/dev/null)
if [[ "$result" == "Hello World!" ]]; then
    echo "✓ PASS" 
else
    echo "✗ FAIL - got: $result"
fi

# Test 3: Shorthand file processing
echo -n "3. Shorthand file processing: "
result=$($XMD test_file.md -v name="World" 2>/dev/null)
if [[ "$result" == "Hello World!" ]]; then
    echo "✓ PASS"
else
    echo "✗ FAIL - got: $result"
fi

# Test 4: Stdin to file
echo -n "4. Stdin to file: "
echo "Hello {{name}}!" | $XMD test_output.md -v name="World" 2>/dev/null
if [[ -f "test_output.md" ]] && [[ "$(cat test_output.md)" == "Hello World!" ]]; then
    echo "✓ PASS"
else
    echo "✗ FAIL - file missing or wrong content"
fi

# Test 5: For loop basic
cat > loop_test.md << 'EOF'
<!-- xmd:for i in [1, 2, 3] -->
Item {{i}}
<!-- xmd:endfor -->
EOF

echo -n "5. For loop processing: "
result=$($XMD process loop_test.md 2>/dev/null)
if [[ "$result" == *"Item 1"* ]] && [[ "$result" == *"Item 2"* ]] && [[ "$result" == *"Item 3"* ]]; then
    echo "✓ PASS"
else
    echo "✗ FAIL - got: $result"
fi

# Cleanup
rm -f test_file.md test_output.md loop_test.md

echo "=== End Quick Test ==="