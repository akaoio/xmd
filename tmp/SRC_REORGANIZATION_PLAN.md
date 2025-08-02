# Source Directory Reorganization Plan

## Current State (21 files in src/)
```
src/
├── ast_consolidated.c
├── bindings_consolidated.c  
├── config_consolidated.c
├── dependency.c
├── devtools_consolidated.c
├── docs_consolidated.c
├── import_consolidated.c
├── lexer_consolidated.c
├── main.c
├── native_xmd_consolidated.c
├── parser_utils.c
├── parsers_consolidated.c
├── performance.c
├── platform.c
├── resource.c
├── security.c
├── store.c
├── systems_consolidated.c
├── token.c
├── utils_consolidated.c
└── variable.c
```

## Proposed Organization (Genesis 6-Directory Vision)

### 1. `src/core/` - Core Language Processing
```
core/
├── ast_consolidated.c          # AST parsing and evaluation
├── lexer_consolidated.c        # Tokenization and lexing
├── native_xmd_consolidated.c   # Native XMD processing
├── parser_utils.c              # Parser utilities
├── parsers_consolidated.c      # Language parsers
└── token.c                     # Token management
```

### 2. `src/runtime/` - Runtime System
```
runtime/
├── store.c                     # Variable storage
├── variable.c                  # Variable management
├── dependency.c                # Module dependencies
└── import_consolidated.c       # Import/export system
```

### 3. `src/platform/` - Platform & Infrastructure
```
platform/
├── platform.c                  # Platform abstractions
├── resource.c                  # Resource management
├── security.c                  # Security and sandboxing
├── performance.c               # Performance monitoring
└── utils_consolidated.c        # Core utilities
```

### 4. `src/bindings/` - API & Integration
```
bindings/
├── bindings_consolidated.c     # Language bindings
├── config_consolidated.c       # Configuration management
└── main.c                      # CLI entry point
```

### 5. `src/systems/` - Supporting Systems
```
systems/
├── systems_consolidated.c      # System integration
├── devtools_consolidated.c     # Development tools
└── docs_consolidated.c         # Documentation system
```

### 6. `src/` (Root) - Single files only
```
src/
├── core/
├── runtime/
├── platform/
├── bindings/
├── systems/
└── (no loose files)
```

## Implementation Steps

### Phase 1: Create Directory Structure
```bash
mkdir -p src/core src/runtime src/platform src/bindings src/systems
```

### Phase 2: Move Files
```bash
# Core language processing
mv src/ast_consolidated.c src/core/
mv src/lexer_consolidated.c src/core/
mv src/native_xmd_consolidated.c src/core/
mv src/parser_utils.c src/core/
mv src/parsers_consolidated.c src/core/
mv src/token.c src/core/

# Runtime system
mv src/store.c src/runtime/
mv src/variable.c src/runtime/
mv src/dependency.c src/runtime/
mv src/import_consolidated.c src/runtime/

# Platform & infrastructure
mv src/platform.c src/platform/
mv src/resource.c src/platform/
mv src/security.c src/platform/
mv src/performance.c src/platform/
mv src/utils_consolidated.c src/platform/

# API & integration
mv src/bindings_consolidated.c src/bindings/
mv src/config_consolidated.c src/bindings/
mv src/main.c src/bindings/

# Supporting systems
mv src/systems_consolidated.c src/systems/
mv src/devtools_consolidated.c src/systems/
mv src/docs_consolidated.c src/systems/
```

### Phase 3: Update CMakeLists.txt
Update all source file paths to reflect new structure.

### Phase 4: Update Include Paths
Update all `#include` statements to use proper relative paths.

## Benefits

1. **Logical Organization**: Related functionality grouped together
2. **Genesis Compliance**: 6 clean directories as envisioned
3. **Maintainability**: Easier navigation and understanding
4. **Scalability**: Room for future growth within categories
5. **Team Clarity**: Clear ownership boundaries

## Risks & Mitigation

**Risk**: Include path breaks
**Mitigation**: Systematic update of all includes

**Risk**: Build system breaks  
**Mitigation**: Update CMakeLists.txt simultaneously

**Risk**: Team confusion
**Mitigation**: Clear documentation and communication

## Success Criteria

✅ 6 logical directories created
✅ All files organized by function
✅ Build system continues at 100% success
✅ No regressions in functionality
✅ Team can navigate structure intuitively
✅ Genesis vision of clean organization achieved