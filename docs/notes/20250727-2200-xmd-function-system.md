# XMD Function System Implementation

**Date**: 2025-07-27 22:00  
**Author**: Claude Code  
**Issue**: Implement ES6/JS/Python-like function system for XMD language

## Current Status

### ✅ Completed
- Basic `print()` function (works in single-line)
- Basic `cmd()` function (works in single-line) 
- Dynamic buffer allocation for command output
- Multiline directive processing infrastructure

### ❌ Issues Found
1. **Multiline function output not working**: Functions execute but don't output in multiline blocks
2. **CLI uses different processor**: `xmd_process_string_api` (lexer-based) vs `process_xmd_content_*` functions
3. **Output collection mismatch**: Multiline output stored in `_multiline_output` but not propagated correctly

## Root Cause Analysis

The XMD system has two processing paths:
1. **API Path**: `xmd_process_string_api` → lexer-based token processing (used by CLI)
2. **Content Path**: `process_xmd_content_*` → directive-based processing (where I added functions)

## Technical Requirements

### User Request
> "user should be able to write function like es6 or js or python, should be easy and clean"

### Desired Syntax
```javascript
// Function definition
function greet(name) {
    return "Hello " + name;
}

// Function call
greet("World")
print(greet("XMD"))
```

### Core Components Needed
1. **Function Definition Parser** - Parse function syntax
2. **Function Registry** - Store user-defined functions  
3. **Function Call Processor** - Execute function calls with arguments
4. **Scope Management** - Handle local variables and parameters
5. **Return Value System** - Support function returns

## Implementation Strategy

### Phase 1: Fix Multiline Output (Critical)
- Investigate CLI processing path
- Fix output propagation in lexer-based processor
- Ensure print()/cmd() work in multiline

### Phase 2: Function Definition System
- Function parser for ES6-like syntax
- Function storage/registry
- Parameter handling
- Local scope management

### Phase 3: Function Execution
- Function call resolution
- Argument passing
- Return value handling
- Integration with existing directives

## Architecture Design

```
XMD Function System
├── Function Parser (parse function definitions)
├── Function Registry (store functions)
├── Call Processor (execute function calls)
├── Scope Manager (handle variables/parameters)
└── Return Handler (manage return values)
```

## Next Steps
1. Create detailed implementation plan with phases
2. Fix multiline output issue first (blocking)
3. Implement function definition parser
4. Build function execution engine
5. Add comprehensive tests

## Risk Assessment
- **High**: Multiline output issue affects all function features
- **Medium**: Complex scope management for nested function calls
- **Low**: Integration with existing XMD directive system