# XMD Processor Create STUB Fix

## CRITICAL TECH DEBT FOUND

### Issue
Line 154 in bindings_consolidated.c:
```c
xmd_processor* xmd_processor_create(const xmd_config* config) { return (xmd_processor*)store_create(); }
```

**THIS IS A STUB!** It just casts store_create() - violates Genesis NO STUBS directive!

### Root Cause of Variable Persistence Issue
1. xmd_processor_create just returns a store (variable hash map)
2. No proper processor state management
3. Each file gets new processor = new store = loses all variables

### Proper Implementation Needed

```c
typedef struct xmd_processor {
    store* variables;           // Variable storage
    xmd_config* config;         // Configuration
    store* modules;             // Loaded modules
    store* functions;           // User-defined functions
    bool initialized;           // Init state
} xmd_processor;

xmd_processor* xmd_processor_create(const xmd_config* config) {
    xmd_processor* processor = malloc(sizeof(xmd_processor));
    if (!processor) return NULL;
    
    processor->variables = store_create();
    processor->config = config;  // Should copy, not just reference
    processor->modules = store_create();
    processor->functions = store_create();
    processor->initialized = true;
    
    return processor;
}

void xmd_processor_free(xmd_processor* processor) {
    if (!processor) return;
    
    store_destroy(processor->variables);
    store_destroy(processor->modules);
    store_destroy(processor->functions);
    // Free config copy
    free(processor);
}
```

### Files to Update
1. bindings_consolidated.c - Replace stub with real implementation
2. Add proper processor structure definition
3. Update xmd_process_string to use processor->variables

### Testing After Fix
1. Variables should persist within file processing
2. {{varname}} substitution should work
3. set directives should maintain state

This fixes the root cause that architect identified!