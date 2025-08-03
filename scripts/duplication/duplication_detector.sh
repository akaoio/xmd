#!/bin/bash
# XMD Real-time Duplication Detection Script
# Zero Duplication Campaign - Tester (Duplication Validation Lead)
# Target: 57.7% → <20% in 24 hours

set -e

echo "=== XMD REAL-TIME DUPLICATION DETECTOR ==="
echo "Campaign: ZERO DUPLICATION - 57.7% → <20%"
echo "Lead: Tester (Quality + Infrastructure)"
echo "Timestamp: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""

# Configuration
SRC_DIR="${1:-src}"
REPORT_DIR="duplication_reports"
TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
REPORT_FILE="$REPORT_DIR/duplication_report_$TIMESTAMP.txt"

# Create report directory
mkdir -p "$REPORT_DIR"

echo "📊 DUPLICATION ANALYSIS STARTING..."
echo "Source directory: $SRC_DIR"
echo "Report file: $REPORT_FILE"
echo ""

# Initialize report
cat > "$REPORT_FILE" << EOF
XMD DUPLICATION ANALYSIS REPORT
================================
Timestamp: $(date '+%Y-%m-%d %H:%M:%S')
Campaign: ZERO DUPLICATION (57.7% → <20%)
Lead: Tester (Duplication Validation Lead)

EOF

# Function to detect duplicate code patterns
detect_duplicates() {
    echo "🔍 DETECTING CODE PATTERNS..."
    
    # Find all C files
    find "$SRC_DIR" -name "*.c" -type f > /tmp/c_files.txt
    TOTAL_FILES=$(cat /tmp/c_files.txt | wc -l)
    
    echo "Total C files: $TOTAL_FILES"
    echo "Files scanned: $TOTAL_FILES" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Pattern detection
    echo "📋 PATTERN ANALYSIS:" >> "$REPORT_FILE"
    
    # 1. Memory allocation patterns
    echo "1. MEMORY ALLOCATION PATTERNS:" >> "$REPORT_FILE"
    MALLOC_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "xmd_malloc\|malloc" {} \; | wc -l)
    FREE_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "xmd_free\|free" {} \; | wc -l)
    echo "   - Files with malloc patterns: $MALLOC_PATTERNS" >> "$REPORT_FILE"
    echo "   - Files with free patterns: $FREE_PATTERNS" >> "$REPORT_FILE"
    
    # 2. Error handling patterns
    echo "2. ERROR HANDLING PATTERNS:" >> "$REPORT_FILE"
    ERROR_RETURN_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "XMD_ERROR_RETURN\|return NULL" {} \; | wc -l)
    NULL_CHECK_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "XMD_NULL_CHECK\|if.*NULL" {} \; | wc -l)
    echo "   - Files with error return patterns: $ERROR_RETURN_PATTERNS" >> "$REPORT_FILE"
    echo "   - Files with null check patterns: $NULL_CHECK_PATTERNS" >> "$REPORT_FILE"
    
    # 3. AST creation patterns
    echo "3. AST CREATION PATTERNS:" >> "$REPORT_FILE"
    AST_CREATE_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "ast_.*_create\|XMD_CREATE" {} \; | wc -l)
    AST_FREE_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "ast_.*_free\|XMD_FREE" {} \; | wc -l)
    echo "   - Files with AST creation patterns: $AST_CREATE_PATTERNS" >> "$REPORT_FILE"
    echo "   - Files with AST free patterns: $AST_FREE_PATTERNS" >> "$REPORT_FILE"
    
    # 4. Parser patterns
    echo "4. PARSER PATTERNS:" >> "$REPORT_FILE"
    PARSER_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "ast_parse_\|token_" {} \; | wc -l)
    echo "   - Files with parser patterns: $PARSER_PATTERNS" >> "$REPORT_FILE"
    
    # 5. Evaluator patterns
    echo "5. EVALUATOR PATTERNS:" >> "$REPORT_FILE"
    EVALUATOR_PATTERNS=$(find "$SRC_DIR" -name "*.c" -exec grep -l "ast_evaluate_\|evaluator" {} \; | wc -l)
    echo "   - Files with evaluator patterns: $EVALUATOR_PATTERNS" >> "$REPORT_FILE"
    
    echo "" >> "$REPORT_FILE"
}

