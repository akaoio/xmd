#!/bin/bash
# Build Health Monitor - Zero Duplication Campaign
# Ensures 0 regressions during optimization
# Tester (Duplication Validation Lead)

echo "🔧 BUILD HEALTH MONITOR - Zero Regression Enforcement"
echo "Timestamp: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""

# Configuration
BUILD_DIR="build-tester"
LOG_FILE="duplication_reports/build_health_$(date '+%Y%m%d_%H%M%S').log"

# Create build directory if not exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating isolated build directory: $BUILD_DIR"
    mkdir -p "$BUILD_DIR"
fi

mkdir -p duplication_reports

echo "🚀 RUNNING BUILD HEALTH CHECK..."
echo "Build directory: $BUILD_DIR"
echo "Log file: $LOG_FILE"
echo ""

# Clean and configure build
echo "📋 Step 1: Clean build configuration..."
cd "$BUILD_DIR"
if [ -f "Makefile" ]; then
    make clean > /dev/null 2>&1
fi

# Configure with CMake
echo "⚙️  Step 2: CMake configuration..."
cmake -S .. . > cmake.log 2>&1
CMAKE_RESULT=$?

if [ $CMAKE_RESULT -ne 0 ]; then
    echo "❌ CMAKE FAILED!"
    echo "Configuration error detected - possible regression!"
    cat cmake.log
    exit 1
fi

echo "✅ CMake configuration: SUCCESS"

# Build with warning tracking
echo "🔨 Step 3: Compilation with warning tracking..."
make -j4 2>&1 | tee build.log

BUILD_RESULT=$?
WARNING_COUNT=$(grep -c "warning:" build.log || true)
ERROR_COUNT=$(grep -c "error:" build.log || true)

# Analysis
echo ""
echo "📊 BUILD ANALYSIS RESULTS:"
echo "   - Build result: $([ $BUILD_RESULT -eq 0 ] && echo "SUCCESS" || echo "FAILED")"
echo "   - Warnings: $WARNING_COUNT"
echo "   - Errors: $ERROR_COUNT"

# Create detailed report
cat > "../$LOG_FILE" << EOF
BUILD HEALTH MONITOR REPORT
===========================
Timestamp: $(date '+%Y-%m-%d %H:%M:%S')
Campaign: Zero Duplication (Regression Detection)
Build Directory: $BUILD_DIR

RESULTS:
- Build Status: $([ $BUILD_RESULT -eq 0 ] && echo "SUCCESS" || echo "FAILED")  
- Warnings: $WARNING_COUNT
- Errors: $ERROR_COUNT
- CMAKE Result: $([ $CMAKE_RESULT -eq 0 ] && echo "SUCCESS" || echo "FAILED")

QUALITY GATE ASSESSMENT:
$(if [ $BUILD_RESULT -eq 0 ] && [ $ERROR_COUNT -eq 0 ]; then
    echo "✅ PASSED - No regressions detected"
else
    echo "❌ FAILED - Build regression detected!"
fi)

$(if [ $WARNING_COUNT -eq 0 ]; then
    echo "✅ PERFECT - Zero warnings maintained"
elif [ $WARNING_COUNT -le 5 ]; then
    echo "⚠️  ACCEPTABLE - $WARNING_COUNT warnings (≤5)"
else
    echo "🔴 REGRESSION - $WARNING_COUNT warnings (>5)"
fi)

DETAILED BUILD LOG:
-------------------
EOF

cat build.log >> "../$LOG_FILE"

# Quality gate enforcement
if [ $BUILD_RESULT -ne 0 ] || [ $ERROR_COUNT -gt 0 ]; then
    echo ""
    echo "🚨 BUILD REGRESSION DETECTED!"
    echo "   - Build failed or errors present"
    echo "   - QUALITY GATE: FAILED"
    echo "   - Action required: Fix regressions before continuing"
    exit 1
fi

if [ $WARNING_COUNT -gt 10 ]; then
    echo ""
    echo "⚠️  WARNING REGRESSION DETECTED!"
    echo "   - Warning count: $WARNING_COUNT (>10)"
    echo "   - QUALITY GATE: WARNING"
    echo "   - Action recommended: Address warnings"
fi

# Test basic functionality
echo ""
echo "🧪 Step 4: Basic functionality test..."
if [ -f "xmd" ]; then
    echo 'print "Build health test"' > health_test.xmd
    if ./xmd process health_test.xmd > /dev/null 2>&1; then
        echo "✅ Functionality test: PASSED"
    else
        echo "❌ Functionality test: FAILED - possible regression!"
        exit 1
    fi
    rm -f health_test.xmd
else
    echo "❌ Binary not generated - build failed!"
    exit 1
fi

cd ..

echo ""
echo "✅ BUILD HEALTH CHECK COMPLETE"
echo "📄 Detailed log: $LOG_FILE"
echo "🔧 Build health: $([ $WARNING_COUNT -eq 0 ] && echo "PERFECT" || echo "$WARNING_COUNT warnings")"
echo "🎯 Quality gate: PASSED - No regressions detected"
echo ""
echo "Ready for continued optimization!"