# Phase 1: Fix Multiline Function Output

## Objective
Fix the critical issue where print() and cmd() functions work in single-line comments but not in multiline blocks.

## Problem Analysis
- CLI uses `xmd_process_string_api` (lexer-based) 
- Functions implemented in `process_xmd_content_*` (directive-based)
- Output collection mechanism mismatch

## Tasks

### 1. Investigate CLI Processing Path
- **File**: Research which processor CLI actually uses
- **Goal**: Understand why multiline functions don't output
- **Output**: Clear understanding of processing flow

### 2. Fix Lexer-Based Function Support
- **File**: Add function support to lexer-based processor
- **Implementation**: Modify token processing to handle function calls
- **Location**: `src/bindings/c_api/c_api.c`

### 3. Unify Function Processing
- **Goal**: Ensure functions work in both single-line and multiline
- **Approach**: Either fix lexer path or redirect to directive path
- **Testing**: Verify both contexts work

## Success Criteria
- `print(variable)` outputs in multiline blocks
- `cmd("command")` outputs in multiline blocks  
- No regression in single-line function calls
- All existing XMD features continue working

## Files to Modify
- `src/bindings/c_api/c_api.c` (lexer-based processor)
- Test files to verify functionality

## Timeline
- Investigation: 30 minutes
- Implementation: 1 hour
- Testing: 30 minutes