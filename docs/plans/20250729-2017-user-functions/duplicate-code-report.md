# Duplicate Code Report

## Overview
Found significant code duplication in XMD codebase that should be removed after legacy parser purge.

## 1. Triple String Parser Implementation

### Files:
- `src/xmd_processor/process_xmd_content/process_xmd_content.c` (Original)
- `src/xmd_processor/process_xmd_content_enhanced/process_xmd_content_enhanced.c` (Enhanced)
- `src/xmd_processor/process_xmd_content_fixed/process_xmd_content_fixed.c` (Fixed)

### Analysis:
- All three implement similar string-based parsing logic
- Enhanced version adds minor features
- Fixed version patches bugs in original
- **Recommendation**: Remove all three, use only `ast_process_xmd_content()`

## 2. Array Literal Parsing Duplication

### Files:
- `src/xmd_processor/parse_array_literal/parse_array_literal.c`
- `src/xmd_processor/parse_array_literal_bridge.c`
- `src/ast_parse_array_literal/ast_parse_array_literal.c` (AST version - keep)

### Analysis:
- Bridge file appears to be exact duplicate of parse_array_literal
- Both are thin wrappers calling AST version
- **Recommendation**: Remove both legacy versions, keep only AST

## 3. Multiline Directive Processing

### Files:
- `src/xmd_processor/process_multiline_directive/process_multiline_directive.c`
- `src/xmd_processor/process_multiline_directive_enhanced/process_multiline_directive_enhanced.c`
- `src/ast_process_multiline_directive/ast_process_multiline_directive.c` (AST version - keep)

### Analysis:
- Two legacy string-based implementations
- Enhanced adds minor improvements
- **Recommendation**: Remove both legacy versions

## 4. Directive Processing Pattern

Found many directive processors with duplicate parsing logic:
- `process_if/`, `process_elif/`, `process_else/`, `process_endif/`
- `process_for/`, `process_exec/`, `process_set/`
- Each reimplements similar string parsing patterns
- **Recommendation**: Consolidate into AST-based directive processor

## 5. Wrapper Functions

### Thin wrappers that just call AST versions:
- `substitute_variables/` → calls `ast_substitute_variables()`
- `process_text_with_directives/` → calls enhanced processor

### Dead code (completely unused):
- `parse_range/`
- `parse_collection/`
- `process_cmd_function/`
- `process_print_function/`

## Summary Statistics

- **26+ directories** containing legacy string parsers
- **3 variants** of main XMD content processor
- **2 variants** of multiline directive processor
- **10+ directive processors** with duplicate logic
- **4+ thin wrappers** that just call AST functions
- **4+ completely unused** parser functions

## Estimated Code Reduction

Removing these duplicates would:
- Reduce codebase by ~30-40%
- Eliminate maintenance burden
- Improve consistency
- Reduce bug surface area

## Action Plan

1. Fix build system (current blocker)
2. Migrate tests to AST functions
3. Remove thin wrappers first (safe)
4. Remove unused code (safe)
5. Remove legacy string parsers
6. Remove duplicate processors

---
*Report compiled by XOAI for team reference*