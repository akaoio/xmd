#!/bin/bash
# Continuous Evaluation Engine Monitor
# Runs evaluation tests every minute and logs progress

MONITOR_LOG="test_infrastructure/logs/evaluation_progress.log"
mkdir -p test_infrastructure/logs

echo "========================================"
echo "XMD EVALUATION ENGINE CONTINUOUS MONITOR"
echo "========================================"
echo "Monitoring evaluation engine completion progress..."
echo "Log file: $MONITOR_LOG"
echo "Press Ctrl+C to stop monitoring"
echo ""

# Initialize log
echo "=== XMD Evaluation Engine Progress Monitor Started $(date) ===" >> $MONITOR_LOG

monitor_cycle=0

while true; do
    ((monitor_cycle++))
    echo "[Cycle $monitor_cycle] Running evaluation tests..."
    
    # Run evaluation tests and capture results
    test_output=$(./test_infrastructure/evaluation_test_runner.sh 2>&1)
    
    # Extract key metrics
    parsing_passed=$(echo "$test_output" | grep "Passed:" | sed 's/.*Passed: //' | sed 's/ .*//')
    parsing_failed=$(echo "$test_output" | grep "Failed:" | sed 's/.*Failed: //' | sed 's/ .*//')
    evaluation_working=$(echo "$test_output" | grep "Working:" | sed 's/.*Working: //' | sed 's/ .*//')
    evaluation_pending=$(echo "$test_output" | grep "Pending:" | sed 's/.*Pending: //' | sed 's/ .*//')
    completion_percent=$(echo "$test_output" | grep "Completion:" | sed 's/.*Completion: //' | sed 's/%//')
    
    # Set defaults if extraction failed
    parsing_passed=${parsing_passed:-0}
    parsing_failed=${parsing_failed:-0}
    evaluation_working=${evaluation_working:-0}
    evaluation_pending=${evaluation_pending:-0}
    completion_percent=${completion_percent:-0}
    
    # Log progress
    timestamp=$(date '+%Y-%m-%d %H:%M:%S')
    echo "[$timestamp] Cycle $monitor_cycle - Parsing: $parsing_passed✅/$parsing_failed❌ | Evaluation: $evaluation_working✅/$evaluation_pending⚠️ | Complete: $completion_percent%" >> $MONITOR_LOG
    
    # Console output
    echo "[$timestamp] Parsing: $parsing_passed✅/$parsing_failed❌ | Evaluation: $evaluation_working✅/$evaluation_pending⚠️ | Complete: $completion_percent%"
    
    # Check for completion
    if [ "$completion_percent" = "100" ] && [ "$parsing_failed" = "0" ]; then
        echo ""
        echo "🎉 EVALUATION ENGINE COMPLETE! All tests passing!"
        echo "[$timestamp] 🎉 EVALUATION ENGINE COMPLETE!" >> $MONITOR_LOG
        break
    fi
    
    # Check for critical regression
    if [ "$parsing_failed" != "0" ]; then
        echo ""
        echo "🚨 CRITICAL: Parsing regression detected! Build may be broken."
        echo "[$timestamp] 🚨 CRITICAL: Parsing regression - $parsing_failed tests failing" >> $MONITOR_LOG
    fi
    
    # Wait before next cycle
    sleep 60
done

echo ""
echo "Monitoring completed. Check log file for full history: $MONITOR_LOG"