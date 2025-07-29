# User-Defined Functions Implementation Plan

## Overview
Implement user-defined functions in XMD following the blueprint's shell-style syntax and natural language principles.

## Target Syntax (from Blueprint)
```xmd
// Natural/Mobile syntax:
function add a b
    return a + b

// Usage
result = add 10 20
```

## Current State Analysis
- ✅ `AST_FUNCTION_CALL` exists for calling built-in functions (exec, join, import)
- ❌ No `AST_FUNCTION_DEF` for defining user functions
- ❌ No function storage/lookup mechanism
- ❌ No function scope/parameter handling
- ❌ No return statement processing

## Implementation Phases

### Phase 1: Core AST Extensions
- Add `AST_FUNCTION_DEF` node type
- Add function definition parsing
- Add function storage in evaluator context
- Basic function call resolution

### Phase 2: Parameter & Scope Management  
- Parameter binding and local scope
- Return statement handling
- Function-local variable isolation

### Phase 3: Advanced Features
- Default parameters
- Variable arguments
- Recursive functions
- Function overloading

### Phase 4: Integration & Testing
- Shell-style syntax transformation
- Comprehensive test suite
- Documentation update

## Success Criteria
1. Parse `function name param1 param2` syntax
2. Store functions in evaluator context
3. Call user functions with `name arg1 arg2` syntax
4. Proper parameter binding and scope isolation
5. Return values correctly
6. Support recursion
7. All tests pass

## Next Steps
Start with Phase 1 implementation.