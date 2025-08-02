# ⚡ XMD VIOLATION DETECTION - QUICK REFERENCE

**🚀 Fast access guide cho team members**

---

## 🔥 QUICK COMMANDS

### 🗑️ Dead Function Detection
```bash
# Basic scan
./tools/analyzer/dead_function_detector

# Check results
cat dead_code_report.json | jq '.summary'

# Count violations
echo "Ghost: $(jq '.summary.ghost_functions_count' dead_code_report.json)"
echo "Dead: $(jq '.summary.dead_functions_count' dead_code_report.json)"
```

### 🎯 Filter Critical Functions
```bash
# XMD-specific ghost functions
jq '.ghost_functions[] | select(.name | test("^(xmd_|ast_|config_)"))' dead_code_report.json

# Most called ghost functions
jq '.ghost_functions | sort_by(.calls | length) | reverse | .[0:10]' dead_code_report.json
```

---

## 📊 STATUS CHECKS

### ✅ Health Check
```bash
#!/bin/bash
echo "🔍 XMD CODEBASE HEALTH CHECK"
./tools/analyzer/dead_function_detector

GHOST=$(jq '.summary.ghost_functions_count' dead_code_report.json)
DEAD=$(jq '.summary.dead_functions_count' dead_code_report.json)
TOTAL=$(jq '.summary.total_defined_functions' dead_code_report.json)

echo "👻 Ghost Functions: $GHOST"
echo "💀 Dead Functions: $DEAD"
echo "📁 Total Functions: $TOTAL"

if [ "$GHOST" -eq 0 ]; then
    echo "✅ HEALTHY: No ghost functions"
else
    echo "⚠️  NEEDS ATTENTION: $GHOST ghost functions need implementation"
fi
```

### 🎯 Progress Tracking
```bash
# Before work
./tools/analyzer/dead_function_detector
BEFORE_GHOST=$(jq '.summary.ghost_functions_count' dead_code_report.json)

# ... do development work ...

# After work  
./tools/analyzer/dead_function_detector
AFTER_GHOST=$(jq '.summary.ghost_functions_count' dead_code_report.json)

echo "Progress: $((BEFORE_GHOST - AFTER_GHOST)) ghost functions resolved"
```

---

## 🛠️ COMMON FIXES

### 👻 Fix Ghost Function
```bash
# 1. Find function details
FUNC_NAME="xmd_example_function"
jq ".ghost_functions[] | select(.name == \"$FUNC_NAME\")" dead_code_report.json

# 2. Create Genesis-compliant directory
mkdir -p "src/module/category/$FUNC_NAME/"

# 3. Implement function
cat > "src/module/category/$FUNC_NAME/$FUNC_NAME.c" << 'EOF'
/**
 * @file xmd_example_function.c
 * @brief Brief description
 */

#include "../../../../include/xmd.h"
#include "../../../utils/common/common_macros.h"

int xmd_example_function(void) {
    // Implementation
    return 0;
}
EOF
```

### 💀 Remove Dead Function
```bash
# 1. Verify it's really dead
FUNC_NAME="dead_function"
grep -r "$FUNC_NAME" src/ --exclude="*/$FUNC_NAME.c"

# 2. If no results, safe to remove
rm "src/path/to/$FUNC_NAME/$FUNC_NAME.c"
rmdir "src/path/to/$FUNC_NAME/"  # If directory becomes empty
```

---

## 🚨 EMERGENCY PROCEDURES

### 🆘 Critical Ghost Functions (Build Blockers)
```bash
# Find functions called in main.c or critical paths
jq '.ghost_functions[] | select(.calls[].file | test("main.c|xmd.h"))' dead_code_report.json

# Priority order for implementation:
# 1. Functions called in main.c
# 2. Functions in public headers (xmd.h)
# 3. Functions with high call counts
```

### 🔧 Build Failure Recovery
```bash
# If build fails due to missing functions:
# 1. Quick scan
./tools/analyzer/dead_function_detector

# 2. Identify build-critical functions
jq '.ghost_functions[] | select(.calls[].file | test("main.c")) | .name' dead_code_report.json

# 3. Implement minimal stubs for immediate fix (then replace with real implementations)
```

---

## 📈 TEAM COORDINATION

### 🎯 Role-Specific Quick Checks

