# Code Duplication Refactoring Note

**Date**: 2025-07-25 21:20
**Author**: System Refactoring
**Topic**: Eliminate code duplication in XMD codebase

## Overview

This refactoring addresses significant code duplication found in the XMD codebase,
particularly in lexer.c where identical malloc/memcpy patterns appear 5 times.

## Issues Identified

1. **Lexer String Extraction Pattern** (5x duplication in lexer.c)
   - Lines: ~166-174, ~203-211, ~246-254, ~280-288, ~323-331
   - Pattern: malloc + null check + memcpy + null termination

2. **Create/Free Function Patterns**
   - Repeated across: lexer, token, variable, store_entry, error_context, module
   - Standard malloc/init/return and null-check/free patterns

3. **Trivial Destroy Aliases**
   - lexer_destroy, token_destroy, token_list_destroy
   - Simply call corresponding _free function

## Solution Strategy

1. Create utility module for common string operations
2. Extract lexer substring function
3. Create macros for standard create/free patterns
4. Remove unnecessary destroy aliases

## New Components

### String Utilities
- `string_duplicate/string_duplicate.c` - Safe string duplication
- `string_extract/string_extract.c` - Extract substring with bounds

### Memory Utilities  
- `memory_allocate/memory_allocate.c` - Safe allocation wrapper
- `memory_free_safe/memory_free_safe.c` - Null-safe free wrapper

### Lexer Helpers
- `lexer_extract_substring/lexer_extract_substring.c` - Extract lexer substring

## Benefits

- Eliminates 100+ lines of duplicated code
- Improves maintainability
- Reduces bug surface area
- Enforces consistent error handling

## Testing Strategy

- Unit tests for each new utility function
- Integration tests to ensure refactoring doesn't break existing functionality
- Memory leak tests with valgrind