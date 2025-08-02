#!/bin/bash
# XMD Continuous Testing Monitor
# Runs tests continuously and reports status

echo "============================================"
echo "XMD CONTINUOUS TESTING MONITOR"
echo "Starting continuous test execution..."
echo "============================================"
echo ""

# Configuration
TEST_INTERVAL=300  # Run tests every 5 minutes
LOG_DIR="test_infrastructure/logs"
mkdir -p "$LOG_DIR"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Function to run all tests
run_all_tests() {
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    local log_file="$LOG_DIR/test_run_$(date +%Y%m%d_%H%M%S).log"
    
    echo ""
    echo "[$timestamp] Starting test run..."
    echo "============================================" | tee "$log_file"
    echo "Test Run: $timestamp" | tee -a "$log_file"
    echo "============================================" | tee -a "$log_file"
    
    # Run basic tests
    echo "" | tee -a "$log_file"
    echo "Running basic test suite..." | tee -a "$log_file"
    if ./test_infrastructure/test_runner.sh >> "$log_file" 2>&1; then
        echo -e "${GREEN}✅ Basic tests PASSED${NC}"
    else
        echo -e "${RED}❌ Basic tests FAILED${NC}"
    fi
    
    # Run comprehensive tests
    echo "" | tee -a "$log_file"
    echo "Running comprehensive test suite..." | tee -a "$log_file"
    if ./test_infrastructure/comprehensive_test_suite.sh >> "$log_file" 2>&1; then
        echo -e "${GREEN}✅ Comprehensive tests PASSED${NC}"
    else
        echo -e "${YELLOW}⚠️  Some comprehensive tests failed or skipped${NC}"
    fi
    
    # Check build status
    echo "" | tee -a "$log_file"
    echo "Checking build status..." | tee -a "$log_file"
    if ./build.sh >> "$log_file" 2>&1; then
        echo -e "${GREEN}✅ Build successful${NC}"
    else
        echo -e "${RED}❌ Build failed${NC}"
    fi
    
    # Generate summary
    echo "" | tee -a "$log_file"
    echo "Test Summary:" | tee -a "$log_file"
    echo "-------------" | tee -a "$log_file"
    
    # Count results from log
    local passed=$(grep -c "✅ PASSED" "$log_file" || echo 0)
    local failed=$(grep -c "❌ FAILED" "$log_file" || echo 0)
    local skipped=$(grep -c "⏭️  SKIPPED" "$log_file" || echo 0)
    
    echo "Tests Passed: $passed" | tee -a "$log_file"
    echo "Tests Failed: $failed" | tee -a "$log_file"
    echo "Tests Skipped: $skipped" | tee -a "$log_file"
    
    # Save summary to latest.json for monitoring tools
    cat > "$LOG_DIR/latest.json" <<EOF
{
    "timestamp": "$timestamp",
    "passed": $passed,
    "failed": $failed,
    "skipped": $skipped,
    "build_status": $([ -f build/xmd ] && echo "true" || echo "false"),
    "log_file": "$log_file"
}
EOF
    
    return $failed
}

# Function to clean old logs
clean_old_logs() {
    # Keep only last 100 log files
    local log_count=$(ls -1 "$LOG_DIR"/test_run_*.log 2>/dev/null | wc -l)
    if [ "$log_count" -gt 100 ]; then
        ls -1t "$LOG_DIR"/test_run_*.log | tail -n +101 | xargs rm -f
    fi
}

# Signal handler for graceful shutdown
cleanup() {
    echo ""
    echo "Shutting down continuous monitoring..."
    exit 0
}

trap cleanup SIGINT SIGTERM

# Main monitoring loop
echo "Monitoring will run tests every $TEST_INTERVAL seconds."
echo "Press Ctrl+C to stop monitoring."
echo ""

while true; do
    run_all_tests
    clean_old_logs
    
    echo ""
    echo "Next test run in $TEST_INTERVAL seconds..."
    echo "============================================"
    
    # Sleep with ability to interrupt
    for i in $(seq $TEST_INTERVAL); do
        sleep 1
        # Show countdown for last 10 seconds
        remaining=$((TEST_INTERVAL - i))
        if [ $remaining -le 10 ] && [ $remaining -gt 0 ]; then
            echo -ne "\rStarting in $remaining seconds...  "
        fi
    done
    echo -ne "\r                                    \r"
done