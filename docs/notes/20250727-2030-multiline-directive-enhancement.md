# Multiline Directive Enhancement

**Date**: 2025-07-27 20:30  
**Issue**: Multiline directives only support `set` commands, missing all other XMD directives  
**Impact**: Users cannot use exec, if, for, etc. in multiline blocks as documented

## Current Implementation Analysis

### Working
- `process_multiline_directive()` handles `set` commands only
- `is_multiline_directive()` correctly detects multiline format
- Documentation shows full multiline support expected

### Missing Directives
- `exec` - command execution  
- `if/elif/else/endif` - conditionals
- `for/endfor` - loops
- `import` - module imports
- All other supported single-line directives

## Technical Requirements

### Current Limitations
1. `process_multiline_directive()` hardcoded for `set` only (line 30-34)
2. No context state management for control flow
3. No output buffer handling for multiline blocks
4. No error propagation for failed directives

### Required Changes
1. **Extend `process_multiline_directive()`** to support all directive types
2. **Add context management** for if/for blocks spanning multiple lines
3. **Implement output buffering** for multiline directive results
4. **Error handling** for invalid multiline syntax

## Implementation Strategy

### Phase 1: Core Infrastructure
- Modify `process_multiline_directive()` to use generic `process_directive()`
- Add multiline context state management
- Implement output collection for multiline blocks

### Phase 2: Control Flow Support  
- Handle if/elif/else/endif blocks in multiline
- Support for/endfor loops in multiline
- Proper scope management for nested structures

### Phase 3: Advanced Features
- exec command support with dynamic buffers
- import directive support
- Error recovery and validation

## Files to Modify
- `src/xmd_processor/process_multiline_directive/process_multiline_directive.c`
- `include/xmd_processor_internal.h` (function signatures)
- Tests in appropriate test directories

## Expected Behavior
```markdown
<!-- xmd:
set name="Alice"
exec date
if name == "Alice"
    set greeting="Hello Admin"
else  
    set greeting="Hello User"
endif
for i in range(1,3)
    exec echo "Item {{i}}"
endfor
-->
```

Should work identically to equivalent single-line directives.