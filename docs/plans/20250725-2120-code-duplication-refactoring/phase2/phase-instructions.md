# Phase 2: Core Utilities Implementation

## Objective
Implement utility functions following one-function-per-file rule

## Implementation Tasks

1. **String Utilities**
   - `src/utils/string/string_duplicate/string_duplicate.c`
   - `src/utils/string/string_extract/string_extract.c`

2. **Memory Utilities**
   - `src/utils/memory/memory_allocate/memory_allocate.c`
   - `src/utils/memory/memory_free_safe/memory_free_safe.c`

3. **Lexer Helpers**
   - `src/lexer/lexer_extract_substring/lexer_extract_substring.c`

## Implementation Guidelines
- Maximum 200 lines per file
- Full Doxygen documentation
- Comprehensive error handling
- No external dependencies

## Header Files
- Create corresponding .h files in same directories
- Use include guards
- Document all function signatures

## Success Criteria
- All functions pass their tests
- No memory leaks
- Clean compilation with -Wall -Wextra