# 📚 XMD VIOLATION DETECTION - EXAMPLES & USE CASES

**🎯 Real-world examples của cách sử dụng violation detection tools**

---

## 🚀 BASIC USAGE EXAMPLES

### Example 1: **Daily Health Check**
```bash
# Morning routine - check codebase health
cd /data/data/com.termux/files/home/xmd
./tools/violation_check.sh

# Expected output:
🛡️ ==============================================
   XMD VIOLATION DETECTION AUTOMATION
   Time: 2025-08-02 08:00:00
===============================================

🔧 Checking violation detection tools...
✅ Tools ready
🎯 Scanning entire codebase...
🔍 Running violation detection analysis...
✅ Analysis complete
📊 Analyzing results...

📋 VIOLATION SUMMARY:
────────────────────────────────────
👻 Ghost Functions: 25 (NEEDS ATTENTION)
💀 Dead Functions: 3 (CAN BE CLEANED)
📁 Total Defined Functions: 350
📞 Total Called Functions: 375
🔄 Potential Duplicates: 5
────────────────────────────────────
⚠️  Health Score: 93% (GOOD)
```

### Example 2: **Quick Module Scan**
```bash
# Quick check on specific module
./tools/violation_check.sh -q src/ast/

# Expected output:
🎯 Scanning directory: src/ast/
📋 VIOLATION SUMMARY:
────────────────────────────────────
👻 Ghost Functions: 8
💀 Dead Functions: 1
📁 Total Defined Functions: 45
📞 Total Called Functions: 53
🔄 Potential Duplicates: 2
────────────────────────────────────
⚠️  Health Score: 85% (GOOD)
```

---

## 🔍 DETAILED ANALYSIS EXAMPLES

### Example 3: **Critical Issues Only**
```bash
./tools/violation_check.sh -c

# Shows only build-blocking issues:
🚨 CRITICAL GHOST FUNCTIONS (Build Blockers):
  • xmd_get_version (called from: main.c, xmd.h)
  • xmd_init (called from: main.c)
  • Copyright (called from: main.c)

⚡ HIGH-PRIORITY GHOST FUNCTIONS (XMD Core):
  • xmd_validate (called 12 times)
  • xmd_set_config (called 8 times)
  • xmd_get_config (called 6 times)
  • config_validate (called 4 times)
```

### Example 4: **Manual JSON Analysis**
```bash
# Run detection first
./tools/violation_check.sh -q

# Then analyze với jq
# Find most called ghost functions
cat dead_code_report.json | jq '.ghost_functions | sort_by(.calls | length) | reverse | .[0:5] | .[] | {name: .name, call_count: (.calls | length)}'

# Output:
{
  "name": "xmd_validate",
  "call_count": 12
}
{
  "name": "xmd_set_config", 
  "call_count": 8
}
{
  "name": "config_get",
  "call_count": 6
}
```

---

## 🛠️ PROBLEM-SOLVING EXAMPLES

### Example 5: **Resolving Ghost Function** 
**Problem:** `xmd_validate` function is called but not implemented

```bash
# 1. Identify the issue
./tools/violation_check.sh -c
# Shows: xmd_validate (called 12 times)

# 2. Find where it's called
cat dead_code_report.json | jq '.ghost_functions[] | select(.name == "xmd_validate") | .calls'
# Shows calls from: src/parser/validate.c, src/bindings/c_api.c

# 3. Create Genesis-compliant implementation
mkdir -p src/bindings/c_api/validation/xmd_validate/

# 4. Implement the function
cat > src/bindings/c_api/validation/xmd_validate/xmd_validate.c << 'EOF'
/**
 * @file xmd_validate.c
 * @brief Validate XMD syntax
 */

#include "../../../../../include/xmd.h"
#include "../../../../utils/common/common_macros.h"

xmd_error_code xmd_validate(const char* content) {
    XMD_VALIDATE_PTRS(XMD_ERROR, content);
    
    // Implementation logic here
    return XMD_SUCCESS;
}
EOF

# 5. Verify resolution
./tools/violation_check.sh -q
# Ghost function count should decrease by 1
```