# Function to find exact duplicate lines
find_exact_duplicates() {
    echo "🔄 FINDING EXACT DUPLICATES..."
    echo "EXACT DUPLICATE ANALYSIS:" >> "$REPORT_FILE"
    
    # Create temporary file with all code lines
    find "$SRC_DIR" -name "*.c" -exec cat {} \; | \
    grep -v "^[[:space:]]*$" | \
    grep -v "^[[:space:]]*#" | \
    grep -v "^[[:space:]]*//" | \
    sort | uniq -d > /tmp/duplicate_lines.txt
    
    DUPLICATE_LINES=$(cat /tmp/duplicate_lines.txt | wc -l)
    echo "   - Exact duplicate lines found: $DUPLICATE_LINES" >> "$REPORT_FILE"
    
    if [ "$DUPLICATE_LINES" -gt 0 ]; then
        echo "   - Top 10 most duplicated lines:" >> "$REPORT_FILE"
        head -10 /tmp/duplicate_lines.txt | while read line; do
            COUNT=$(find "$SRC_DIR" -name "*.c" -exec grep -F "$line" {} \; | wc -l)
            echo "     [$COUNT times] $line" >> "$REPORT_FILE"
        done
    fi
    echo "" >> "$REPORT_FILE"
}

# Function to calculate duplication percentage
calculate_duplication_percentage() {
    echo "📊 CALCULATING DUPLICATION PERCENTAGE..."
    
    # Total lines of code (excluding comments and empty lines)
    TOTAL_LOC=$(find "$SRC_DIR" -name "*.c" -exec cat {} \; | \
                grep -v "^[[:space:]]*$" | \
                grep -v "^[[:space:]]*#" | \
                grep -v "^[[:space:]]*//" | wc -l)
    
    # Unique lines of code
    UNIQUE_LOC=$(find "$SRC_DIR" -name "*.c" -exec cat {} \; | \
                 grep -v "^[[:space:]]*$" | \
                 grep -v "^[[:space:]]*#" | \
                 grep -v "^[[:space:]]*//" | \
                 sort | uniq | wc -l)
    
    # Calculate duplication percentage
    if [ "$TOTAL_LOC" -gt 0 ]; then
        DUPLICATION_PERCENTAGE=$(echo "scale=1; 100 * (1 - $UNIQUE_LOC / $TOTAL_LOC)" | bc -l)
    else
        DUPLICATION_PERCENTAGE="0.0"
    fi
    
    echo "DUPLICATION METRICS:" >> "$REPORT_FILE"
    echo "   - Total lines of code: $TOTAL_LOC" >> "$REPORT_FILE"
    echo "   - Unique lines of code: $UNIQUE_LOC" >> "$REPORT_FILE"
    echo "   - Duplicate lines: $(($TOTAL_LOC - $UNIQUE_LOC))" >> "$REPORT_FILE"
    echo "   - DUPLICATION PERCENTAGE: $DUPLICATION_PERCENTAGE%" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Display results
    echo "📈 CURRENT DUPLICATION: $DUPLICATION_PERCENTAGE%"
    
    # Set color based on percentage
    if (( $(echo "$DUPLICATION_PERCENTAGE < 20" | bc -l) )); then
        echo "🟢 TARGET ACHIEVED: <20% duplication!"
    elif (( $(echo "$DUPLICATION_PERCENTAGE < 30" | bc -l) )); then
        echo "🟡 GOOD PROGRESS: <30% duplication"
    elif (( $(echo "$DUPLICATION_PERCENTAGE < 45" | bc -l) )); then
        echo "🟠 MODERATE PROGRESS: <45% duplication"
    else
        echo "🔴 HIGH DUPLICATION: >45% - URGENT ACTION NEEDED"
    fi
    
    echo "CURRENT_DUPLICATION=$DUPLICATION_PERCENTAGE" > /tmp/duplication_percentage.txt
}

