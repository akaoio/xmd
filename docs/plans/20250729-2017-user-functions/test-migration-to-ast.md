# Test Migration to AST Functions

## Overview
Before we can purge legacy string parsers, we must migrate all tests to use AST functions.

## Tests Requiring Migration

### 1. test/integration/test_advanced_integration.c
- **Currently uses**: `process_xmd_content_enhanced()`
- **Migrate to**: `ast_process_xmd_content()`
- **Notes**: May use enhanced features - verify AST supports all functionality

### 2. test/stress/test_brutal_nesting.c  
- **Currently uses**: `process_xmd_content()`
- **Migrate to**: `ast_process_xmd_content()`
- **Notes**: Stress test - ensure AST handles deep nesting

### 3. test/stress/test_resource_exhaustion.c
- **Currently uses**: `process_xmd_content()`
- **Migrate to**: `ast_process_xmd_content()`
- **Notes**: Resource limits test - verify AST respects limits

### 4. test/xmd_processor/test_advanced_scripting.c
- **Currently uses**: Legacy string parser functions
- **Migrate to**: AST equivalents
- **Notes**: Complex scripting scenarios

### 5. test/xmd_processor/test_xmd_processor.c
- **Currently uses**: `process_xmd_content()`
- **Migrate to**: `ast_process_xmd_content()`
- **Notes**: Core processor tests - critical to migrate correctly

### 6. test/xmd_processor/test_truncate_fix.c
- **Currently uses**: Legacy functions
- **Migrate to**: AST functions
- **Notes**: Tests truncation handling

## Migration Steps

1. **Function Signature Changes**:
   ```c
   // Old: process_xmd_content(input, variables)
   // New: ast_process_xmd_content(input, variables)
   ```

2. **Include Updates**:
   ```c
   // Remove: #include "process_xmd_content.h"
   // Add: #include "ast_process_xmd_content.h"
   ```

3. **Variable Store Changes**:
   - AST functions use the same `store*` type
   - No changes needed for variable handling

4. **Output Handling**:
   - AST functions return allocated strings
   - Remember to free the result

## Testing Migration Success

1. Run each test individually after migration
2. Compare output with legacy function results
3. Ensure all edge cases still pass
4. Check memory usage hasn't increased significantly

## Blocked By

- Library build failure (libxmd_lib.a not created)
- Test executables not being generated
- Need BO to fix build system first

## Team Assignments

- **XOAI**: Document migration requirements (COMPLETE)
- **BO**: Fix build system, then help migrate tests
- **CAM**: Validate migrated tests produce same results
- **DADDY**: Coordinate migration effort

---
*Created by XOAI for team reference*