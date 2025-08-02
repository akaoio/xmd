#!/bin/bash

# 🛡️ XMD VIOLATION DETECTION AUTOMATION SCRIPT
# Author: DEBTHUNTER Team
# Purpose: Automated violation detection với comprehensive reporting

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Configuration
REPORT_FILE="dead_code_report.json"
HEALTH_LOG="xmd_health.log"
TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')

# Banner
echo -e "${BOLD}${BLUE}"
echo "🛡️ =============================================="
echo "   XMD VIOLATION DETECTION AUTOMATION"
echo "   Time: $TIMESTAMP"
echo "===============================================${NC}"
echo

# Function: Print colored message
print_status() {
    local color=$1
    local message=$2
    echo -e "${color}${message}${NC}"
}

# Function: Check if tools exist
check_tools() {
    print_status $BLUE "🔧 Checking violation detection tools..."
    
    if [ ! -f "./tools/analyzer/dead_function_detector" ]; then
        print_status $RED "❌ Dead function detector not found. Building..."
        if [ -f "./build-tools/dead-function-detector.sh" ]; then
            ./build-tools/dead-function-detector.sh
        else
            print_status $RED "❌ Build script not found. Please build tools manually."
            exit 1
        fi
    fi
    
    print_status $GREEN "✅ Tools ready"
}

# Function: Run violation detection
run_detection() {
    print_status $BLUE "🔍 Running violation detection analysis..."
    
    # Run the detector
    ./tools/analyzer/dead_function_detector "$@"
    
    if [ ! -f "$REPORT_FILE" ]; then
        print_status $RED "❌ Detection failed - no report generated"
        exit 1
    fi
    
    print_status $GREEN "✅ Analysis complete"
}

