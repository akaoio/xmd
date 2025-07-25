# Phase 3: Refactoring & Cleanup

## Objective
Replace duplicated code with utility functions and clean up codebase

## Refactoring Tasks

1. **Lexer.c Refactoring**
   - Replace 5 instances of malloc/memcpy pattern
   - Use lexer_extract_substring function
   - Update includes and dependencies

2. **Remove Destroy Aliases**
   - Remove lexer_destroy (use lexer_free directly)
   - Remove token_destroy (use token_free directly)
   - Remove token_list_destroy (use token_list_free directly)
   - Update all call sites

3. **Update Build System**
   - Add new source files to CMakeLists.txt
   - Create utility library targets
   - Update test configurations

4. **Documentation Updates**
   - Update API documentation
   - Add utility function usage examples
   - Update architecture documentation

## Verification Steps
- Run full test suite
- Check with valgrind for memory leaks
- Verify performance is maintained
- Code review for missed duplications

## Success Criteria
- All tests pass
- No new warnings
- Reduced code size
- Improved maintainability