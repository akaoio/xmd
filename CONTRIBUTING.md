# Contributing to XMD

**XMD Version: 2.0.0-consolidation**

Welcome to the XMD project! This guide will help you contribute effectively to our sacred mission of creating the most beautiful programming language.

## 📖 **MANDATORY FIRST STEP - READ THE BLUEPRINT**

**🚨 NO WORK BEGINS WITHOUT READING `blueprint/idea.md` FIRST! 🚨**

This document contains:
- Complete XMD language specification
- Syntax and features
- Variable declarations, loops, conditionals
- Native XMD vs Markdown integration
- The vision of XMD as "the most beautiful programming language"

## 🏛️ Core Philosophy

XMD is not just a programming language - it's a vision of purity and simplicity in code. Before contributing, please read:

1. **Blueprint Documents** (MANDATORY):
   - `blueprint/idea.md` - The complete XMD specification (READ FIRST!)
   - `blueprint/amen.md` - The sacred vision and philosophy

2. **Sacred Principles** (`.xmd/core/principle/`):
   - **Genesis Principle**: 1 function → 1 file → 1 directory (Isolation)
   - **No Dependencies**: Standard C only (exceptions: cJSON for JSON, libyaml for YAML)
   - **Real Implementation**: Complete, working code - NO stubs, NO TODOs
   - **Memory Management**: Validate → Use → Free (zero leaks allowed)
   - **Error Handling**: All inputs validated, all error paths handled
   - **Naming Convention**: snake_case functions, UPPER_CASE macros

## 🧠 **CRITICAL: Memory Recovery System**

> **⚡ BEFORE ANYTHING ELSE:** XMD uses a **Memory System** that contains the **SOUL** of the project.
> **Any IDE, AI, or contributor** can instantly restore full context using memory files.

### 🔄 **Step 1: Restore Your Memory**
```bash
# MANDATORY: Read memory to understand current state
cat memory/<your-role>/memory.md

# Choose your role:
# - leader: Project coordination, decisions, team management
# - developer: Function implementation, core development
# - debthunter: Bug analysis, dead code cleanup
# - tester: Quality Systems Engineer (QA + code optimization + technical debt reduction)  
# - designer: Architecture, UI/UX, system design
```