# Function: Parse and display results
display_results() {
    print_status $BLUE "📊 Analyzing results..."
    
    # Check if jq is available for JSON parsing
    if ! command -v jq &> /dev/null; then
        print_status $YELLOW "⚠️  jq not available, showing raw summary..."
        grep -A 10 "summary" "$REPORT_FILE" || head -20 "$REPORT_FILE"
        return
    fi
    
    # Extract metrics
    local ghost_count=$(jq '.summary.ghost_functions_count' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    local dead_count=$(jq '.summary.dead_functions_count' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    local total_defined=$(jq '.summary.total_defined_functions' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    local total_called=$(jq '.summary.total_called_functions' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    local duplicates=$(jq '.summary.potential_duplicates' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    
    # Display summary
    echo -e "${BOLD}📋 VIOLATION SUMMARY:${NC}"
    echo "────────────────────────────────────"
    
    # Ghost functions (critical)
    if [ "$ghost_count" != "unknown" ] && [ "$ghost_count" -gt 0 ]; then
        print_status $RED "👻 Ghost Functions: $ghost_count (NEEDS ATTENTION)"
    else
        print_status $GREEN "👻 Ghost Functions: $ghost_count"
    fi
    
    # Dead functions
    if [ "$dead_count" != "unknown" ] && [ "$dead_count" -gt 0 ]; then
        print_status $YELLOW "💀 Dead Functions: $dead_count (CAN BE CLEANED)"
    else
        print_status $GREEN "💀 Dead Functions: $dead_count"
    fi
    
    # Total functions
    print_status $BLUE "📁 Total Defined Functions: $total_defined"
    print_status $BLUE "📞 Total Called Functions: $total_called"
    
    # Duplicates
    if [ "$duplicates" != "unknown" ] && [ "$duplicates" -gt 0 ]; then
        print_status $YELLOW "🔄 Potential Duplicates: $duplicates"
    else
        print_status $GREEN "🔄 Potential Duplicates: $duplicates"
    fi
    
    # Calculate health score
    if [ "$ghost_count" != "unknown" ] && [ "$total_called" != "unknown" ] && [ "$total_called" -gt 0 ]; then
        local implemented=$((total_called - ghost_count))
        local health_percent=$((implemented * 100 / total_called))
        
        echo "────────────────────────────────────"
        if [ "$health_percent" -ge 90 ]; then
            print_status $GREEN "🏆 Health Score: ${health_percent}% (EXCELLENT)"
        elif [ "$health_percent" -ge 70 ]; then
            print_status $YELLOW "⚠️  Health Score: ${health_percent}% (GOOD)"
        else
            print_status $RED "🚨 Health Score: ${health_percent}% (NEEDS WORK)"
        fi
    fi
}

# Function: Show critical violations
show_critical() {
    if ! command -v jq &> /dev/null; then
        print_status $YELLOW "⚠️  jq not available for detailed analysis"
        return
    fi
    
    print_status $BLUE "🚨 Analyzing critical violations..."
    
    # Critical ghost functions (called from main.c or public headers)
    local critical_ghosts=$(jq '.ghost_functions[] | select(.calls[].file | test("main.c|xmd.h")) | .name' "$REPORT_FILE" 2>/dev/null | wc -l)
    
    if [ "$critical_ghosts" -gt 0 ]; then
        echo -e "${BOLD}${RED}🚨 CRITICAL GHOST FUNCTIONS (Build Blockers):${NC}"
        jq -r '.ghost_functions[] | select(.calls[].file | test("main.c|xmd.h")) | "  • \(.name) (called from: \([.calls[].file] | unique | join(", ")))"' "$REPORT_FILE" 2>/dev/null
        echo
    fi
    
    # High-priority ghost functions (XMD-specific)
    local xmd_ghosts=$(jq '.ghost_functions[] | select(.name | test("^(xmd_|ast_|config_)")) | .name' "$REPORT_FILE" 2>/dev/null | wc -l)
    
    if [ "$xmd_ghosts" -gt 0 ]; then
        echo -e "${BOLD}${YELLOW}⚡ HIGH-PRIORITY GHOST FUNCTIONS (XMD Core):${NC}"
        jq -r '.ghost_functions[] | select(.name | test("^(xmd_|ast_|config_)")) | "  • \(.name) (called \(.calls | length) times)"' "$REPORT_FILE" 2>/dev/null | head -10
        echo
    fi
}

# Function: Generate recommendations
generate_recommendations() {
    if ! command -v jq &> /dev/null; then
        return
    fi
    
    local ghost_count=$(jq '.summary.ghost_functions_count' "$REPORT_FILE" 2>/dev/null || echo "0")
    local dead_count=$(jq '.summary.dead_functions_count' "$REPORT_FILE" 2>/dev/null || echo "0")
    
    print_status $BLUE "💡 RECOMMENDATIONS:"
    echo "────────────────────────────────────"
    
    if [ "$ghost_count" -gt 0 ]; then
        echo -e "${YELLOW}1. Implement ghost functions:${NC}"
        echo "   • Start với functions called from main.c"
        echo "   • Prioritize xmd_*, ast_*, config_* functions"
        echo "   • Follow Genesis principles: 1 function → 1 file → 1 directory"
        echo
    fi
    
    if [ "$dead_count" -gt 0 ]; then
        echo -e "${YELLOW}2. Clean up dead functions:${NC}"
        echo "   • Verify functions are truly unused với 'grep -r function_name src/'"
        echo "   • Remove unused functions và empty directories"
        echo "   • Update CMakeLists.txt if needed"
        echo
    fi
    
    echo -e "${GREEN}3. Maintain code quality:${NC}"
    echo "   • Run this tool regularly (weekly/before commits)"
    echo "   • Keep ghost functions count < 10 for healthy codebase"
    echo "   • Document any intentionally unused functions"
}

# Function: Log results
log_results() {
    if ! command -v jq &> /dev/null; then
        return
    fi
    
    local ghost_count=$(jq '.summary.ghost_functions_count' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    local dead_count=$(jq '.summary.dead_functions_count' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    local total_defined=$(jq '.summary.total_defined_functions' "$REPORT_FILE" 2>/dev/null || echo "unknown")
    
    # Append to health log
    echo "$TIMESTAMP,ghost:$ghost_count,dead:$dead_count,total:$total_defined" >> "$HEALTH_LOG"
    
    print_status $GREEN "📝 Results logged to $HEALTH_LOG"
}

# Function: Show usage
show_usage() {
    echo "Usage: $0 [OPTIONS] [DIRECTORY]"
    echo
    echo "Options:"
    echo "  -h, --help          Show this help message"
    echo "  -q, --quick         Quick scan only (no detailed analysis)"
    echo "  -c, --critical      Show only critical violations"
    echo "  --no-log            Don't log results"
    echo
    echo "Directory:"
    echo "  Optional path to scan (default: entire src/ directory)"
    echo
    echo "Examples:"
    echo "  $0                    # Full scan with detailed analysis"
    echo "  $0 -q                 # Quick scan"
    echo "  $0 -c                 # Show only critical issues"
    echo "  $0 src/ast/           # Scan specific directory"
}

# Parse command line arguments
QUICK_MODE=false
CRITICAL_ONLY=false
NO_LOG=false
SCAN_DIR=""

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_usage
            exit 0
            ;;
        -q|--quick)
            QUICK_MODE=true
            shift
            ;;
        -c|--critical)
            CRITICAL_ONLY=true
            shift
            ;;
        --no-log)
            NO_LOG=true
            shift
            ;;
        -*)
            print_status $RED "Unknown option: $1"
            show_usage
            exit 1
            ;;
        *)
            SCAN_DIR="$1"
            shift
            ;;
    esac
done

# Main execution
main() {
    check_tools
    
    if [ -n "$SCAN_DIR" ]; then
        print_status $BLUE "🎯 Scanning directory: $SCAN_DIR"
        run_detection "$SCAN_DIR"
    else
        print_status $BLUE "🎯 Scanning entire codebase..."
        run_detection
    fi
    
    display_results
    
    if [ "$CRITICAL_ONLY" = true ]; then
        show_critical
    elif [ "$QUICK_MODE" = false ]; then
        echo
        show_critical
        echo
        generate_recommendations
    fi
    
    if [ "$NO_LOG" = false ]; then
        echo
        log_results
    fi
    
    # Final status
    if command -v jq &> /dev/null; then
        local ghost_count=$(jq '.summary.ghost_functions_count' "$REPORT_FILE" 2>/dev/null || echo "0")
        echo
        if [ "$ghost_count" -eq 0 ]; then
            print_status $GREEN "🎉 EXCELLENT: Codebase is clean!"
        elif [ "$ghost_count" -lt 10 ]; then
            print_status $YELLOW "👍 GOOD: Only $ghost_count ghost functions remaining"
        else
            print_status $RED "⚠️  ATTENTION NEEDED: $ghost_count ghost functions require implementation"
        fi
    fi
    
    echo
    print_status $BLUE "📄 Detailed results saved to: $REPORT_FILE"
    print_status $BLUE "🔍 Use 'cat $REPORT_FILE | jq' for detailed JSON analysis"
}

# Run main function
main "$@"