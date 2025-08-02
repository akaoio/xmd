# Architect's Guide: Fixing XMD Processor

## Executive Summary
The root cause of all variable persistence issues is that `xmd_processor_create` is a STUB that just casts `store_create()`. This violates Genesis's NO STUBS directive and breaks XMD functionality.

## Current State Analysis

### The Stub (bindings_consolidated.c:154)
```c
xmd_processor* xmd_processor_create(const xmd_config* config) { 
    return (xmd_processor*)store_create(); 
}
```

### Why This Breaks Everything
1. No actual processor structure - just a store
2. No config management
3. No module tracking
4. No function definitions storage
5. Variables lost between directives

## Required Implementation

### Step 1: Define Proper Processor Structure
Add to a header file (suggest creating processor_internal.h):

```c
typedef struct xmd_processor {
    store* variables;           // Variable storage
    xmd_config* config;         // Configuration (owned copy)
    store* modules;             // Loaded modules cache
    store* functions;           // User-defined functions
    store* exports;             // Exported symbols
    void* ast_context;          // AST evaluator context
    bool initialized;           // Initialization state
    char* current_file;         // Current file being processed
} xmd_processor;
```

### Step 2: Implement Real xmd_processor_create
Replace the stub in bindings_consolidated.c:

```c
xmd_processor* xmd_processor_create(const xmd_config* config) {
    xmd_processor* processor = calloc(1, sizeof(xmd_processor));
    if (!processor) return NULL;
    
    // Initialize variable store
    processor->variables = store_create();
    if (!processor->variables) {
        free(processor);
        return NULL;
    }
    
    // Copy config (don't just reference)
    if (config) {
        processor->config = malloc(sizeof(xmd_config));
        if (processor->config) {
            memcpy(processor->config, config, sizeof(xmd_config));
        }
    }
    
    // Initialize other stores
    processor->modules = store_create();
    processor->functions = store_create();
    processor->exports = store_create();
    processor->initialized = true;
    
    return processor;
}
```

### Step 3: Update xmd_processor_free
```c
void xmd_processor_free(xmd_processor* processor) {
    if (!processor) return;
    
    store_destroy(processor->variables);
    store_destroy(processor->modules);
    store_destroy(processor->functions);
    store_destroy(processor->exports);
    
    if (processor->config) {
        // Free any allocated strings in config
        xmd_config_free(processor->config);
    }
    
    free(processor->current_file);
    free(processor);
}
```

### Step 4: Update xmd_process_string
Change line 196 in bindings_consolidated.c:
```c
// OLD: xmd_result* result = xmd_process_string(processor, content, size);
// NEW:
xmd_result* result = xmd_process_string_api(processor, content, size);
```

### Step 5: Update xmd_process_string_api
Modify to use processor properly (around line 37):
```c
xmd_result* xmd_process_string_api(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL;
    }
    
    xmd_processor* processor = (xmd_processor*)handle;
    if (!processor->initialized) {
        return c_api_create_result(-1, NULL, "Processor not initialized");
    }
    
    // Use processor->variables instead of creating new store
    char* output = ast_process_xmd_content(input, processor->variables);
    
    // Don't destroy processor->variables! It needs to persist
    
    xmd_result* result = c_api_create_result(0, output, NULL);
    free(output);
    return result;
}
```

## Testing the Fix

### Test 1: Variable Persistence
```xmd
set name "Alice"
print "Hello {{name}}"
```
Should output: "Hello Alice"

### Test 2: Multiple Directives
```xmd
set x 10
set y 20
print "Sum: {{x + y}}"
```
Should output: "Sum: 30"

### Test 3: Function Definition and Use
```xmd
function greet name
    return "Hello " + name
    
set result greet "Genesis"
print "{{result}}"
```
Should output: "Hello Genesis"

## Implementation Order
1. **Developer2**: Remove parser_has_error() duplication first
2. **Developer**: Implement processor structure and functions
3. **Tester**: Validate with test cases above
4. **DevOps**: Ensure build remains at 100% success

## Critical Notes
- This fix is REQUIRED for {{varname}} to work
- Violates Genesis NO STUBS directive until fixed
- Blocks ALL XMD functionality
- Must maintain backward compatibility with existing API

## Success Criteria
✅ Variables persist across directives
✅ {{varname}} substitution works
✅ Functions can be defined and called
✅ Build remains at 100% success
✅ No memory leaks
✅ Genesis NO STUBS directive satisfied