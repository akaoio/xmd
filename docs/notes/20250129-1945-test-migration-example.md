# Test Migration Example - Legacy to AST

## Date: 2025-01-29 19:45

## Summary
Concrete example of migrating test_xmd_processor.c from legacy to AST functions.

## Migration Changes Required

### 1. Update Includes
```c
// OLD:
// External functions from unified processor
char* process_xmd_content(const char* input, store* variables);
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size);

// NEW:
#include "../../include/ast_evaluator.h"
// External AST function
extern char* ast_process_xmd_content(const char* input, store* variables);
```

### 2. Update Function Calls
```c
// OLD:
char* result = process_xmd_content(input, vars);

// NEW:
char* result = ast_process_xmd_content(input, vars);
```

### 3. Remove process_xmd_directive Usage
The AST parser doesn't expose a direct directive processor. All directives are handled internally by ast_process_xmd_content().

### 4. Complete Example Migration

**BEFORE:**
```c
void test_basic_variable_substitution(void) {
    printf("Testing basic variable substitution...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = 
        "<!-- xmd set name=\"World\" -->\n"
        "Hello {{name}}!\n";
    
    char* result = process_xmd_content(input, vars);
    assert(result != NULL);
    assert(strstr(result, "Hello World!") != NULL);
    assert(strstr(result, "xmd set") == NULL);
    
    free(result);
    store_destroy(vars);
    printf("✅ Basic variable substitution test passed\n");
}
```

**AFTER:**
```c
void test_basic_variable_substitution(void) {
    printf("Testing basic variable substitution...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* input = 
        "<!-- xmd set name=\"World\" -->\n"
        "Hello {{name}}!\n";
    
    char* result = ast_process_xmd_content(input, vars);
    assert(result != NULL);
    assert(strstr(result, "Hello World!") != NULL);
    assert(strstr(result, "xmd set") == NULL);
    
    free(result);
    store_destroy(vars);
    printf("✅ Basic variable substitution test passed\n");
}
```

## Migration Script Pattern

For bulk migration, use this sed pattern:
```bash
# Replace function declarations
sed -i 's/char\* process_xmd_content(/extern char* ast_process_xmd_content(/g' test_file.c

# Replace function calls
sed -i 's/process_xmd_content(/ast_process_xmd_content(/g' test_file.c
sed -i 's/process_xmd_content_enhanced(/ast_process_xmd_content(/g' test_file.c

# Add AST include after variable.h include
sed -i '/include "variable.h"/a #include "../../include/ast_evaluator.h"' test_file.c
```

## Files Needing Migration

Priority order (based on simplicity):
1. test/xmd_processor/test_xmd_processor.c - Basic tests
2. test/xmd_processor/test_advanced_scripting.c - Uses enhanced
3. test/stress/test_brutal_nesting.c - Stress tests
4. test/stress/test_resource_exhaustion.c - Resource tests
5. test/integration/test_advanced_integration.c - Complex tests

## Testing After Migration

1. Build with `./build.sh` (BO only)
2. Run individual test: `./build/test_xmd_processor`
3. Check for any behavioral differences
4. Note any elif/else issues (known bug)

---
*Migration example by XOAI - Ready for team use*