### Example 6: **Cleaning Dead Functions**
**Problem:** Found dead functions that need cleanup

```bash
# 1. Identify dead functions
cat dead_code_report.json | jq '.dead_functions[]'
# Shows: unused_helper_function

# 2. Double-check it's really unused
grep -r "unused_helper_function" src/ --exclude="*/unused_helper_function.c"
# No results = safe to remove

# 3. Remove the function
rm src/utils/helpers/unused_helper_function/unused_helper_function.c
rmdir src/utils/helpers/unused_helper_function/

# 4. Update build system if needed
# Edit CMakeLists.txt to remove reference

# 5. Verify cleanup
./tools/violation_check.sh -q
# Dead function count should decrease
```

---

## 👥 TEAM WORKFLOW EXAMPLES

### Example 7: **DEBTHUNTER Daily Routine**
```bash
#!/bin/bash
# debthunter_routine.sh

echo "🗑️ DEBTHUNTER DAILY ROUTINE"

# 1. Full health check
./tools/violation_check.sh

# 2. Focus on XMD-specific ghost functions
echo "🎯 XMD-SPECIFIC GHOST FUNCTIONS:"
cat dead_code_report.json | jq -r '.ghost_functions[] | select(.name | test("^(xmd_|config_)")) | "  • \(.name) (\(.calls | length) calls)"'

# 3. Identify implementation priorities
echo "📋 IMPLEMENTATION PRIORITIES:"
cat dead_code_report.json | jq -r '.ghost_functions[] | select(.calls[].file | test("main.c|xmd.h")) | "  HIGH: \(.name)"'
cat dead_code_report.json | jq -r '.ghost_functions[] | select(.calls | length > 5) | "  MEDIUM: \(.name) (\(.calls | length) calls)"'

# 4. Log progress
GHOST_COUNT=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
echo "$(date): Ghost functions remaining: $GHOST_COUNT" >> debthunter_progress.log
```

### Example 8: **SYSTEMS Engineer Focus**
```bash
#!/bin/bash
# systems_analysis.sh

echo "🔧 SYSTEMS ENGINEER ANALYSIS"

# Focus on potential duplicates for macro application  
echo "🔄 POTENTIAL DUPLICATES FOR MACRO APPLICATION:"
cat dead_code_report.json | jq -r '.potential_duplicates[] | "  • \(.name) (similarity: \(.similarity)%)"'

# Look for pattern-based duplications
echo "📊 FUNCTIONS BY PATTERN:"
cat dead_code_report.json | jq -r '.ghost_functions[] | .name' | sed 's/_[^_]*$//' | sort | uniq -c | sort -nr
```

### Example 9: **LEADER Status Report**
```bash
#!/bin/bash
# leader_report.sh

echo "👑 LEADER STATUS REPORT"

# Overall metrics
./tools/violation_check.sh -q

# Calculate progress toward targets
GHOST_COUNT=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
TOTAL_CALLED=$(cat dead_code_report.json | jq '.summary.total_called_functions')
COMPLETION_PERCENT=$(( (TOTAL_CALLED - GHOST_COUNT) * 100 / TOTAL_CALLED ))

echo "📈 PROGRESS METRICS:"
echo "  • Implementation Completion: $COMPLETION_PERCENT%"
echo "  • Ghost Functions Target: <10 (current: $GHOST_COUNT)"

if [ "$GHOST_COUNT" -lt 10 ]; then
    echo "✅ TARGET ACHIEVED: Ghost functions under control"
else
    echo "⚠️  TARGET MISSED: Need to reduce ghost functions"
fi

# Team coordination needs
echo "👥 TEAM COORDINATION NEEDS:"
cat dead_code_report.json | jq -r '.ghost_functions[] | select(.name | test("^ast_")) | "  DEVELOPER: \(.name)"' | head -5
cat dead_code_report.json | jq -r '.ghost_functions[] | select(.name | test("^(store_|token_)")) | "  SYSTEMS: \(.name)"' | head -5
```

