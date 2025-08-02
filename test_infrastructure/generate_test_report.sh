#!/bin/bash
# XMD Test Report Generator
# Generates comprehensive test reports in multiple formats

echo "============================================"
echo "XMD TEST REPORT GENERATOR"
echo "============================================"
echo ""

# Configuration
REPORT_DIR="test_infrastructure/reports"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
DATE=$(date +"%Y-%m-%d %H:%M:%S")
mkdir -p "$REPORT_DIR"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Report files
MARKDOWN_REPORT="$REPORT_DIR/test_report_${TIMESTAMP}.md"
HTML_REPORT="$REPORT_DIR/test_report_${TIMESTAMP}.html"
JSON_REPORT="$REPORT_DIR/test_report_${TIMESTAMP}.json"

echo "Generating test reports..."
echo ""

# Function to run tests and capture output
run_and_capture() {
    local test_name="$1"
    local test_script="$2"
    local output_var="$3"
    
    echo "Running $test_name..."
    local output=$($test_script 2>&1)
    eval "$output_var=\"\$output\""
}

# Run all test suites
run_and_capture "Basic Tests" "./test_infrastructure/test_runner.sh" "BASIC_OUTPUT"
run_and_capture "Comprehensive Tests" "./test_infrastructure/comprehensive_test_suite.sh" "COMPREHENSIVE_OUTPUT"
run_and_capture "Genesis Compliance Tests" "./test_infrastructure/genesis_compliance_test.sh" "GENESIS_OUTPUT"
run_and_capture "Deployment Readiness" "./test_infrastructure/deployment_readiness.sh" "DEPLOYMENT_OUTPUT"
run_and_capture "Performance Benchmarks" "./test_infrastructure/performance_benchmark.sh" "PERFORMANCE_OUTPUT"

# Extract statistics
BASIC_PASSED=$(echo "$BASIC_OUTPUT" | grep -c "✅ PASSED" || echo 0)
BASIC_FAILED=$(echo "$BASIC_OUTPUT" | grep -c "❌ FAILED" || echo 0)
COMPREHENSIVE_PASSED=$(echo "$COMPREHENSIVE_OUTPUT" | grep -c "✅ PASSED" || echo 0)
COMPREHENSIVE_FAILED=$(echo "$COMPREHENSIVE_OUTPUT" | grep -c "❌ FAILED" || echo 0)
COMPREHENSIVE_SKIPPED=$(echo "$COMPREHENSIVE_OUTPUT" | grep -c "⏭️  SKIPPED" || echo 0)
GENESIS_PASSED=$(echo "$GENESIS_OUTPUT" | grep -c "✅ PASSED" || echo 0)
GENESIS_FAILED=$(echo "$GENESIS_OUTPUT" | grep -c "❌ FAILED" || echo 0)

# Generate Markdown Report
cat > "$MARKDOWN_REPORT" << EOF
# XMD Test Report

**Generated:** $DATE  
**System:** XMD Language Implementation  
**Version:** $(./build/xmd --version 2>/dev/null || echo "Unknown")

## Executive Summary

### Overall Status
$(if [ $BASIC_FAILED -eq 0 ] && [ $COMPREHENSIVE_FAILED -eq 0 ]; then
    echo "✅ **All implemented features are working correctly**"
else
    echo "❌ **Some tests are failing - investigation required**"
fi)

### Test Statistics
- **Basic Tests:** $BASIC_PASSED passed, $BASIC_FAILED failed
- **Comprehensive Tests:** $COMPREHENSIVE_PASSED passed, $COMPREHENSIVE_FAILED failed, $COMPREHENSIVE_SKIPPED skipped
- **Genesis Compliance:** $GENESIS_PASSED passed, $GENESIS_FAILED failed
- **Total Tests Run:** $((BASIC_PASSED + BASIC_FAILED + COMPREHENSIVE_PASSED + COMPREHENSIVE_FAILED + COMPREHENSIVE_SKIPPED + GENESIS_PASSED + GENESIS_FAILED))
- **Implementation Progress:** $((COMPREHENSIVE_PASSED * 100 / 20))% of Genesis specification
- **Genesis Compliance:** $((GENESIS_PASSED * 100 / (GENESIS_PASSED + GENESIS_FAILED)))% correct syntax

## Detailed Test Results

