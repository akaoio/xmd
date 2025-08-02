#!/bin/bash
# Emergency Build Monitor - Real-time compilation tracking during crisis
# DevOps assignment: Monitor Developer2's build fixes in real-time

echo "========================================"
echo "🚨 EMERGENCY BUILD CRISIS MONITOR"
echo "Real-time tracking of Developer2 fixes"
echo "========================================"

EMERGENCY_LOG="test_infrastructure/logs/emergency_build_fixes.log"
mkdir -p test_infrastructure/logs

# Initialize emergency log
echo "=== EMERGENCY BUILD CRISIS MONITORING STARTED $(date) ===" >> $EMERGENCY_LOG
echo "Crisis: 12 compilation errors blocking all development" >> $EMERGENCY_LOG
echo "Lead: Developer2 assigned to fix build" >> $EMERGENCY_LOG
echo "Monitor: DevOps real-time verification" >> $EMERGENCY_LOG
echo "" >> $EMERGENCY_LOG

fix_attempt=0
last_error_count=12  # Starting point from tester's report

echo "🔍 MONITORING DEVELOPER2 BUILD FIXES..."
echo "Starting error count: 12 (confirmed by Tester)"
echo "Press Ctrl+C to stop monitoring"
echo ""

while true; do
    ((fix_attempt++))
    timestamp=$(date '+%Y-%m-%d %H:%M:%S')
    
    echo "[$timestamp] Fix Attempt #$fix_attempt - Building..."
    
    # Build and capture detailed output
    build_output=$(cmake --build build 2>&1)
    build_exit_code=$?
    
    # Count errors and warnings
    error_count=$(echo "$build_output" | grep -c "error:" || echo 0)
    warning_count=$(echo "$build_output" | grep -c "warning:" || echo 0)
    
    # Log detailed results
    echo "[$timestamp] Fix #$fix_attempt | Exit: $build_exit_code | Errors: $error_count | Warnings: $warning_count" >> $EMERGENCY_LOG
    
    # Console output with progress tracking
    if [ $error_count -lt $last_error_count ]; then
        improvement=$((last_error_count - error_count))
        echo "✅ PROGRESS! Errors reduced: $last_error_count → $error_count (Fixed $improvement errors)"
        echo "[$timestamp] ✅ PROGRESS: Fixed $improvement errors ($last_error_count → $error_count)" >> $EMERGENCY_LOG
        last_error_count=$error_count
    elif [ $error_count -gt $last_error_count ]; then
        regression=$((error_count - last_error_count))
        echo "❌ REGRESSION! Errors increased: $last_error_count → $error_count (+$regression errors)"
        echo "[$timestamp] ❌ REGRESSION: Added $regression errors ($last_error_count → $error_count)" >> $EMERGENCY_LOG
        last_error_count=$error_count
    else
        echo "⚠️ No change: $error_count errors remaining"
    fi
    
    # Check for crisis resolution
    if [ $build_exit_code -eq 0 ] && [ $error_count -eq 0 ]; then
        echo ""
        echo "🎉 BUILD CRISIS RESOLVED!"
        echo "✅ Exit Code: 0 (Success)"
        echo "✅ Errors: 0"
        echo "✅ Warnings: $warning_count"
        
        # Verify binary creation
        if [ -f "build/xmd" ]; then
            binary_size=$(ls -lh build/xmd | awk '{print $5}')
            echo "✅ Binary: Created ($binary_size)"
            
            # Test basic functionality
            version_test=$(./build/xmd --version 2>&1)
            if [ $? -eq 0 ]; then
                echo "✅ Functionality: Basic test passed"
                echo "Version output: $version_test"
                
                # Log success
                echo "[$timestamp] 🎉 BUILD CRISIS RESOLVED!" >> $EMERGENCY_LOG
                echo "[$timestamp] Binary created and functional" >> $EMERGENCY_LOG
                echo "[$timestamp] Ready for phase development" >> $EMERGENCY_LOG
                
                echo ""
                echo "📊 CRISIS RESOLUTION SUMMARY:"
                echo "Fix attempts: $fix_attempt"
                echo "Final status: ✅ SUCCESS"
                echo "Next step: Phase 1 implementation can proceed"
                break
                
            else
                echo "❌ Functionality: Binary created but basic test failed"
                echo "Error: $version_test"
            fi
        else
            echo "❌ Binary: Not created despite successful compilation"
        fi
        
    elif [ $error_count -gt 0 ]; then
        echo "Remaining errors to fix: $error_count"
        
        # Show top 3 errors for Developer2
        echo ""
        echo "📋 TOP ERRORS FOR DEVELOPER2:"
        echo "$build_output" | grep "error:" | head -3 | sed 's/^/   /'
        echo ""
        
        # Log current errors
        echo "[$timestamp] Remaining errors:" >> $EMERGENCY_LOG
        echo "$build_output" | grep "error:" | head -5 >> $EMERGENCY_LOG
        echo "" >> $EMERGENCY_LOG
    fi
    
    # Wait before next check (Developer2 needs time to make fixes)
    sleep 30
done

echo ""
echo "Emergency build monitoring completed."
echo "Full log: $EMERGENCY_LOG"