---

## 🚨 EMERGENCY SCENARIOS

### Example 10: **Build Failure Recovery**
**Scenario:** Build suddenly fails due to missing functions

```bash
# 1. Emergency scan
./tools/violation_check.sh -c

# 2. Identify build-critical functions
echo "🚨 BUILD-CRITICAL FUNCTIONS:"
cat dead_code_report.json | jq -r '.ghost_functions[] | select(.calls[].file | test("main.c")) | .name'

# 3. Create minimal stubs for immediate fix
for func in $(cat dead_code_report.json | jq -r '.ghost_functions[] | select(.calls[].file | test("main.c")) | .name'); do
    echo "Creating emergency stub for $func..."
    mkdir -p "src/emergency/stubs/$func/"
    cat > "src/emergency/stubs/$func/$func.c" << EOF
// EMERGENCY STUB - REPLACE WITH REAL IMPLEMENTATION
#include "../../../include/xmd.h"

int $func(void) {
    // TODO: Implement proper functionality
    return 0;
}
EOF
done

# 4. Test build
make clean && make

# 5. Replace stubs với real implementations ASAP
```

### Example 11: **Pre-Release Validation**
**Scenario:** Preparing for release, need clean codebase

```bash
#!/bin/bash
# pre_release_validation.sh

echo "🚀 PRE-RELEASE VALIDATION"

# 1. Full comprehensive scan
./tools/violation_check.sh

# 2. Check critical metrics
GHOST_COUNT=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
DEAD_COUNT=$(cat dead_code_report.json | jq '.summary.dead_functions_count')

# 3. Release readiness check
echo "📋 RELEASE READINESS:"
if [ "$GHOST_COUNT" -eq 0 ]; then
    echo "✅ Ghost Functions: READY ($GHOST_COUNT)"
else
    echo "❌ Ghost Functions: NOT READY ($GHOST_COUNT remaining)"
fi

if [ "$DEAD_COUNT" -lt 5 ]; then
    echo "✅ Dead Functions: ACCEPTABLE ($DEAD_COUNT)"
else
    echo "⚠️  Dead Functions: CONSIDER CLEANUP ($DEAD_COUNT)"
fi

# 4. Generate release notes section
echo "📝 RELEASE NOTES - CODE QUALITY:"
echo "  • Ghost Functions Resolved: $(( $(cat last_release_report.json | jq '.summary.ghost_functions_count' 2>/dev/null || echo 50) - GHOST_COUNT ))"
echo "  • Code Health Score: $(( ($(cat dead_code_report.json | jq '.summary.total_called_functions') - GHOST_COUNT) * 100 / $(cat dead_code_report.json | jq '.summary.total_called_functions') ))%"
```

---

## 📊 ADVANCED ANALYSIS EXAMPLES

### Example 12: **Trend Analysis**
```bash
#!/bin/bash
# trend_analysis.sh

echo "📈 GHOST FUNCTION TREND ANALYSIS"

# Compare với previous reports
if [ -f "previous_report.json" ]; then
    PREV_GHOST=$(cat previous_report.json | jq '.summary.ghost_functions_count')
    CURR_GHOST=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
    PROGRESS=$((PREV_GHOST - CURR_GHOST))
    
    echo "Progress since last check: $PROGRESS functions resolved"
    
    if [ "$PROGRESS" -gt 0 ]; then
        echo "✅ IMPROVING: $PROGRESS functions implemented"
    elif [ "$PROGRESS" -eq 0 ]; then
        echo "⚠️  STAGNANT: No progress made"
    else
        echo "❌ REGRESSING: $((0 - PROGRESS)) new ghost functions introduced"
    fi
fi

# Backup current report for next comparison
cp dead_code_report.json previous_report.json
```

