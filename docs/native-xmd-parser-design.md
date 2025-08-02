# Native XMD Parser Design - Genesis Vision Implementation

## Genesis Blueprint Requirements

**Target Syntax (mobile-first programming language):**
```xmd
set name "Genesis"
set age 25
print "Hello " + name

if age >= 18
    print "Adult"
else
    print "Minor"

function greet name
    print "Hello " + name

greet "World"
```

## Architecture Design

### 1. Native XMD Lexer
- **Token types**: KEYWORD, IDENTIFIER, STRING, NUMBER, OPERATOR, NEWLINE
- **No special chars**: Space-separated tokens only
- **Mobile-friendly**: No shift/alt/symbol requirements

### 2. Native XMD Parser  
- **Statement-based**: Line-oriented parsing
- **Indentation-aware**: Python-like blocks
- **Natural language**: English keywords only

### 3. Native XMD Evaluator
- **Variables**: Dynamic typing (string, number, boolean)
- **Functions**: User-defined with parameters
- **Control flow**: if/else, for loops
- **Operations**: Math, string concat, comparisons

## Implementation Strategy

### Phase A: Dual System Support
- **Maintain**: Current HTML comment system (working)
- **Add**: Native XMD parser alongside
- **Detect**: File content type and route appropriately

### Phase B: Gradual Migration
- **Test files**: Create native XMD examples
- **Documentation**: Update to show both syntaxes
- **User choice**: Support both during transition

### Phase C: Genesis Vision Complete
- **Default**: Native XMD becomes primary
- **Legacy**: HTML comments optional/deprecated
- **Mobile**: Touch-friendly REPL ready

## File Structure

```
src/native_xmd/
├── native_lexer.c      # Mobile-optimized tokenizer
├── native_parser.c     # Natural language parser  
├── native_evaluator.c  # Programming language runtime
└── xmd_dispatcher.c    # Route HTML vs native syntax
```

## Integration Points

- **CLI**: Auto-detect syntax and route to appropriate processor
- **API**: Support both processing modes
- **Tests**: Dual test suites for both systems
- **Build**: Compile both parsers together

**Priority**: Implement alongside Phase 7 consolidation (dual track approach)