### Basic Language Tests
\`\`\`
$BASIC_OUTPUT
\`\`\`

### Comprehensive Feature Tests
\`\`\`
$COMPREHENSIVE_OUTPUT
\`\`\`

### Genesis Specification Compliance
\`\`\`
$GENESIS_OUTPUT
\`\`\`

### Deployment Readiness
\`\`\`
$DEPLOYMENT_OUTPUT
\`\`\`

### Performance Benchmarks
\`\`\`
$PERFORMANCE_OUTPUT
\`\`\`

## Implementation Status by Feature

| Feature | Status | Notes |
|---------|--------|-------|
| Variables (set/get) | ✅ Implemented | Working with {{varname}} syntax |
| Math Expressions | ⚠️ Partial | Parsing works, evaluation pending |
| Conditionals (if/else) | ⚠️ Partial | Basic if works, comparisons pending |
| Loops (for/while) | ❌ Not Implemented | Planned for next phase |
| Functions | ❌ Not Implemented | Planned for next phase |
| Classes | ❌ Not Implemented | Advanced feature |
| Import/Export | ❌ Not Implemented | Module system pending |
| Arrays | ❌ Not Implemented | Data structures pending |
| Objects | ❌ Not Implemented | Data structures pending |
| Error Handling | ❌ Not Implemented | Exception system pending |
| Async/Await | ❌ Not Implemented | Advanced feature |
| Generators | ❌ Not Implemented | Advanced feature |
| Lambda Functions | ❌ Not Implemented | Advanced feature |
| Formal Logic | ❌ Not Implemented | Specialized feature |
| Exec Command | ⚠️ Partial | Security configuration needed |
| Markdown Integration | ✅ Implemented | Working with code blocks |
| HTML Comments | ✅ Implemented | Inline XMD supported |

## Recommendations

$(if [ $BASIC_FAILED -eq 0 ]; then
    echo "1. ✅ Basic functionality is stable - proceed with advanced features"
else
    echo "1. ❌ Fix failing basic tests before implementing new features"
fi)

2. Priority features to implement next:
   - Complete math expression evaluation
   - Implement comparison operators for conditionals
   - Add function definition and calling support
   - Implement for loops with basic iteration

3. System is $(if [ $COMPREHENSIVE_FAILED -eq 0 ]; then echo "ready"; else echo "not ready"; fi) for production deployment

## Test Artifacts

- Full test logs: \`test_infrastructure/logs/\`
- Performance data: \`test_infrastructure/benchmark_results.json\`
- This report: \`$MARKDOWN_REPORT\`

---
*Report generated by XMD Test Infrastructure*
EOF

# Generate HTML Report
cat > "$HTML_REPORT" << EOF
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XMD Test Report - $DATE</title>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background: #f5f5f5;
        }
        .header {
            background: #2c3e50;
            color: white;
            padding: 2rem;
            border-radius: 8px;
            margin-bottom: 2rem;
        }
        .summary {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 1rem;
            margin-bottom: 2rem;
        }
        .card {
            background: white;
            padding: 1.5rem;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .passed { color: #27ae60; font-weight: bold; }
        .failed { color: #e74c3c; font-weight: bold; }
        .skipped { color: #f39c12; font-weight: bold; }
        pre {
            background: #f8f9fa;
            padding: 1rem;
            border-radius: 4px;
            overflow-x: auto;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 1rem 0;
        }
        th, td {
            text-align: left;
            padding: 0.75rem;
            border-bottom: 1px solid #ddd;
        }
        th {
            background: #f8f9fa;
            font-weight: 600;
        }
        .progress {
            width: 100%;
            height: 30px;
            background: #e0e0e0;
            border-radius: 15px;
            overflow: hidden;
        }
        .progress-bar {
            height: 100%;
            background: #27ae60;
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="header">
        <h1>XMD Test Report</h1>
        <p>Generated: $DATE</p>
    </div>
    
    <div class="summary">
        <div class="card">
            <h3>Basic Tests</h3>
            <p class="passed">✅ Passed: $BASIC_PASSED</p>
            <p class="failed">❌ Failed: $BASIC_FAILED</p>
        </div>
        <div class="card">
            <h3>Comprehensive Tests</h3>
            <p class="passed">✅ Passed: $COMPREHENSIVE_PASSED</p>
            <p class="failed">❌ Failed: $COMPREHENSIVE_FAILED</p>
            <p class="skipped">⏭️ Skipped: $COMPREHENSIVE_SKIPPED</p>
        </div>
        <div class="card">
            <h3>Implementation Progress</h3>
            <div class="progress">
                <div class="progress-bar" style="width: $((COMPREHENSIVE_PASSED * 100 / 20))%">
                    $((COMPREHENSIVE_PASSED * 100 / 20))%
                </div>
            </div>
        </div>
    </div>
    
    <div class="card">
        <h2>Test Results</h2>
        <p>See the markdown report for detailed test output.</p>
    </div>
</body>
</html>
EOF

# Generate JSON Report
cat > "$JSON_REPORT" << EOF
{
    "timestamp": "$DATE",
    "version": "$(./build/xmd --version 2>/dev/null || echo "Unknown")",
    "summary": {
        "total_tests": $((BASIC_PASSED + BASIC_FAILED + COMPREHENSIVE_PASSED + COMPREHENSIVE_FAILED + COMPREHENSIVE_SKIPPED)),
        "passed": $((BASIC_PASSED + COMPREHENSIVE_PASSED)),
        "failed": $((BASIC_FAILED + COMPREHENSIVE_FAILED)),
        "skipped": $COMPREHENSIVE_SKIPPED,
        "implementation_percentage": $((COMPREHENSIVE_PASSED * 100 / 20))
    },
    "basic_tests": {
        "passed": $BASIC_PASSED,
        "failed": $BASIC_FAILED
    },
    "comprehensive_tests": {
        "passed": $COMPREHENSIVE_PASSED,
        "failed": $COMPREHENSIVE_FAILED,
        "skipped": $COMPREHENSIVE_SKIPPED
    },
    "deployment_ready": $([ $BASIC_FAILED -eq 0 ] && [ $COMPREHENSIVE_FAILED -eq 0 ] && echo "true" || echo "false")
}
EOF

# Create symlinks to latest reports
ln -sf "test_report_${TIMESTAMP}.md" "$REPORT_DIR/latest.md"
ln -sf "test_report_${TIMESTAMP}.html" "$REPORT_DIR/latest.html"
ln -sf "test_report_${TIMESTAMP}.json" "$REPORT_DIR/latest.json"

echo -e "${GREEN}✅ Test reports generated successfully!${NC}"
echo ""
echo "Reports created:"
echo "- Markdown: $MARKDOWN_REPORT"
echo "- HTML: $HTML_REPORT"
echo "- JSON: $JSON_REPORT"
echo ""
echo "Latest reports available at:"
echo "- $REPORT_DIR/latest.md"
echo "- $REPORT_DIR/latest.html"
echo "- $REPORT_DIR/latest.json"