#!/bin/bash
# Generate evaluation engine progress report
# Creates detailed report in multiple formats for CI/CD monitoring

REPORT_DIR="test_infrastructure/reports"
mkdir -p $REPORT_DIR

TIMESTAMP=$(date '+%Y-%m-%d_%H-%M-%S')
TXT_REPORT="$REPORT_DIR/evaluation_progress_$TIMESTAMP.txt"
MD_REPORT="$REPORT_DIR/evaluation_progress_$TIMESTAMP.md"
JSON_REPORT="$REPORT_DIR/evaluation_progress_$TIMESTAMP.json"

echo "Generating evaluation engine progress report..."

# Run evaluation tests and capture output
TEST_OUTPUT=$(./test_infrastructure/evaluation_test_runner.sh 2>&1)

# Extract metrics
PARSING_PASSED=$(echo "$TEST_OUTPUT" | grep "Passed:" | sed 's/.*Passed: //' | sed 's/ .*//')
PARSING_FAILED=$(echo "$TEST_OUTPUT" | grep "Failed:" | sed 's/.*Failed: //' | sed 's/ .*//')
EVALUATION_WORKING=$(echo "$TEST_OUTPUT" | grep "Working:" | sed 's/.*Working: //' | sed 's/ .*//')
EVALUATION_PENDING=$(echo "$TEST_OUTPUT" | grep "Pending:" | sed 's/.*Pending: //' | sed 's/ .*//')
COMPLETION_PERCENT=$(echo "$TEST_OUTPUT" | grep "Completion:" | sed 's/.*Completion: //' | sed 's/%//')

# Set defaults if extraction failed
PARSING_PASSED=${PARSING_PASSED:-0}
PARSING_FAILED=${PARSING_FAILED:-0} 
EVALUATION_WORKING=${EVALUATION_WORKING:-0}
EVALUATION_PENDING=${EVALUATION_PENDING:-0}
COMPLETION_PERCENT=${COMPLETION_PERCENT:-0}

# Calculate totals
TOTAL_PARSING=$((PARSING_PASSED + PARSING_FAILED))
TOTAL_EVALUATION=$((EVALUATION_WORKING + EVALUATION_PENDING))

# Determine status
if [ "$PARSING_FAILED" -eq 0 ] && [ "$COMPLETION_PERCENT" -eq 100 ]; then
    STATUS="COMPLETE"
    STATUS_EMOJI="🎉"
elif [ "$PARSING_FAILED" -eq 0 ] && [ "$EVALUATION_WORKING" -gt 0 ]; then
    STATUS="IN_PROGRESS"
    STATUS_EMOJI="⚠️"
elif [ "$PARSING_FAILED" -eq 0 ]; then
    STATUS="PARSING_READY"
    STATUS_EMOJI="🔧"
else
    STATUS="BROKEN"
    STATUS_EMOJI="❌"
fi

# Generate Text Report
cat > $TXT_REPORT << EOF
XMD EVALUATION ENGINE PROGRESS REPORT
=====================================
Generated: $(date)
Status: $STATUS_EMOJI $STATUS

PARSING LAYER (Syntax Recognition)
----------------------------------
✅ Passed: $PARSING_PASSED/$TOTAL_PARSING
❌ Failed: $PARSING_FAILED/$TOTAL_PARSING

EVALUATION LAYER (Computation Engine)
-------------------------------------
✅ Working: $EVALUATION_WORKING/$TOTAL_EVALUATION
⚠️  Pending: $EVALUATION_PENDING/$TOTAL_EVALUATION
📊 Completion: $COMPLETION_PERCENT%

SYSTEM STATUS INTERPRETATION
---------------------------
EOF

if [ "$STATUS" = "COMPLETE" ]; then
    echo "🎉 EVALUATION ENGINE COMPLETE!" >> $TXT_REPORT
    echo "- All parsing tests passing" >> $TXT_REPORT
    echo "- All evaluation tests passing" >> $TXT_REPORT
    echo "- Ready for advanced features" >> $TXT_REPORT
elif [ "$STATUS" = "IN_PROGRESS" ]; then
    echo "⚠️ EVALUATION ENGINE IN PROGRESS" >> $TXT_REPORT
    echo "- Parsing layer operational" >> $TXT_REPORT
    echo "- Some evaluation features working" >> $TXT_REPORT
    echo "- Development actively progressing" >> $TXT_REPORT
