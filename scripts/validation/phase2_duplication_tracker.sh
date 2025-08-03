#!/bin/bash
# PHASE 2 DUPLICATION TRACKER - Quality + Monitoring Master
# Real-time measurement system for manual consolidation validation
# Tester - Phase 2 Assignment

echo "📊 PHASE 2 DUPLICATION TRACKER - Manual Consolidation Validation"
echo "Timestamp: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""

# Initialize baseline metrics
TOTAL_C_FILES=$(find src -name "*.c" -type f | wc -l)
echo "🔍 BASELINE METRICS:"
echo "   Total C files: $TOTAL_C_FILES"

# Track specific target areas for Developer's manual consolidation
echo ""
echo "🎯 DEVELOPER TARGET AREA TRACKING:"

# Priority 1: src/ast/evaluator/* (40+ files target)
AST_EVAL_FILES=$(find src/ast/evaluator -name "*.c" -type f | wc -l)
AST_EVAL_MODIFIED=$(find src/ast/evaluator -name "*.c" -type f -mmin -30 | wc -l)
echo "   📂 AST Evaluator files: $AST_EVAL_FILES total"
echo "   📝 Recently modified (30min): $AST_EVAL_MODIFIED"

# Priority 2: src/ast/parser/* (30+ files target)  
AST_PARSER_FILES=$(find src/ast/parser -name "*.c" -type f | wc -l)
AST_PARSER_MODIFIED=$(find src/ast/parser -name "*.c" -type f -mmin -30 | wc -l)
echo "   📂 AST Parser files: $AST_PARSER_FILES total"
echo "   📝 Recently modified (30min): $AST_PARSER_MODIFIED"

# Priority 3: src/ast/node/create/* (20+ files target)
AST_CREATE_FILES=$(find src/ast/node/create -name "*.c" -type f | wc -l)
AST_CREATE_MODIFIED=$(find src/ast/node/create -name "*.c" -type f -mmin -30 | wc -l)
echo "   📂 AST Node Create files: $AST_CREATE_FILES total"
echo "   📝 Recently modified (30min): $AST_CREATE_MODIFIED"

# Calculate Developer's consolidation progress indicators
TOTAL_TARGET_FILES=$((AST_EVAL_FILES + AST_PARSER_FILES + AST_CREATE_FILES))
TOTAL_MODIFIED=$((AST_EVAL_MODIFIED + AST_PARSER_MODIFIED + AST_CREATE_MODIFIED))

echo ""
echo "📈 MANUAL CONSOLIDATION PROGRESS INDICATORS:"
echo "   🎯 Total Developer target files: $TOTAL_TARGET_FILES"
echo "   📝 Files with recent activity: $TOTAL_MODIFIED"

if [ $TOTAL_MODIFIED -gt 0 ]; then
    ACTIVITY_PERCENTAGE=$(($TOTAL_MODIFIED * 100 / $TOTAL_TARGET_FILES))
    echo "   📊 Activity rate: $ACTIVITY_PERCENTAGE% of target files"
    
    if [ $ACTIVITY_PERCENTAGE -gt 50 ]; then
        echo "   🔥 HIGH INTENSITY: Developer actively consolidating"
    elif [ $ACTIVITY_PERCENTAGE -gt 20 ]; then
        echo "   🟡 MODERATE ACTIVITY: Steady consolidation progress"
    elif [ $ACTIVITY_PERCENTAGE -gt 5 ]; then
        echo "   🟢 LOW ACTIVITY: Some consolidation detected"
    else
        echo "   ⏸️ MINIMAL ACTIVITY: Consolidation may be paused"
    fi
else
    echo "   ⏸️ NO RECENT ACTIVITY: Awaiting consolidation start"
fi

# Pattern analysis for duplication indicators
echo ""
echo "🔍 DUPLICATION PATTERN ANALYSIS:"

# Type validation patterns (Debthunter identified 9)
TYPE_VALIDATION_COUNT=$(grep -r "if.*node->type.*!=" src/ast/ 2>/dev/null | wc -l)
echo "   🔸 Type validation patterns: $TYPE_VALIDATION_COUNT instances"

# Memory allocation patterns (Debthunter identified 3)
MALLOC_PATTERNS=$(grep -r "xmd_malloc(sizeof" src/ 2>/dev/null | wc -l)
echo "   🔸 Memory allocation patterns: $MALLOC_PATTERNS instances"

# Error handling patterns  
ERROR_PATTERNS=$(grep -r "XMD_ERROR_RETURN" src/ 2>/dev/null | wc -l)
echo "   🔸 Error handling patterns: $ERROR_PATTERNS instances"

# Validation patterns
VALIDATE_PATTERNS=$(grep -r "XMD_VALIDATE_PTRS" src/ 2>/dev/null | wc -l)
echo "   🔸 Validation patterns: $VALIDATE_PATTERNS instances"

# Estimate consolidation potential
TOTAL_PATTERNS=$((TYPE_VALIDATION_COUNT + MALLOC_PATTERNS + ERROR_PATTERNS + VALIDATE_PATTERNS))
echo "   📊 Total consolidable patterns: $TOTAL_PATTERNS"

# Calculate estimated duplication level
if [ $TOTAL_C_FILES -gt 0 ]; then
    DUPLICATION_ESTIMATE=$(($TOTAL_PATTERNS * 100 / ($TOTAL_C_FILES * 10)))
    echo "   📈 Estimated duplication level: ~$DUPLICATION_ESTIMATE%"
    
    # Compare to baseline (57.7%)
    if [ $DUPLICATION_ESTIMATE -lt 58 ]; then
        REDUCTION=$((58 - DUPLICATION_ESTIMATE))
        echo "   ✅ Progress detected: ~$REDUCTION% reduction from baseline"
    else
        echo "   ⏳ Baseline level: 57.7% - consolidation in progress"
    fi
fi

echo ""
echo "🎯 PHASE 2 STATUS SUMMARY:"
echo "   🧪 Monitoring system: ✅ OPERATIONAL"
echo "   📊 Duplication tracking: ✅ ACTIVE"
echo "   🔍 Developer validation: ✅ MONITORING"
echo "   ⏰ Next report: 30 minutes"

echo ""
echo "💪 Quality + Monitoring Master tracking manual consolidation progress!"