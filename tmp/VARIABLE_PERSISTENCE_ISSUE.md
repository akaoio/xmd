# Variable Persistence Architecture Issue

## Problem Statement
Variables are not persisting between directives in XMD files. When processing:
```xmd
set name "World"
Hello, {{name}}!
```

The output shows: `set name "World"Hello, !` (variable is empty)

## Root Cause Analysis

### 1. Processor Lifecycle Issue
**Location**: `src/main.c:190-239` (cmd_process function)
```c
xmd_processor* processor = xmd_processor_create(config);
// ... process file ...
xmd_processor_free(processor);
```
**Issue**: New processor created for each file, destroying variable state

### 2. Processor Implementation Flaw
**Location**: `src/bindings_consolidated.c:154`
```c
xmd_processor* xmd_processor_create(const xmd_config* config) { 
    return (xmd_processor*)store_create(); 
}
```
**Issue**: Processor is just a cast of store - no proper state management

### 3. Processing Within File
Even within a single file, variables may not persist between directives if each directive is processed independently.

## Proposed Solutions

### Solution 1: Global Processor (Quick Fix)
Maintain a global processor instance across file processing:
```c
static xmd_processor* global_processor = NULL;

int cmd_process(int argc, char* argv[]) {
    if (!global_processor) {
        global_processor = xmd_processor_create(config);
    }
    // Use global_processor instead of creating new one
}
```

### Solution 2: Proper Processor Implementation (Correct Fix)
Create a real processor structure that maintains state:
```c
typedef struct {
    store* variables;          // Variable storage
    xmd_config* config;        // Configuration
    module_registry* modules;  // Module state
    import_tracker* imports;   // Import state
} xmd_processor_internal;

xmd_processor* xmd_processor_create(const xmd_config* config) {
    xmd_processor_internal* proc = malloc(sizeof(xmd_processor_internal));
    proc->variables = store_create();
    proc->config = config;
    // ... initialize other state
    return (xmd_processor*)proc;
}
```

### Solution 3: Context Passing (Architectural Fix)
Pass processor context through all processing functions:
- native_xmd_process_file should receive and update processor state
- xmd_dispatch_process should maintain variable state across directives
- Each directive should update the same variable store

## Impact on Team

- **Developer**: Already fixed lexer to recognize bare keywords ✅
- **Developer2**: Already migrated to {{varname}} syntax ✅
- **Architect**: Need to fix processor architecture for persistence

## Recommended Action

1. Implement Solution 2 (Proper Processor) for correct architecture
2. Ensure processor state persists across directives within a file
3. Test with multiple set/use patterns
4. Consider session persistence for interactive mode