# Test Migration Plan - Legacy to AST Functions

## Date: 2025-01-29 18:00

## Summary
Before removing legacy string parsers, all test files must be migrated to use AST functions. This document provides a migration guide for each test file.

## Test Files Requiring Migration

### 1. test/xmd_processor/test_xmd_processor.c
**Current**: Uses `process_xmd_content()` and `process_xmd_directive()`
**Migration**:
```c
// Replace:
char* process_xmd_content(const char* input, store* variables);
// With:
char* ast_process_xmd_content(const char* input, store* variables);

// Remove process_xmd_directive - no AST equivalent needed
```

### 2. test/integration/test_advanced_integration.c  
**Current**: Uses `process_xmd_content_enhanced()`
**Migration**:
```c
// Replace all calls to:
process_xmd_content_enhanced(input, variables)
// With:
ast_process_xmd_content(input, variables)
```

### 3. test/stress/test_brutal_nesting.c
**Current**: Uses `process_xmd_content()`
**Migration**: Replace with `ast_process_xmd_content()`

### 4. test/stress/test_resource_exhaustion.c
**Current**: Uses `process_xmd_content()`  
**Migration**: Replace with `ast_process_xmd_content()`

### 5. test/xmd_processor/test_advanced_scripting.c
**Current**: Uses `process_xmd_content_enhanced()`
**Migration**: Replace with `ast_process_xmd_content()`

## Migration Steps

1. **Update includes**:
   ```c
   // Add:
   #include "../../include/ast_evaluator.h"
   ```

2. **Update function declarations**:
   ```c
   // Replace legacy declarations with:
   extern char* ast_process_xmd_content(const char* input, store* variables);
   ```

3. **Update all function calls** in test bodies

4. **Remove any direct directive processing** - AST handles this internally

## Testing After Migration

1. Run each migrated test individually
2. Verify output matches expected results
3. Check for memory leaks with valgrind
4. Ensure no references to legacy functions remain

## Order of Migration

1. Start with `test_truncate_fix.c` (already uses AST)
2. Migrate simple tests first (`test_xmd_processor.c`)
3. Then complex integration tests
4. Finally stress tests

## Notes

- The AST parser has an elif/else bug that outputs both branches
- Some tests may fail due to this bug, not the migration
- Document any behavioral differences found during migration