elif [ "$STATUS" = "PARSING_READY" ]; then
    echo "🔧 READY FOR EVALUATION IMPLEMENTATION" >> $TXT_REPORT
    echo "- Parsing layer fully operational" >> $TXT_REPORT
    echo "- Evaluation engine needs implementation" >> $TXT_REPORT
    echo "- Foundation solid for development" >> $TXT_REPORT
else
    echo "❌ CRITICAL ISSUES DETECTED" >> $TXT_REPORT
    echo "- Parsing layer has failures" >> $TXT_REPORT  
    echo "- Build or syntax recognition broken" >> $TXT_REPORT
    echo "- Fix parsing before evaluation work" >> $TXT_REPORT
fi

echo "" >> $TXT_REPORT
echo "DETAILED TEST OUTPUT" >> $TXT_REPORT
echo "-------------------" >> $TXT_REPORT
echo "$TEST_OUTPUT" >> $TXT_REPORT

# Generate Markdown Report
cat > $MD_REPORT << EOF
# XMD Evaluation Engine Progress Report

**Generated:** $(date)  
**Status:** $STATUS_EMOJI **$STATUS**

## 📊 Test Results Summary

### Parsing Layer (Syntax Recognition)
- ✅ **Passed:** $PARSING_PASSED/$TOTAL_PARSING
- ❌ **Failed:** $PARSING_FAILED/$TOTAL_PARSING

### Evaluation Layer (Computation Engine)  
- ✅ **Working:** $EVALUATION_WORKING/$TOTAL_EVALUATION
- ⚠️ **Pending:** $EVALUATION_PENDING/$TOTAL_EVALUATION
- 📊 **Completion:** $COMPLETION_PERCENT%

## 🎯 Status Interpretation

EOF

if [ "$STATUS" = "COMPLETE" ]; then
    cat >> $MD_REPORT << EOF
### 🎉 EVALUATION ENGINE COMPLETE!
- ✅ All parsing tests passing
- ✅ All evaluation tests passing  
- ✅ Ready for advanced features

**Next Steps:** Begin implementing advanced language features (functions, classes, etc.)
EOF
elif [ "$STATUS" = "IN_PROGRESS" ]; then
    cat >> $MD_REPORT << EOF
### ⚠️ EVALUATION ENGINE IN PROGRESS
- ✅ Parsing layer operational
- ⚡ Some evaluation features working
- 🔧 Development actively progressing

**Next Steps:** Continue evaluation engine implementation, focus on pending features
EOF
elif [ "$STATUS" = "PARSING_READY" ]; then
    cat >> $MD_REPORT << EOF
### 🔧 READY FOR EVALUATION IMPLEMENTATION
- ✅ Parsing layer fully operational
- ⚠️ Evaluation engine needs implementation
- 🏗️ Foundation solid for development

**Next Steps:** Implement evaluation engine in \`ast_evaluate()\` function
EOF
else
    cat >> $MD_REPORT << EOF
### ❌ CRITICAL ISSUES DETECTED
- ❌ Parsing layer has failures
- 🚨 Build or syntax recognition broken
- 🔧 Fix parsing before evaluation work

**Next Steps:** Debug and fix parsing layer issues before continuing
EOF
fi

cat >> $MD_REPORT << EOF

## 📋 Detailed Test Results

\`\`\`
$TEST_OUTPUT
\`\`\`

---
*Report generated by XMD DevOps Test Infrastructure*
EOF

# Generate JSON Report
cat > $JSON_REPORT << EOF
{
  "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "status": "$STATUS",
  "status_emoji": "$STATUS_EMOJI",  
  "parsing": {
    "passed": $PARSING_PASSED,
    "failed": $PARSING_FAILED,  
    "total": $TOTAL_PARSING
  },
  "evaluation": {
    "working": $EVALUATION_WORKING,
    "pending": $EVALUATION_PENDING,
    "total": $TOTAL_EVALUATION,
    "completion_percent": $COMPLETION_PERCENT
  },
  "test_output": $(echo "$TEST_OUTPUT" | jq -Rs .)
}
EOF

echo "Reports generated:"
echo "  📄 Text: $TXT_REPORT"
echo "  📝 Markdown: $MD_REPORT"  
echo "  📊 JSON: $JSON_REPORT"
echo ""
echo "Current Status: $STATUS_EMOJI $STATUS ($COMPLETION_PERCENT% evaluation complete)"