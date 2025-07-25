# Phase 1: Core Parser Foundation

## Objective
Establish the foundational markdown parser with XMD directive detection capabilities.

## Components

### 1.1 Lexical Scanner (lexer/)
- `lexer/lexer.c`: Main tokenization logic
- `token/token.c`: Token type definitions
- `scanner/scanner.c`: Character stream handling

### 1.2 Parser Core (parser/)
- `parser/parser.c`: Recursive descent parser
- `ast/ast.c`: Abstract syntax tree structures
- `visitor/visitor.c`: AST visitor pattern

### 1.3 XMD Detection (xmd_detector/)
- `xmd_detector/xmd_detector.c`: HTML comment XMD directive detection
- `directive/directive.c`: Directive type identification
- `validator/validator.c`: Syntax validation

### 1.4 Test Framework (test/)
- `test_runner/test_runner.c`: Main test execution
- `assert/assert.c`: Custom assertions
- `fixtures/fixtures.c`: Test data management

## Implementation Steps

1. **Token Types Definition**
   - Define all markdown token types
   - Add XMD-specific tokens
   - Create token factory functions

2. **Scanner Implementation**
   - Character buffering
   - Line/column tracking
   - UTF-8 support

3. **Lexer Development**
   - Markdown syntax tokenization
   - HTML comment detection
   - XMD directive parsing

4. **AST Design**
   - Node type hierarchy
   - Memory management
   - Visitor interface

5. **Parser Logic**
   - Recursive descent implementation
   - Error recovery
   - AST construction

6. **XMD Integration**
   - Directive extraction
   - Namespace validation
   - Parameter parsing

## Test Coverage
- Unit tests for each component
- Integration tests for parser pipeline
- Edge cases and error scenarios
- Performance benchmarks

## Deliverables
- Working markdown parser
- XMD directive detection
- Complete test suite
- Performance baseline