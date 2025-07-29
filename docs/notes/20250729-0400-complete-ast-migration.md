# Complete AST Migration and Remove String Parser

## Current State
- Hybrid system: main processing uses string parser, some directives use AST
- Key AST components implemented: lexer, parser, evaluator
- Some functions migrated: process_set, join, exec with variable substitution

## Migration Plan

### Phase 1: Create AST-based XMD Content Processor
1. Create `ast_process_xmd_content` to replace all string-based processors
2. Use lexer to tokenize entire input including HTML comments
3. Parse XMD directives within comments using AST parser
4. Evaluate directives using existing AST evaluator

### Phase 2: Remove String-Based Functions
1. Remove `process_xmd_content`, `process_xmd_content_enhanced`, `process_xmd_content_fixed`
2. Remove string-based directive processors
3. Remove string-based parsing helpers
4. Update all callers to use AST versions

### Phase 3: Update Entry Points
1. Update `xmd_process_string` to use `ast_process_xmd_content`
2. Update `xmd_process_file` to use AST processor
3. Ensure all API entry points use AST

### Phase 4: Validation and Testing
1. Run all existing tests
2. Fix any failing tests
3. Verify no string parsing remains
4. Check for memory leaks
5. Ensure all INSTRUCTIONS.md rules are followed

## Key Implementation Details
- Lexer must handle HTML comments as special tokens
- Parser must recognize XMD directive structure within comments
- Must maintain backward compatibility with existing XMD syntax
- All functions must follow one-file-per-folder rule
- Maximum 200 lines per file
- Proper error handling and memory management

## Success Criteria
- All tests pass
- No string-based parsing functions remain
- Clean build with no warnings
- Follows all INSTRUCTIONS.md rules
- Ready for commit and push