#### 👤 DEBTHUNTER Role:
```bash
# Focus on ghost function resolution
jq '.ghost_functions | length' dead_code_report.json
jq '.ghost_functions[] | select(.name | test("^(xmd_|config_)")) | .name' dead_code_report.json
```

#### 🔧 SYSTEMS Role:
```bash
# Focus on duplicate detection for macro application
jq '.potential_duplicates' dead_code_report.json
```

#### 👨‍💻 DEVELOPER Role:
```bash
# Focus on functions in specific modules
jq '.ghost_functions[] | select(.name | test("^(ast_|parser_)"))' dead_code_report.json
```

#### 👑 LEADER Role:
```bash
# Overall health metrics
jq '{
  ghost_count: .summary.ghost_functions_count,
  dead_count: .summary.dead_functions_count,
  health_score: ((.summary.total_defined_functions - .summary.ghost_functions_count) / .summary.total_defined_functions * 100 | floor)
}' dead_code_report.json
```

---

## 🎯 CI/CD INTEGRATION

### ✅ Pre-Commit Hook
```bash
#!/bin/bash
# .git/hooks/pre-commit
./tools/analyzer/dead_function_detector

GHOST_COUNT=$(jq '.summary.ghost_functions_count' dead_code_report.json)
if [ "$GHOST_COUNT" -gt 100 ]; then  # Adjust threshold as needed
    echo "❌ Too many ghost functions: $GHOST_COUNT"
    echo "Please resolve some ghost functions before committing"
    exit 1
fi
```

### 📊 Daily Health Report
```bash
#!/bin/bash
# daily_health.sh
echo "📅 $(date) - XMD Health Report"
./tools/analyzer/dead_function_detector

jq '{
  date: now | strftime("%Y-%m-%d %H:%M"),
  ghost_functions: .summary.ghost_functions_count,
  dead_functions: .summary.dead_functions_count,
  total_functions: .summary.total_defined_functions,
  health_score: ((.summary.total_defined_functions - .summary.ghost_functions_count) / .summary.total_defined_functions * 100 | floor)
}' dead_code_report.json >> daily_health.json
```

---

## 🔍 DEBUGGING TOOL ISSUES

### 🐛 Common Problems & Solutions

#### Tool không chạy:
```bash
# Check permissions
chmod +x ./tools/analyzer/dead_function_detector

# Rebuild if needed
cd tools/analyzer && make clean && make
```

#### Kết quả không chính xác:
```bash
# Clear cache and re-run
rm -f dead_code_report.json
./tools/analyzer/dead_function_detector
```

#### Performance issues:
```bash
# Scan specific directory instead of entire src/
./tools/analyzer/dead_function_detector src/specific_module/
```

---

## 📚 USEFUL JQ QUERIES

### 🔍 Analysis Queries
```bash
# Top 10 most called ghost functions
jq '.ghost_functions | sort_by(.calls | length) | reverse | .[0:9] | .[] | {name: .name, call_count: (.calls | length)}' dead_code_report.json

# Functions called from multiple files
jq '.ghost_functions[] | select(.calls | length > 1) | {name: .name, files: [.calls[].file] | unique}' dead_code_report.json

# Ghost functions by module
jq '.ghost_functions | group_by(.name | split("_")[0]) | .[] | {module: .[0].name | split("_")[0], count: length}' dead_code_report.json
```

### 📊 Metrics Queries
```bash
# Calculate ghost function resolution progress
TOTAL_FUNCTIONS=$(jq '.summary.total_called_functions' dead_code_report.json)
GHOST_FUNCTIONS=$(jq '.summary.ghost_functions_count' dead_code_report.json)
IMPLEMENTED_FUNCTIONS=$((TOTAL_FUNCTIONS - GHOST_FUNCTIONS))
COMPLETION_PERCENT=$((IMPLEMENTED_FUNCTIONS * 100 / TOTAL_FUNCTIONS))
echo "Implementation completion: $COMPLETION_PERCENT%"
```

---

**⚡ Pro Tips:**
- Run tools regularly, not just before commits
- Focus on ghost functions called from main.c first
- Use jq for powerful JSON analysis
- Coordinate với team để avoid duplicate work
- Keep tools updated với latest codebase changes

**🏆 Current Achievement:** 22+ ghost functions resolved, 42% duplication reduction achieved!