# Function to identify top duplication hotspots
identify_hotspots() {
    echo "🎯 IDENTIFYING DUPLICATION HOTSPOTS..."
    echo "DUPLICATION HOTSPOTS:" >> "$REPORT_FILE"
    
    # Find files with most potential for consolidation
    echo "   - Top directories by file count:" >> "$REPORT_FILE"
    find "$SRC_DIR" -name "*.c" -type f | sed 's|/[^/]*$||' | sort | uniq -c | sort -nr | head -10 | \
    while read count dir; do
        echo "     $dir: $count files" >> "$REPORT_FILE"
    done
    
    echo "   - Files with common patterns (consolidation candidates):" >> "$REPORT_FILE"
    
    # Find ast_create patterns
    AST_CREATE_FILES=$(find "$SRC_DIR" -path "*/ast/node/create/*" -name "*.c" | wc -l)
    echo "     ast/node/create/ directory: $AST_CREATE_FILES files" >> "$REPORT_FILE"
    
    # Find ast_evaluator patterns  
    AST_EVAL_FILES=$(find "$SRC_DIR" -path "*/ast/evaluator/*" -name "*.c" | wc -l)
    echo "     ast/evaluator/ directory: $AST_EVAL_FILES files" >> "$REPORT_FILE"
    
    # Find ast_parser patterns
    AST_PARSER_FILES=$(find "$SRC_DIR" -path "*/ast/parser/*" -name "*.c" | wc -l)
    echo "     ast/parser/ directory: $AST_PARSER_FILES files" >> "$REPORT_FILE"
    
    echo "" >> "$REPORT_FILE"
}

# Function to suggest optimization targets
suggest_optimizations() {
    echo "💡 OPTIMIZATION SUGGESTIONS:" >> "$REPORT_FILE"
    echo "   
RECOMMENDED ACTIONS:
1. IMMEDIATE (Developer):
   - Consolidate ast/node/create/* files using XMD_CREATE_VALIDATED macro
   - Apply XMD_PARSER_COMMON pattern to ast/parser/* files
   - Implement XMD_EVALUATOR_STANDARD in ast/evaluator/* files

2. SHORT-TERM (Debthunter):
   - Pattern consolidation: memory allocation, error handling
   - Macro application blitz: XMD_* pattern enforcement
   - Dead code elimination: unused functions, redundant includes

3. VALIDATION (Tester):
   - Monitor progress every 30 minutes
   - Validate 0 regressions after each optimization
   - Track build health throughout campaign

TARGET MILESTONES:
- 2h: 57.7% → 45% (Developer macro consolidation)
- 4h: 45% → 35% (Combined team effort)  
- 6h: 35% → 25% (Debthunter pattern optimization)
- 24h: 25% → <20% (Final cleanup and validation)
" >> "$REPORT_FILE"
}

# Main execution
echo "🚀 STARTING DUPLICATION ANALYSIS..."

detect_duplicates
find_exact_duplicates  
calculate_duplication_percentage
identify_hotspots
suggest_optimizations

# Final report summary
echo "" >> "$REPORT_FILE"
echo "ANALYSIS COMPLETE - $(date '+%Y-%m-%d %H:%M:%S')" >> "$REPORT_FILE"
echo "Next scan recommended in 30 minutes" >> "$REPORT_FILE"

echo ""
echo "✅ DUPLICATION ANALYSIS COMPLETE"
echo "📄 Report saved: $REPORT_FILE"
echo "📊 Current duplication: $(cat /tmp/duplication_percentage.txt | cut -d= -f2)%"
echo ""
echo "🎯 ZERO DUPLICATION CAMPAIGN - ACTIVE MONITORING"
echo "Next measurement in 30 minutes for progress tracking"