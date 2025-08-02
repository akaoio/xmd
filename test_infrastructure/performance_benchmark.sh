#!/bin/bash
# XMD Performance Benchmark Suite
# Tests performance characteristics of XMD language features

echo "============================================"
echo "XMD PERFORMANCE BENCHMARK SUITE"
echo "============================================"
echo ""

# Configuration
ITERATIONS=100
BENCHMARK_DIR="test_infrastructure/benchmarks"
RESULTS_FILE="test_infrastructure/benchmark_results.json"
mkdir -p "$BENCHMARK_DIR"

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Function to measure execution time
benchmark() {
    local test_name="$1"
    local test_file="$2"
    local iterations="${3:-$ITERATIONS}"
    
    echo -n "Benchmarking $test_name ($iterations iterations)... "
    
    # Warm up run
    ./build/xmd process "$test_file" > /dev/null 2>&1
    
    # Measure time
    local start_time=$(date +%s.%N)
    
    for i in $(seq 1 $iterations); do
        ./build/xmd process "$test_file" > /dev/null 2>&1
    done
    
    local end_time=$(date +%s.%N)
    local total_time=$(echo "$end_time - $start_time" | bc)
    local avg_time=$(echo "scale=6; $total_time / $iterations" | bc)
    
    echo -e "${GREEN}Average: ${avg_time}s${NC}"
    
    # Return average time in milliseconds
    echo "scale=3; $avg_time * 1000" | bc
}

# Start benchmarking
echo "Preparing benchmark tests..."
echo ""

# Initialize results array
echo "{" > "$RESULTS_FILE"
echo '  "timestamp": "'$(date -u +"%Y-%m-%dT%H:%M:%SZ")'",' >> "$RESULTS_FILE"
echo '  "iterations": '$ITERATIONS',' >> "$RESULTS_FILE"
echo '  "benchmarks": {' >> "$RESULTS_FILE"

# Benchmark 1: Simple variable assignment
cat > "$BENCHMARK_DIR/bench_simple_var.xmd" << 'EOF'
set x 42
{{x}}
EOF
time_simple=$(benchmark "Simple variable" "$BENCHMARK_DIR/bench_simple_var.xmd")
echo '    "simple_variable": '$time_simple',' >> "$RESULTS_FILE"

# Benchmark 2: Multiple variables
cat > "$BENCHMARK_DIR/bench_multi_var.xmd" << 'EOF'
set a 1
set b 2
set c 3
set d 4
set e 5
{{a}} {{b}} {{c}} {{d}} {{e}}
EOF
time_multi=$(benchmark "Multiple variables" "$BENCHMARK_DIR/bench_multi_var.xmd")
echo '    "multiple_variables": '$time_multi',' >> "$RESULTS_FILE"

# Benchmark 3: String interpolation
cat > "$BENCHMARK_DIR/bench_interpolation.xmd" << 'EOF'
set name "World"
set greeting "Hello"
{{greeting}}, {{name}}! Welcome to {{greeting}} {{name}} test.
EOF
time_interp=$(benchmark "String interpolation" "$BENCHMARK_DIR/bench_interpolation.xmd")
echo '    "string_interpolation": '$time_interp',' >> "$RESULTS_FILE"

# Benchmark 4: Large text with variables
cat > "$BENCHMARK_DIR/bench_large_text.xmd" << 'EOF'
set title "Performance Test"
set author "XMD Benchmark"
set date "2025"

# {{title}}

This is a large document created by {{author}} in {{date}}.

Lorem ipsum dolor sit amet, consectetur adipiscing elit. {{title}} is important.
Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. By {{author}}.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris.
This was written in {{date}} for {{title}} purposes.

## Section 1: {{title}}

More text here with {{author}} and {{date}} references.
EOF
time_large=$(benchmark "Large text processing" "$BENCHMARK_DIR/bench_large_text.xmd")
echo '    "large_text_processing": '$time_large',' >> "$RESULTS_FILE"

# Benchmark 5: Math expressions (if working)
cat > "$BENCHMARK_DIR/bench_math.xmd" << 'EOF'
set a 10
set b 20
set c 30
set result a + b + c
{{result}}
EOF
time_math=$(benchmark "Math expressions" "$BENCHMARK_DIR/bench_math.xmd" 50)
echo '    "math_expressions": '$time_math',' >> "$RESULTS_FILE"

# Benchmark 6: Nested structures (if implemented)
cat > "$BENCHMARK_DIR/bench_nested.xmd" << 'EOF'
set x 1
if x = 1
    set y 2
    if y = 2
        set z 3
        Result: {{z}}
    endif
endif
EOF
time_nested=$(benchmark "Nested structures" "$BENCHMARK_DIR/bench_nested.xmd" 50)
echo '    "nested_structures": '$time_nested',' >> "$RESULTS_FILE"

# Benchmark 7: Loop performance (if implemented)
cat > "$BENCHMARK_DIR/bench_loop.xmd" << 'EOF'
for i in 1 2 3 4 5 6 7 8 9 10
    Item {{i}}
endfor
EOF
time_loop=$(benchmark "Loop performance" "$BENCHMARK_DIR/bench_loop.xmd" 50)
echo '    "loop_performance": '$time_loop >> "$RESULTS_FILE"

# Close JSON
echo '  }' >> "$RESULTS_FILE"
echo '}' >> "$RESULTS_FILE"

# Generate summary report
echo ""
echo "============================================"
echo "PERFORMANCE SUMMARY"
echo "============================================"
echo ""

echo "Test Results (milliseconds per execution):"
echo "-----------------------------------------"
printf "%-30s %10s\n" "Test Name" "Avg Time"
printf "%-30s %10s\n" "Simple variable" "${time_simple}ms"
printf "%-30s %10s\n" "Multiple variables" "${time_multi}ms"
printf "%-30s %10s\n" "String interpolation" "${time_interp}ms"
printf "%-30s %10s\n" "Large text processing" "${time_large}ms"
printf "%-30s %10s\n" "Math expressions" "${time_math}ms"
printf "%-30s %10s\n" "Nested structures" "${time_nested}ms"
printf "%-30s %10s\n" "Loop performance" "${time_loop}ms"

echo ""

# Performance analysis
echo "Performance Analysis:"
echo "--------------------"

# Check if basic operations are fast enough
if (( $(echo "$time_simple < 10" | bc -l) )); then
    echo -e "${GREEN}✅ Simple operations are fast (<10ms)${NC}"
else
    echo -e "${YELLOW}⚠️  Simple operations are slow (>10ms)${NC}"
fi

if (( $(echo "$time_large < 50" | bc -l) )); then
    echo -e "${GREEN}✅ Large text processing is acceptable (<50ms)${NC}"
else
    echo -e "${YELLOW}⚠️  Large text processing needs optimization (>50ms)${NC}"
fi

echo ""
echo "Full results saved to: $RESULTS_FILE"
echo ""

# Generate comparison with previous run if exists
if [ -f "$RESULTS_FILE.previous" ]; then
    echo "Comparison with previous run:"
    echo "----------------------------"
    # This would compare with previous results
    echo "(Comparison feature not yet implemented)"
fi

# Save current results as previous for next comparison
cp "$RESULTS_FILE" "$RESULTS_FILE.previous"