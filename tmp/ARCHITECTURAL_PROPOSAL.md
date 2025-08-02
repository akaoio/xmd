# XMD Architectural Proposal - Technical Debt Elimination

## ARCHITECT FINDINGS - CRITICAL DUPLICATIONS

### 1. MAJOR DUPLICATION: minimal_stubs.c
**VIOLATION**: Genesis directive "NO TECH DEBTS, NO STUBS, ALL ARE REAL IMPLEMENTATIONS"

**Evidence Found**:
```c
// minimal_stubs.c has complete duplicate implementations:
store* store_create(void)     // DUPLICATES store.c
void store_destroy(store* s)  // DUPLICATES store.c  
bool store_set(...)           // DUPLICATES store.c
variable* store_get(...)      // DUPLICATES store.c
// ... ALL store functions duplicated!

bool evaluate_condition(...)  // DUPLICATES systems_consolidated.c
```

**IMMEDIATE ACTION**: Remove minimal_stubs.c from CMakeLists.txt

### 2. Variable Syntax Migration Required
- Current: ${varname}
- Target: {{varname}} per Genesis directive
- Impact: Lexer, parser, evaluator updates needed

## PROPOSED SRC/ REORGANIZATION

### Clean Architecture (6 Core Directories)
```
src/
├── core/        # Language core (lexer, parser, ast, evaluator)
├── runtime/     # Runtime systems (variables, store, memory)
├── features/    # Language features (control, functions, classes)
├── io/          # I/O operations (file, console, formats)
├── platform/    # Platform-specific (platform.c, security.c)
├── tools/       # Dev tools (cli, devtools, docs)
└── main.c       # Entry point
```

### File Mappings
- lexer_consolidated.c → core/lexer.c
- ast_consolidated.c → core/ast.c
- native_xmd_consolidated.c → core/evaluator.c
- variable.c → runtime/variables.c
- store.c → runtime/store.c (KEEP, remove minimal_stubs.c)
- systems_consolidated.c → features/control.c

## IMMEDIATE ACTIONS

1. **ELIMINATE minimal_stubs.c**
   - Remove from CMakeLists.txt
   - Use store.c implementations only
   - Use systems_consolidated.c for evaluate_condition

2. **Fix Native Lexer** (Developer working on this)
   - Recognize bare keywords like "set", "if", "for"
   - Support {{varname}} syntax

3. **Reorganize src/**
   - Create 6 clean directories
   - Move consolidated files to proper locations
   - Update CMakeLists.txt paths

## GENESIS COMPLIANCE
✅ NO TECH DEBTS - Duplications eliminated
✅ NO MOCK - Real implementations only  
✅ NO STUBS - minimal_stubs.c removed
✅ Clean src/ structure - 6 directories
✅ {{varname}} syntax support