### Example 13: **Module Health Comparison**
```bash
#!/bin/bash
# module_comparison.sh

echo "📊 MODULE HEALTH COMPARISON"

for module in ast config store token variable; do
    echo "Analyzing $module..."
    ./tools/violation_check.sh -q "src/$module/"
    
    if [ -f dead_code_report.json ]; then
        GHOST=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
        DEAD=$(cat dead_code_report.json | jq '.summary.dead_functions_count')
        TOTAL=$(cat dead_code_report.json | jq '.summary.total_defined_functions')
        
        if [ "$TOTAL" -gt 0 ]; then
            HEALTH=$(( (TOTAL - GHOST) * 100 / TOTAL ))
            echo "$module: Health $HEALTH% (Ghost: $GHOST, Dead: $DEAD, Total: $TOTAL)"
        fi
        
        mv dead_code_report.json "${module}_report.json"
    fi
done

echo "📋 MODULE RANKING (by health score):"
for module in ast config store token variable; do
    if [ -f "${module}_report.json" ]; then
        GHOST=$(cat "${module}_report.json" | jq '.summary.ghost_functions_count')
        TOTAL=$(cat "${module}_report.json" | jq '.summary.total_defined_functions')
        if [ "$TOTAL" -gt 0 ]; then
            HEALTH=$(( (TOTAL - GHOST) * 100 / TOTAL ))
            echo "$HEALTH% - $module"
        fi
    fi
done | sort -nr
```

---

## 🎯 SUCCESS METRICS EXAMPLES

### Example 14: **Achievement Tracking**
```bash
#!/bin/bash
# achievement_tracker.sh

echo "🏆 XMD PROJECT ACHIEVEMENTS"

# Current metrics
GHOST_COUNT=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
TOTAL_FUNCTIONS=$(cat dead_code_report.json | jq '.summary.total_defined_functions')
COMPLETION_PERCENT=$(( ($(cat dead_code_report.json | jq '.summary.total_called_functions') - GHOST_COUNT) * 100 / $(cat dead_code_report.json | jq '.summary.total_called_functions') ))

echo "📈 CURRENT ACHIEVEMENTS:"
echo "  • Functions Implemented: $(($(cat dead_code_report.json | jq '.summary.total_called_functions') - GHOST_COUNT))"
echo "  • Implementation Rate: $COMPLETION_PERCENT%"
echo "  • Ghost Functions Remaining: $GHOST_COUNT"

# Milestone tracking
if [ "$GHOST_COUNT" -eq 0 ]; then
    echo "🎉 MILESTONE: Perfect Implementation (0% ghost functions)"
elif [ "$GHOST_COUNT" -lt 10 ]; then
    echo "🏅 MILESTONE: Excellent Health (<10 ghost functions)"
elif [ "$COMPLETION_PERCENT" -ge 90 ]; then
    echo "🥈 MILESTONE: High Implementation Rate (>90%)"
elif [ "$COMPLETION_PERCENT" -ge 80 ]; then
    echo "🥉 MILESTONE: Good Implementation Rate (>80%)"
fi

# Historical comparison
echo "📊 PROGRESS COMPARISON:"
echo "  • Week 1: 558 ghost functions identified"
echo "  • Current: $GHOST_COUNT ghost functions remaining"
echo "  • Resolved: $((558 - GHOST_COUNT)) functions ($((((558 - GHOST_COUNT) * 100) / 558))% progress)"
```

---

**💡 Pro Tips for Examples:**

1. **Save frequently used queries** as shell functions
2. **Create team-specific scripts** for role-based analysis  
3. **Use automation** for daily/weekly health checks
4. **Track progress over time** with historical data
5. **Combine với CI/CD** for automated quality gates

**🏆 Team Achievement:** Using these tools, team đã resolve 22+ ghost functions và achieve 42% duplication reduction!