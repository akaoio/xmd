# Phase 1 Implementation: Core Parser Foundation

## Objective
Implement the foundational markdown parser with XMD directive detection following TDD principles.

## Architecture Overview
```
Input MD → Lexer → Token Stream → Parser → AST → XMD Detector → Validated Directives
```

## Components to Implement

### 1. Token System (token/token.c)
- Define token types for markdown elements
- Token creation, destruction, and utility functions
- Memory management for token data

### 2. Lexer (lexer/lexer.c)  
- Character-by-character tokenization
- UTF-8 support and line/column tracking
- HTML comment detection for XMD directives

### 3. Parser (parser/parser.c)
- Recursive descent parser for markdown
- AST construction from token stream
- Error recovery and reporting

### 4. AST (ast/ast.c)
- Node types for document structure
- Tree building and traversal functions
- Memory management with reference counting

### 5. XMD Detector (xmd_detector/xmd_detector.c)
- Extract XMD directives from HTML comments
- Validate namespace and syntax
- Parse directive parameters

## Test Strategy
Write comprehensive tests first for each component:
- Unit tests for individual functions
- Integration tests for parser pipeline
- Edge cases and error scenarios
- Memory leak detection

## Success Criteria
- All markdown syntax parsed correctly
- XMD directives detected and validated
- 100% test coverage achieved
- No memory leaks detected
- Performance baseline established (<5ms per MB)

## Key Files to Create
```
src/token/token.c
src/lexer/lexer.c
src/parser/parser.c
src/ast/ast.c
src/xmd_detector/xmd_detector.c
test/token/test_token.c
test/lexer/test_lexer.c
test/parser/test_parser.c
test/ast/test_ast.c
test/xmd_detector/test_xmd_detector.c
```

## Implementation Order
1. Write all tests first (following TDD)
2. Implement token system
3. Implement lexer with UTF-8 support
4. Implement AST structures
5. Implement parser with error handling
6. Implement XMD directive detection
7. Integration testing and optimization