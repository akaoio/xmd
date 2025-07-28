# Parser Implementation Notes

## Current Status
- ✅ AST node system complete with all creation functions
- ✅ Enhanced lexer producing proper token streams
- 🔄 Need recursive descent parser to build AST from tokens

## Parser Architecture Design

### Parser State Structure
```c
typedef struct {
    token* tokens;           // Token stream from lexer
    token* current_token;    // Current parsing position
    size_t position;         // Current token index
    const char* filename;    // Source filename for errors
    bool has_error;          // Error flag
    char* error_message;     // Last error message
} parser_state;
```

### Precedence Hierarchy (lowest to highest)
1. Assignment operators (=, +=)
2. Logical OR (||)
3. Logical AND (&&)
4. Equality (==, !=)
5. Relational (<, >, <=, >=)
6. Additive (+, -)
7. Multiplicative (*, /)
8. Unary (!, -)
9. Primary (literals, identifiers, function calls)

### Key Parsing Functions
- `ast_parse_program()` - Entry point, parse entire program
- `ast_parse_statement()` - Parse single statement
- `ast_parse_expression()` - Parse expressions with precedence
- `ast_parse_assignment()` - Handle variable assignments

### Integration with Existing Code
Parser will replace string-based parsing in:
- `process_set.c` assignment logic → `ast_parse_assignment()`
- `process_directive.c` command parsing → `ast_parse_directive()`
- Expression evaluation throughout codebase

### Error Recovery Strategy
- Stop at statement boundaries on errors
- Continue parsing after semicolons or newlines
- Collect multiple errors before failing
- Provide source location context

### Testing Strategy
- Test each grammar rule independently
- Test operator precedence thoroughly
- Test error conditions and recovery
- Integration tests with real XMD syntax

## Implementation Priority
1. Basic expression parsing (literals, identifiers, binary ops)
2. Assignment statements (var = value, var += value)
3. Function calls (import, exec, print)
4. Control structures (if/for) - later phase
5. Integration with existing XMD processor