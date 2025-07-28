# AST Implementation Notes

## Analysis of Current String-Based Issues

### Problems Identified
1. **Error-prone parsing**: strchr/strstr can miss edge cases
2. **No source tracking**: Errors don't show location in source
3. **Limited extensibility**: Adding operators requires string surgery
4. **Type safety**: No compile-time validation of AST structure

### Key Files to Replace
- `process_set.c:96-180` - Assignment parsing with strchr
- `process_directive.c:50-94` - Command extraction with string ops
- `process_multiline_directive_enhanced.c:49` - Line-by-line tokenization

## AST Architecture Design

### Node Hierarchy
```
AST_PROGRAM (root)
├── AST_DIRECTIVE (xmd commands)
│   ├── AST_ASSIGNMENT (var = value)
│   ├── AST_CONDITIONAL (if/elif/else)  
│   └── AST_LOOP (for loops)
├── AST_EXPRESSION
│   ├── AST_BINARY_OP (+, -, ==, etc)
│   ├── AST_FUNCTION_CALL (import, exec)
│   └── AST_LITERAL (strings, numbers)
```

### Memory Management Strategy
- Each node owns its children (tree ownership)
- Reference counting for shared subtrees
- Single ast_free() call frees entire tree

### Parser Strategy  
- Recursive descent with operator precedence
- Left-to-right associativity for same precedence
- Error recovery with meaningful messages

### Integration Points
- Replace process_directive() with ast_parse_directive()
- Replace variable assignment logic with ast_evaluate()
- Maintain same external API initially

## Implementation Order
1. Core AST nodes and memory management
2. Enhanced lexer with all token types
3. Recursive descent parser
4. AST evaluator/interpreter
5. Integration with existing processor
6. String parser removal

## Testing Strategy
- Unit tests for each AST node type
- Parser tests with valid/invalid syntax
- Integration tests with existing XMD files
- Performance benchmarks vs string parsing