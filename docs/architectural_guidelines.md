# XMD Architectural Guidelines for Refactoring

## Core Principles

### 1. Test-First Refactoring
- **NO refactoring without tests**
- Minimum 80% coverage before touching code
- Integration tests for module boundaries
- Performance benchmarks to prevent regression

### 2. Incremental Migration
- One module at a time
- Verify working state after each step
- Roll back if tests fail
- Keep old code until new code proven

### 3. Feature Protection
- Identify all current features
- Create test matrix for each feature
- Automated regression testing
- User acceptance criteria

## Module Consolidation Guidelines

### Memory Management (utils/memory.c)
Consolidate from:
- `xmd_malloc()` → Safe malloc wrapper
- `xmd_calloc()` → Safe calloc wrapper  
- `xmd_realloc()` → Safe realloc wrapper
- `xmd_strdup()` → String duplication
- `xmd_aligned_alloc()` → Aligned allocation
- `memory_allocate()` → Generic allocator

**Pattern**: Single allocation API with type safety

### String Operations (utils/string.c)
Consolidate from:
- `string_duplicate()` → Remove, use xmd_strdup
- `trim_whitespace()` → Unified trimming
- `skip_whitespace()` → Single implementation
- String manipulation utilities

**Pattern**: Consistent string handling API

### AST Operations (core/ast.c)
Current: 40+ directories, one per function
Target: 3-5 files maximum
- `ast_node.c` → Node creation/destruction
- `ast_parse.c` → Parsing operations
- `ast_evaluate.c` → Evaluation logic
- `ast_transform.c` → AST transformations

**Pattern**: Factory pattern for node creation

## Duplication Removal Strategy

### 1. Identify Pattern
```c
// Current: 15+ similar functions
ast_node* ast_create_X(...) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) return NULL;
    memset(node, 0, sizeof(ast_node));
    node->type = AST_X;
    // Set specific fields
    return node;
}
```

### 2. Create Generic Factory
```c
// Target: Single factory function
ast_node* ast_create_node(ast_node_type type, ...) {
    ast_node* node = xmd_calloc(1, sizeof(ast_node));
    if (!node) return NULL;
    node->type = type;
    // Type-specific initialization
    return node;
}
```

### 3. Maintain API Compatibility
```c
// Wrapper for compatibility
static inline ast_node* ast_create_identifier(const char* name) {
    return ast_create_node(AST_IDENTIFIER, name);
}
```

## Directory Structure Principles

### Before: One Function Per Directory
```
src/
├── ast_create_identifier/
│   └── ast_create_identifier.c (20 lines)
├── ast_create_number/
│   └── ast_create_number.c (22 lines)
└── ... (430+ directories)
```

### After: Logical Grouping
```
src/
├── core/
│   ├── ast.c (2000+ lines, well-organized)
│   ├── ast.h
│   └── ast_internal.h
```

## Safety Checklist

### Pre-Refactoring
- [ ] All tests enabled and passing
- [ ] Coverage baseline established
- [ ] Performance benchmarks recorded
- [ ] Feature matrix documented
- [ ] Rollback plan prepared

### During Refactoring
- [ ] One module at a time
- [ ] Tests run after each change
- [ ] Performance monitored
- [ ] Git commits frequent
- [ ] Team coordination active

### Post-Refactoring
- [ ] All tests still passing
- [ ] Coverage maintained/improved
- [ ] Performance unchanged/better
- [ ] Documentation updated
- [ ] Team review completed

## Error Handling Standards

### Current Issues
- Multiple error handling patterns
- Inconsistent error propagation
- Memory leaks on error paths

### Target Pattern
```c
typedef enum {
    XMD_SUCCESS = 0,
    XMD_ERROR_MEMORY = -1,
    XMD_ERROR_INVALID_PARAM = -2,
    // ... other errors
} xmd_error_t;

// Consistent error handling
xmd_error_t function_name(params, result_type** result) {
    if (!result) return XMD_ERROR_INVALID_PARAM;
    *result = NULL;
    
    // Allocate resources
    // On error: cleanup and return error code
    // On success: set result and return XMD_SUCCESS
}
```

## Performance Considerations

### Consolidation Impact
- Fewer files = faster compilation
- Better cache locality
- Reduced function call overhead
- Opportunity for inlining

### Monitoring Required
- Benchmark before/after each module
- Memory usage tracking
- Execution time profiling
- Cache miss analysis

## Team Coordination

### Architect Responsibilities
- Overall design consistency
- Interface definitions
- Performance requirements
- Quality gates

### Developer Responsibilities  
- Implementation following guidelines
- Test coverage maintenance
- Performance validation
- Documentation updates

### Tester Responsibilities
- Test plan execution
- Coverage reporting
- Regression detection
- Performance monitoring

## Conclusion

These guidelines ensure safe, systematic refactoring while protecting existing functionality. The key is incremental progress with continuous validation.