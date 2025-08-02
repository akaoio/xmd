# 🤖 CLAUDE.md - AI Assistant Guide for XMD Project

> **Purpose**: This document helps AI assistants (Claude, GPT, or others) quickly understand and contribute to the XMD project effectively.

---

## 🎯 PROJECT OVERVIEW

**XMD** is a lightweight, mobile-friendly programming language with natural language-like syntax. Created by Nguyen Ky Son, it's designed to be "the most beautiful programming language" - prioritizing clarity and human readability over raw power.

### Core Vision
- **Mobile-first**: Minimal syntax optimized for mobile typing
- **Natural language**: Space-separated function calls, no parentheses
- **Markdown-compatible**: Embeddable in .md files using ```xmd``` blocks
- **Pure simplicity**: No complex punctuation or nested brackets

### Example XMD Syntax
```xmd
# Variables - no quotes needed for keys
set user name "Alice", age 30, active true

# Functions - space-separated arguments
function greet name
    return "Hello " + name

# Loops - natural language style
for item in items
    print item

# File operations - clean and simple
File.write "data.txt" "Hello World"
set content File.read "data.txt"
```

---

## 📖 MANDATORY FIRST STEPS

### 1. Read Core Documents (IN THIS ORDER)
```bash
# 1. XMD Language Specification - MANDATORY FIRST!
cat blueprint/idea.md

# 2. Your role's memory (if assigned a role)
cat memory/<role>/memory.md

# 3. Your role prompt (if assigned a role)
cat prompts/<role>.md

# 4. Team communication guidelines
cat CHAT.md
```

### 2. Create Your Build Directory
```bash
# NEVER use shared 'build/' - ALWAYS use isolated directory
mkdir -p build-<your-identifier>
cmake -B build-<your-identifier> -S .
cd build-<your-identifier> && make -j4
```

---

## 🧠 MEMORY SYSTEM - PROJECT CONTINUITY

The `memory/` directory contains the **SOUL** of the project. Any AI can instantly restore full context from these files.

### Memory Structure
```
memory/
├── leader/memory.md      # Project coordination & decisions
├── systems/memory.md     # Code optimization & technical debt
├── debthunter/memory.md  # Bug analysis & violation detection
├── developer/memory.md   # Function implementation & core dev
├── tester/memory.md      # Testing strategies & quality
└── designer/memory.md    # Architecture & design decisions
```

### Memory Update Requirements
**🚨 UPDATE FREQUENTLY - NOT JUST AT SESSION END!**
- 📝 Every 30-45 minutes (checkpoint progress)
- 📝 After completing major tasks
- 📝 When discovering important information
- 📝 Before context switches
- 📝 At session end (comprehensive update)

### Memory Update Template
```markdown
## Session [DATE TIME] Update
### Tasks Completed
- ✅ [Specific task with evidence/file paths]

### Discoveries/Issues
- 🔍 [Important finding with context]
- ⚠️ [Issue encountered and resolution]

### Current State
- Build status: [100% success / X warnings]
- Tests: [passing/failing]
- Metrics: [duplication %, coverage %, etc.]

### Next Steps
- [ ] [Immediate priority]
- [ ] [Follow-up task]
```

---

## 🏛️ SACRED PRINCIPLES (NEVER VIOLATE)

### 1. Genesis Principle - File Organization
**"1 function → 1 file → 1 directory"**
```
src/
└── ast/
    └── evaluator/
        └── expression/
            └── ast_evaluate_binary_op/
                ├── ast_evaluate_binary_op.c  # ONE function only
                └── ast_evaluate_binary_op.h  # Header for that function
```

### 2. No Dependencies
- Standard C only (C17)
- Exceptions: cJSON for JSON, libyaml for YAML
- NO other external libraries

### 3. Real Implementation
- Complete, working code
- NO stubs, NO TODOs
- All functions must be production-ready

### 4. Memory Management
- Pattern: Validate → Use → Free
- Zero memory leaks allowed
- Use provided macros: XMD_MALLOC, XMD_FREE

### 5. Error Handling
- All inputs validated
- All error paths handled
- Error messages to stderr
- Proper return codes

### 6. Naming Convention
- Functions: snake_case (e.g., `ast_evaluate_expression`)
- Macros: UPPER_CASE (e.g., `XMD_ASSERT`)
- No camelCase, no PascalCase

---

## 💬 TEAM COMMUNICATION

### Chat System Usage
```bash
# Check messages
node chat.js

# Send to specific role
node chat.js @<your-role>: @recipient "message"

# Broadcast to all
node chat.js @<your-role>: @all "team update"
```

### Team Roles
- **leader**: Project coordination, decisions, team management
- **systems**: Code optimization, technical debt reduction
- **debthunter**: Bug analysis, violation detection
- **developer**: Function implementation, core development
- **tester**: Testing, validation, quality assurance
- **designer**: Architecture, system design

---

## 🏗️ BUILD SYSTEM

### CMake Configuration
```bash
# Configure with your isolated build directory
cmake -B build-<identifier> -S .

# Build
cd build-<identifier> && make -j4

# Test
./xmd --version
```

### Build Isolation Rule
**GENESIS DIRECTIVE**: "anh em phải có riêng mỗi người 1 thư mục build riêng"

❌ **NEVER**: `mkdir build`
✅ **ALWAYS**: `mkdir build-<your-identifier>`

---

## 📊 CURRENT PROJECT STATUS

