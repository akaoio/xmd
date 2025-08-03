#!/bin/bash
# Quick Duplication Check - Zero Duplication Campaign
# Tester (Duplication Validation Lead)

echo "=== QUICK DUPLICATION CHECK ==="
echo "Campaign: ZERO DUPLICATION (57.7% → <20%)"
echo "Timestamp: $(date '+%Y-%m-%d %H:%M:%S')"
echo ""

# Count files
TOTAL_FILES=$(find src -name "*.c" -type f | wc -l)
echo "📊 Total C files: $TOTAL_FILES"

# Simple duplication analysis
echo "🔍 Pattern Analysis:"

# Memory patterns
MALLOC_FILES=$(grep -r "xmd_malloc\|malloc" src --include="*.c" -l | wc -l)
echo "   - Files with malloc patterns: $MALLOC_FILES"

# Error patterns  
ERROR_FILES=$(grep -r "XMD_ERROR_RETURN\|return NULL" src --include="*.c" -l | wc -l)
echo "   - Files with error patterns: $ERROR_FILES"

# AST creation patterns
AST_CREATE_FILES=$(find src -path "*/ast/node/create/*" -name "*.c" | wc -l)
echo "   - AST creation files: $AST_CREATE_FILES"

# AST evaluator patterns
AST_EVAL_FILES=$(find src -path "*/ast/evaluator/*" -name "*.c" | wc -l)  
echo "   - AST evaluator files: $AST_EVAL_FILES"

# AST parser patterns
AST_PARSER_FILES=$(find src -path "*/ast/parser/*" -name "*.c" | wc -l)
echo "   - AST parser files: $AST_PARSER_FILES"

echo ""
echo "🎯 High-Priority Consolidation Targets:"
echo "   - ast/node/create/: $AST_CREATE_FILES files (macro consolidation potential)"
echo "   - ast/evaluator/: $AST_EVAL_FILES files (pattern standardization)"  
echo "   - ast/parser/: $AST_PARSER_FILES files (common flow consolidation)"

# Estimate duplication level
CONSOLIDATION_POTENTIAL=$((AST_CREATE_FILES + AST_EVAL_FILES + AST_PARSER_FILES))
PERCENTAGE=$(echo "scale=1; 100 * $CONSOLIDATION_POTENTIAL / $TOTAL_FILES" | bc -l)

echo ""
echo "📈 ESTIMATED DUPLICATION LEVEL: ~$PERCENTAGE% (files with consolidation potential)"
echo "🎯 TARGET: Reduce to <20% through macro and pattern consolidation"
echo ""
echo "✅ BASELINE MEASUREMENT COMPLETE"
echo "Ready for team optimization tracking!"