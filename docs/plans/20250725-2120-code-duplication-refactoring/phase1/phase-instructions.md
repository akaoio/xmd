# Phase 1: Test Infrastructure

## Objective
Create comprehensive test suite for new utility functions before implementation

## Tasks

1. **String Utility Tests**
   - Test string_duplicate with various inputs
   - Test string_extract with boundary conditions
   - Test null pointer handling
   - Test empty string handling

2. **Memory Utility Tests**
   - Test memory_allocate with various sizes
   - Test memory_free_safe with null pointers
   - Test allocation failure scenarios

3. **Lexer Helper Tests**
   - Test lexer_extract_substring with valid ranges
   - Test boundary conditions
   - Test error cases

## Test Files to Create
- `test/utils/string/test_string_duplicate.c`
- `test/utils/string/test_string_extract.c`
- `test/utils/memory/test_memory_allocate.c`
- `test/utils/memory/test_memory_free_safe.c`
- `test/lexer/test_lexer_extract_substring.c`

## Success Criteria
- All test files compile without warnings
- Test framework integration complete
- Tests document expected behavior