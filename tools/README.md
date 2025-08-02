# XMD Development Tools

⚠️ **IMPORTANT CLARIFICATION:**

**These tools are NOT part of the XMD project core.** They are external development utilities created during the XMD development process to help accelerate development.

## Purpose

These tools are "công cụ ngoài lề" (external utilities) developed to:
- Speed up XMD development process
- Maintain code quality during development  
- Help detect issues early in development cycle
- Assist with code analysis and cleanup

## Tools Available

### 🗑️ Dead Function Detector & Violation Detection Suite
- **Purpose:** Detect unused, ghost, and duplicate functions + code violations
- **Location:** `tools/analyzer/`
- **Usage:** `./tools/violation_check.sh` (recommended) or `./build-tools/dead-function-detector.sh`
- **Status:** Development utility only

## 📚 Documentation

### Complete Documentation Suite:
- **📖 [VIOLATION_DETECTION_GUIDE.md](VIOLATION_DETECTION_GUIDE.md)** - Comprehensive usage guide
- **⚡ [QUICK_REFERENCE.md](QUICK_REFERENCE.md)** - Fast commands and shortcuts  
- **📚 [EXAMPLES.md](EXAMPLES.md)** - Real-world usage examples
- **🛠️ [violation_check.sh](violation_check.sh)** - Automated violation detection script

### Quick Start:
```bash
# Basic health check
./tools/violation_check.sh

# Quick scan specific module
./tools/violation_check.sh -q src/ast/

# Show only critical issues
./tools/violation_check.sh -c

# Get help
./tools/violation_check.sh --help
```

## 🎯 What These Tools Detect

### 👻 Ghost Functions
Functions called but not implemented (build blockers)

### 💀 Dead Functions  
Functions implemented but never called (cleanup candidates)

### 🔄 Duplicate Functions
Functions with similar implementations (refactoring opportunities)

## 📊 Current Achievement
Using these tools, the XMD team has:
- ✅ Resolved 22+ critical ghost functions
- ✅ Achieved 42% code duplication reduction (70% → 28%)
- ✅ Maintained <10 ghost functions target
- ✅ Enabled historic 20% duplication target approach

## Genesis Principles Compliance

Even though these are external tools, they still follow Genesis principles:
- ✅ **ISOLATION:** 1 function → 1 file → 1 directory
- ✅ **NO DEPENDENCIES:** Standard C only 
- ✅ **REAL IMPLEMENTATION:** Complete, no stubs/TODOs
- ✅ **MEMORY MANAGEMENT:** Proper validation and cleanup
- ✅ **ERROR HANDLING:** All paths handled explicitly

## Important Notes

1. **NOT XMD CORE:** These tools are separate from XMD language implementation
2. **DEVELOPMENT ONLY:** Used during development, not shipped with XMD
3. **TEMPORARY:** May be removed or changed as development progresses
4. **EXTERNAL:** Not subject to XMD's runtime requirements or constraints

## Relationship to XMD

```
XMD Project Core (src/)     ←→     Development Tools (tools/)
    ↓                                       ↓
• Language implementation           • Analysis utilities  
• Runtime components               • Development helpers
• Production code                  • Code quality tools
• Shipped with XMD                 • Development-only
```

These tools help BUILD XMD, but are not PART OF XMD itself.