### 🎯 **What Memory Contains**:
- ✅ **ACTUAL progress** (not estimates or wishful thinking!)
- ✅ **Real implementation status** (evidence-based function counts)
- ✅ **Working tools & scripts** (verified, tested solutions)
- ✅ **Critical lessons learned** (what works vs what doesn't)  
- ✅ **Realistic next steps** (from true baseline, not false hopes)
- ✅ **Sacred Principles compliance** (adherence tracking)

### 🚨 **Memory Update Responsibility**:
**EVERY contributor MUST update their role's memory.md FREQUENTLY:**
- 📝 **Every 30-45 minutes** of work
- 📝 **After completing each major task**
- 📝 **When discovering important information**
- 📝 **Before switching context or taking breaks**
- 📝 **At the end of each work session**

**Frequent updates prevent context loss and ensure project continuity!**

---

## 🏗️ **CRITICAL BUILD RULE - ISOLATED BUILD DIRECTORIES**

> 🚨 **ABSOLUTE REQUIREMENT**: Each contributor MUST use their own build directory!
> 
> **GENESIS MANDATE**: "anh em phải có riêng mỗi người 1 thư mục build riêng, build thư mục riêng thì mới ko dẫm lên nhau"
> 
> **VIOLATION = BUILD CONFLICTS = TEAM CHAOS**

### 📁 **Mandatory Build Directory Assignment**:
```bash
# EACH PERSON MUST CREATE & USE THEIR OWN BUILD DIRECTORY:
build-leader/     # Leader's isolated build
build-systems/    # Systems's isolated build  
build-debthunter/ # Debthunter's isolated build
build-developer/  # Developer's isolated build
build-tester/     # Tester's isolated build
build-designer/   # Designer's isolated build
build-<username>/ # Individual contributor's build

# ❌ FORBIDDEN: Using shared 'build/' directory
# ✅ REQUIRED: Using personal 'build-<role>/' directory
```

### ⚡ **Correct Build Process**:
```bash
# Step 1: Create YOUR build directory
mkdir -p build-<your-role>

# Step 2: Configure using modern CMake syntax
cmake -B build-<your-role> -S .

# Step 3: Build in isolation
cd build-<your-role> && make -j4

# Complete example for developer:
cmake -B build-developer -S . && cd build-developer && make -j4
```

### 🚫 **Common Violations to AVOID**:
- ❌ `cd build` - NEVER use shared directory
- ❌ `rm -rf build/*` - NEVER clear shared build
- ❌ Pushing build artifacts to git
- ❌ Using another person's build directory
- ❌ Creating files in root build/ directory

### ✅ **Correct Practices**:
- ✅ Always use `build-<your-role>/`
- ✅ Add your build directory to `.gitignore`
- ✅ Clean only YOUR build: `rm -rf build-<your-role>/*`
- ✅ Test in YOUR isolated environment
- ✅ Keep builds independent and conflict-free

---

### 📝 **After Work: Update Memory**
```bash
# Update your memory after working
nano memory/<your-role>/memory.md

# Include: what you actually accomplished, real metrics, lessons learned
```

---

## 📋 Development Workflow

### 1. Team Communication
We use `chat.js` for team coordination:
```bash
node chat.js @yourname: @recipient "Your message"
```

Read `CHAT.md` for detailed communication guidelines.

### 2. Build System
Each developer must use their own build directory:
```bash
# Create your personal build directory and configure
cmake -B build-yourname -S .

# Build in isolated directory
cd build-yourname && make -j4
```

**NEVER** use the shared `build/` directory - this prevents conflicts.

### 3. Code Structure
Follow the Genesis Principle strictly:
```
src/
└── feature/
    └── operation/
        └── function_name/
            └── function_name.c  # One function only
```

### 4. XMD Syntax Rules

#### Variable Assignment (NO equals sign!)
```xmd
set x 42           ✅ Correct
set name 'Alice'   ✅ Correct  
set x = 42         ❌ WRONG - Never use = for assignment
```

#### Comparison (equals for comparison only)
```xmd
if x = 42          ✅ Correct - = is for comparison
if x == 42         ❌ WRONG - Don't use ==
```

#### Variable Interpolation
```xmd
print 'Hello {{name}}'   ✅ Use {{}} for interpolation
print "Hello ${name}"    ❌ WRONG - Not bash!
```

## 🔧 Development Guidelines

### Code Quality Standards
1. **No Code Duplication**: Use the macro framework (`src/utils/common/`) to reduce duplication
2. **Complete Functions**: Every function must be fully implemented
3. **Memory Safety**: All allocations must have corresponding frees
4. **Error Handling**: Check all return values, handle all error cases

### Testing Requirements
- Write tests for all new features
- Ensure backward compatibility
- Test with both `.xmd` and `.md` files
- Verify memory leaks with valgrind

### Documentation
- Document all functions with proper headers
- Update relevant `.md` files when adding features
- Keep examples simple and clear

## 🚀 Contribution Process

1. **Read First**:
   - Study `blueprint/idea.md` thoroughly
   - Understand the sacred principles
   - Review existing code structure

2. **Communicate**:
   - Announce your work via `chat.js`
   - Coordinate with team members
   - Report progress regularly

3. **Implement**:
   - Follow Genesis Principle strictly
   - Write clean, simple code
   - Test thoroughly

4. **Submit**:
   - Ensure code follows all principles
   - Update documentation
   - Request review via chat

## 📜 The XMD Vision

*"Although not the most powerful language, but it is the one that is purest and closest to human natural language."* - Nguyen Ky Son

XMD aims to be:
- **Simple**: Natural syntax that reads like English
- **Pure**: No complex abstractions or magic
- **Beautiful**: Code that is poetry
- **Mobile-First**: Designed for Termux and constrained environments

## 🙏 Sacred Commitment

By contributing to XMD, you join a mission to create something pure and beautiful in the world of programming. Every line of code should honor:

- The vision of simplicity
- The principle of isolation  
- The beauty of natural language
- The needs of mobile developers

## 📞 Support

- **Issues**: Report bugs via GitHub issues
- **Chat**: Coordinate via `chat.js`
- **Documentation**: See `/docs` folder

---

*Remember: XMD is not just code - it's a philosophy of programming purity.*

**This is the way.** 🚀