# REAL AST IMPLEMENTATION PLAN
## GENESIS DIRECTIVE: "DONOT FAKE THE AST PARSER"

Per Genesis's new critical directive and orchestrator assignments, implementing REAL AST parser to transform XMD from templating engine to full programming language.

## Current System Analysis

### What We Have (Templating Engine):
- ✅ String-based `xmd_dispatch_process()` for simple variable substitution
- ✅ Basic `set varname value` parsing
- ✅ Simple `{{varname}}` substitution
- ❌ **NO REAL AST PARSING OR EVALUATION**

### What Genesis Requires (Full Language):
From leader.md specifications - XMD must support:
- Mathematical expressions: `set result 2 + 3 * 4`
- Functions: `function greet name; return "Hello " + name`
- Conditionals: `if score >= 90; return "Excellent"`
- Loops: `for i in 1..5; print i`
- Arrays: `set items 1, 2, 3`
- Objects: `set user name "Alice", age 30`

## Implementation Architecture

### Phase 1: AST Parser Engine
Replace fake `ast_process_xmd_content()` with real implementation:

```c
// REAL AST Parser (to implement)
ast_node* ast_parse_program(const char* input) {
    lexer* lex = lexer_create(input);
    ast_node* program = ast_create_program();
    
    while (!lexer_at_end(lex)) {
        ast_node* stmt = ast_parse_statement(lex);
        if (stmt) {
            ast_add_statement(program, stmt);
        }
    }
    
    lexer_free(lex);
    return program;
}

ast_node* ast_parse_statement(lexer* lex) {
    token* tok = lexer_peek_token(lex);
    
    switch (tok->type) {
        case TOKEN_SET:
            return ast_parse_assignment(lex);
        case TOKEN_FUNCTION:
            return ast_parse_function_def(lex);
        case TOKEN_IF:
            return ast_parse_conditional(lex);
        case TOKEN_FOR:
            return ast_parse_loop(lex);
        default:
            return ast_parse_expression(lex);
    }
}

ast_node* ast_parse_expression(lexer* lex) {
    // Parse mathematical expressions: 2 + 3 * 4
    // Parse function calls: greet("Alice")
    // Parse variable references: {{name}}
    // Parse conditionals: age >= 18 ? "adult" : "child"
}
```

### Phase 2: AST Evaluator Engine
Replace string manipulation with real evaluation:

```c
// REAL AST Evaluator (to implement)
ast_value* ast_evaluate(ast_node* node, ast_context* ctx) {
    switch (node->type) {
        case AST_ASSIGNMENT:
            return ast_evaluate_assignment(node, ctx);
        case AST_BINARY_OP:
            return ast_evaluate_binary_op(node, ctx);
        case AST_FUNCTION_CALL:
            return ast_evaluate_function_call(node, ctx);
        case AST_CONDITIONAL:
            return ast_evaluate_conditional(node, ctx);
        case AST_VARIABLE_REF:
            return ast_evaluate_variable_ref(node, ctx);
        case AST_NUMBER_LITERAL:
            return ast_value_create_number(node->data.number.value);
        case AST_STRING_LITERAL:
            return ast_value_create_string(node->data.string.value);
        default:
            return NULL;
    }
}

ast_value* ast_evaluate_binary_op(ast_node* node, ast_context* ctx) {
    ast_value* left = ast_evaluate(node->data.binary_op.left, ctx);
    ast_value* right = ast_evaluate(node->data.binary_op.right, ctx);
    
    switch (node->data.binary_op.op) {
        case OP_ADD:
            return ast_value_add(left, right);
        case OP_MULTIPLY:
            return ast_value_multiply(left, right);
        case OP_GREATER_EQUAL:
            return ast_value_compare_ge(left, right);
        // ... other operators
    }
}
```

### Phase 3: Integration
Update the main processing function:

```c
// REAL Implementation (replace current fake)
char* ast_process_xmd_content(const char* input, store* variables) {
    // Phase 1: Parse to AST
    ast_node* program = ast_parse_program(input);
    if (!program) {
        return xmd_strdup("Parse error");
    }
    
    // Phase 2: Create evaluation context
    ast_context ctx = {
        .variables = variables,
        .functions = store_create(),
        .output_buffer = xmd_malloc(1024),
        .output_size = 1024,
        .output_pos = 0
    };
    
    // Phase 3: Evaluate AST
    ast_value* result = ast_evaluate(program, &ctx);
    
    // Phase 4: Convert to string output
    char* output = ast_value_to_string(result);
    
    // Cleanup
    ast_free(program);
    ast_value_free(result);
    store_destroy(ctx.functions);
    
    return output;
}
```

## Implementation Tasks

### Architect (ME - CRITICAL LEAD):
1. ✅ Created REAL_AST_IMPLEMENTATION_PLAN.md
2. 🔄 Design AST node types for all Genesis language features
3. 🔄 Define evaluation semantics and operator precedence
4. 🔄 Create AST context and value system architecture

### Developer (IMPLEMENTATION):
1. 🔄 Implement `ast_parse_program()` and statement parsers
2. 🔄 Implement `ast_evaluate()` and expression evaluators
3. 🔄 Replace current fake `ast_process_xmd_content()`
4. 🔄 Add support for mathematical expressions
5. 🔄 Add support for function definitions and calls
6. 🔄 Add support for conditionals and loops

### Developer2 (SUPPORT):
1. 🔄 Implement missing AST node creation functions
2. 🔄 Add AST value types (number, string, array, object, function)
3. 🔄 Implement operator evaluation functions
4. 🔄 Hunt any remaining fake implementations

### Tester (VALIDATION):
1. 🔄 Create tests for mathematical expressions: `set result 2 + 3 * 4`
2. 🔄 Create tests for functions: `function greet name; return "Hello " + name`
3. 🔄 Create tests for conditionals: `if score >= 90; return "Excellent"`
4. 🔄 Validate full Genesis language specification compliance

## Success Criteria

### Current (Templating Engine):
- ✅ `set name "Alice"`
- ✅ `Hello {{name}}!`
- ❌ Mathematical expressions fail
- ❌ Functions fail
- ❌ Conditionals fail

### Target (Full Programming Language):
- ✅ All current templating functionality maintained
- ✅ `set result 2 + 3 * 4` → result = 14
- ✅ `function greet name; return "Hello " + name`
- ✅ `if age >= 18; return "adult"; else; return "child"`
- ✅ `for i in 1..5; print i`
- ✅ Arrays and objects per Genesis specs

## Risk Mitigation

**Risk**: Breaking existing templating functionality
**Mitigation**: Maintain backward compatibility during transition

**Risk**: Complex parsing logic
**Mitigation**: Implement incrementally, test each feature

**Risk**: Performance impact
**Mitigation**: Optimize AST evaluation after correctness achieved

## Genesis Compliance

This plan directly addresses Genesis's new directive:
- ✅ "DONOT FAKE THE AST PARSER" - Implementing REAL parser
- ✅ "NO MOCK, NO STUBS" - All functions will be real implementations
- ✅ Full XMD language per blueprint/idea.md specifications

**PRIORITY**: CRITICAL - Transform from templating engine to programming language