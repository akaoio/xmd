# Legacy String Parser Purge Sequence

## Status: Ready to Execute
AST migration confirmed complete in production code. Legacy string parsers are dead code.

## Phase 1: Safe Dead Code Removal (IMMEDIATE)
These functions have zero call sites and can be safely deleted:

### 1.1 Legacy Preprocessors (605 lines total)
- `src/bindings/c_api/preprocess_variables/` (81 lines)
- `src/bindings/c_api/preprocess_if_statements/` (209 lines)  
- `src/bindings/c_api/preprocess_for_loops/` (315 lines)
- Remove declarations from `include/c_api_internal.h` lines 39, 41, 44

### 1.2 Build System Fix
- Update CMakeLists.txt to remove preprocess_* directories
- Fix GLOB_RECURSE conflicts causing current build failures

## Phase 2: Test Migration Support (COORDINATED)
CAM reports tests still use legacy functions - coordinate with team:

### 2.1 Test Function Migration
Work with CAM to update remaining test files calling legacy:
- `process_xmd_content()` → `ast_process_xmd_content()`
- Verify test behaviors remain consistent

## Phase 3: Systematic Duplicate Removal (PLANNED)
Based on duplicate-code-report.md - 26+ directories identified:

### 3.1 Complete Duplicate Variants (Safe)
- Remove 2 extra variants of `process_xmd_content` (keep AST version)
- Remove 1 extra variant of multiline processor
- Remove `parse_array_literal_bridge.c` (exact duplicate)

### 3.2 Thin Wrappers (Low Risk)
- Remove wrappers that only call AST functions
- Direct callers to AST functions

### 3.3 Unused Functions (Safe)
- `parse_range/`, `parse_collection/`
- `process_cmd_function/`, `process_print_function/`

## Coordination Notes
- **BO**: Working on import fixes, avoid conflicts
- **CAM**: Testing coordinator, inform of purge impact on tests
- **Build**: Current failures due to duplicate files, Phase 1 will fix

## Expected Benefits
- Fix current build failures
- Reduce codebase by 30-40%
- Eliminate maintenance burden
- Improve build consistency

---
*Architect purge plan - ready for execution*