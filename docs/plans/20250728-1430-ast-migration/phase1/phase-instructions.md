# Phase 1: Core AST Infrastructure

## Components to Create

### 1. AST Node System
- `src/ast_node/ast_node.c` - Core AST node creation/destruction
- `include/ast_node.h` - AST node type definitions
- Following one-function-per-file rule for each node type

### 2. Enhanced Lexer
- `src/lexer_enhanced/lexer_enhanced.c` - Enhanced tokenization
- Extend existing token.h with expression tokens
- Add TOKEN_OPERATOR, TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER

### 3. Source Location Tracking
- `src/source_location/source_location.c` - Location management
- `include/source_location.h` - Location structure

## File Structure (following rules 1-3)
```
src/ast_node_create/ast_node_create.c
src/ast_node_free/ast_node_free.c  
src/ast_node_print/ast_node_print.c
src/lexer_enhanced/lexer_enhanced.c
src/token_create_enhanced/token_create_enhanced.c
```

## Tests First (rule 4)
- `test/test_ast_node.c` - Complete AST node testing
- `test/test_lexer_enhanced.c` - Enhanced lexer testing
- All edge cases and error conditions

## Memory Management (rule 14)
- Proper malloc/free for all AST nodes
- Reference counting for shared nodes
- NULL pointer checks throughout

## Error Handling (rule 13)
- Return codes for all operations
- Meaningful error messages with source locations
- Graceful handling of malformed input