### Implementation Progress
- **Core Module**: 9 functions (runtime, config, validation)
- **CLI Module**: 2 functions (init, cleanup)
- **AST Module**: ~150+ functions (parser, evaluator, nodes)
- **Build Health**: 100% compilation success
- **Code Duplication**: 57.7% (target: 20%)

### Active Priorities
1. **Genesis Violations**: Splitting multi-function files
2. **Duplication Reduction**: Phase 1 (57.7% → 45%)
3. **Array/Object Access**: Implementing indexing evaluation
4. **Technical Debt**: 497 violations being addressed

---

## 🚀 QUICK START COMMANDS

```bash
# 1. Read the vision
cat blueprint/idea.md

# 2. Check current status
cat memory/leader/memory.md

# 3. Create build directory
mkdir -p build-ai-$(date +%s)

# 4. Configure and build
cmake -B build-ai-* -S .
cd build-ai-* && make -j4

# 5. Test
./xmd --version

# 6. Join team chat
node chat.js @ai: @all "AI assistant online, memory restored"
```

---

## ⚠️ COMMON PITFALLS TO AVOID

### DON'T:
- ❌ Use shared `build/` directory
- ❌ Create functions with stubs or TODOs
- ❌ Put multiple functions in one file
- ❌ Skip reading blueprint/idea.md
- ❌ Update memory only at session end
- ❌ Present estimates as facts
- ❌ Use external dependencies

### DO:
- ✅ Use isolated build-<identifier>/ directory
- ✅ Implement complete, working functions
- ✅ Follow Genesis: 1 function → 1 file → 1 directory
- ✅ Read blueprint/idea.md FIRST
- ✅ Update memory every 30-45 minutes
- ✅ Provide evidence-based metrics
- ✅ Use only standard C (+ cJSON/libyaml)

---

## 📝 EVIDENCE-BASED CULTURE

### Always Provide Proof
```bash
# Bad: "I fixed the warnings"
# Good: "Fixed 28 warnings: 20 missing newlines, 8 unused params. Build output: 58→30 warnings"

# Bad: "Duplication reduced"  
# Good: "Duplication: 57.7%→45.2% (12.5% reduction) verified by duplication_check.sh"

# Bad: "Tests pass"
# Good: "Tests: 147/147 passing. Coverage: 89.3%. Zero memory leaks (valgrind clean)"
```

### Verification Commands
```bash
# Check build health
make 2>&1 | grep -c "warning\|error"

# Check duplication (if tool exists)
./tools/duplication_check.sh

# Run tests
make test

# Memory check
valgrind --leak-check=full ./xmd test.xmd
```

---

## 🎯 SUCCESS METRICS

### You're doing well if:
- ✅ Build maintains 100% success
- ✅ Memory updated every 30-45 minutes
- ✅ Following Genesis principle strictly
- ✅ Providing evidence-based updates
- ✅ Communicating via chat.js
- ✅ Using isolated build directory

### Red flags to address:
- 🚨 Build errors introduced
- 🚨 Memory not updated for >1 hour
- 🚨 Multiple functions in single file
- 🚨 Using shared build/ directory
- 🚨 TODOs or stubs in code
- 🚨 Claims without evidence

---

## 🤝 WORKING WITH THE TEAM

### Coordination Protocol
1. **Check messages**: `node chat.js`
2. **Announce presence**: `@ai: @all "AI assistant online"`
3. **Claim tasks**: `@ai: @leader "Taking task X"`
4. **Report progress**: `@ai: @all "Task X: 50% complete"`
5. **Request help**: `@ai: @developer "Need help with Y"`
6. **Update memory**: Every 30-45 minutes

### Handoff Protocol
When ending session:
1. Complete current task or reach safe stopping point
2. Update memory with detailed status
3. Send handoff message via chat.js
4. Document any blockers or next steps

---

## 📚 KEY PROJECT FILES

### Core Documentation
- `blueprint/idea.md` - XMD language specification
- `CONTRIBUTING.md` - Contribution guidelines
- `README.md` - Project overview
- `CHAT.md` - Team communication guide

### Configuration
- `CMakeLists.txt` - Build configuration
- `.xmd/core/principle/` - Sacred principles

### Implementation
- `src/core/` - Core runtime functions
- `src/ast/` - AST parser and evaluator
- `src/bindings/` - C API bindings
- `src/cli/` - Command-line interface

### Tools & Scripts
- `chat.js` - Team communication system
- `tools/` - Various utility scripts

---

## 🆘 GETTING HELP

### When stuck:
1. Check memory files for context
2. Read relevant documentation
3. Search codebase for similar patterns
4. Ask team via chat.js
5. Update memory with blockers

### Useful searches:
```bash
# Find function implementations
grep -r "function_name" src/

# Find Genesis violations
find src/ -name "*.c" -exec grep -l "^[a-z_]*(" {} \; | xargs -I {} sh -c 'echo {}; grep -c "^[a-z_]*(" {}'

# Check for TODOs
grep -r "TODO\|FIXME\|XXX" src/
```

---

## 🌟 FINAL REMINDERS

1. **Blueprint first**: Always read `blueprint/idea.md` before starting
2. **Memory frequently**: Update every 30-45 minutes, not just at end
3. **Build isolation**: Use `build-<identifier>/`, never shared `build/`
4. **Genesis always**: 1 function → 1 file → 1 directory
5. **Evidence-based**: Provide proof for all claims
6. **Communicate**: Use chat.js for all team interaction

**Welcome to XMD! Together we're building the most beautiful programming language!** 🚀

---

*Generated by Leader on 2025-08-02 22:50*
*XMD Version: 2.0.0-consolidation*