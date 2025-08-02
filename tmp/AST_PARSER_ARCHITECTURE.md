# AST Parser Architecture Design
## Genesis Compliance: Real AST Parser Implementation

The AST node structures in `include/ast_node.h` are excellent and comprehensive. The missing components are the **parser** and **evaluator** engines.

## Architecture Analysis

### What EXISTS (Excellent Foundation):
- ✅ Complete AST node type definitions (42 types)
- ✅ Comprehensive data structures for all language constructs
- ✅ Node creation functions in `ast_consolidated.c`
- ✅ Memory management and source location tracking

### What's MISSING (Critical Gap):
- ❌ Parser functions to convert source code to AST
- ❌ Evaluator functions to execute AST nodes
- ❌ Integration with the processor system

## Parser Engine Design

### Core Parser Functions (to implement):

```c
// Primary parsing interface
ast_node* ast_parse_program(const char* input);

// Statement parsers
ast_node* ast_parse_statement(lexer* lex);
ast_node* ast_parse_assignment(lexer* lex);      // set varname value
ast_node* ast_parse_function_def(lexer* lex);    // function name args; body
ast_node* ast_parse_conditional(lexer* lex);     // if condition; then; else
ast_node* ast_parse_loop(lexer* lex);            // for var in iterable; body

// Expression parsers (with precedence)
ast_node* ast_parse_expression(lexer* lex);
ast_node* ast_parse_logical_or(lexer* lex);      // ||
ast_node* ast_parse_logical_and(lexer* lex);     // &&
ast_node* ast_parse_equality(lexer* lex);        // == !=
ast_node* ast_parse_comparison(lexer* lex);      // < <= > >=
ast_node* ast_parse_addition(lexer* lex);        // + -
ast_node* ast_parse_multiplication(lexer* lex);  // * /
ast_node* ast_parse_unary(lexer* lex);          // ! -
ast_node* ast_parse_primary(lexer* lex);        // literals, vars, function calls

// Utility parsers
ast_node* ast_parse_array_literal(lexer* lex);   // [1, 2, 3]
ast_node* ast_parse_function_call(lexer* lex);   // func(args)
ast_node* ast_parse_variable_ref(lexer* lex);    // {{varname}}
```

### Parser Implementation Strategy:

1. **Recursive Descent Parser**: Using the existing lexer system
2. **Operator Precedence**: Mathematical expressions follow standard precedence
3. **Error Recovery**: Graceful handling of syntax errors
4. **Location Tracking**: Maintain source positions for debugging

## Evaluator Engine Design

### Core Evaluator Functions (to implement):

```c
// AST Value system
typedef enum {
    AST_VALUE_NULL,
    AST_VALUE_STRING,
    AST_VALUE_NUMBER,
    AST_VALUE_BOOLEAN,
    AST_VALUE_ARRAY,
    AST_VALUE_OBJECT,
    AST_VALUE_FUNCTION
} ast_value_type;

typedef struct ast_value {
    ast_value_type type;
    union {
        char* string;
        double number;
        bool boolean;
        struct { ast_value** items; size_t count; } array;
        store* object;  // Key-value pairs
        struct { ast_node* body; char** params; size_t param_count; } function;
    } data;
} ast_value;

// Primary evaluation interface
ast_value* ast_evaluate(ast_node* node, ast_context* ctx);

// Statement evaluators
ast_value* ast_evaluate_assignment(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_conditional(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_loop(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_function_def(ast_node* node, ast_context* ctx);

// Expression evaluators
ast_value* ast_evaluate_binary_op(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_unary_op(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_function_call(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_variable_ref(ast_node* node, ast_context* ctx);
ast_value* ast_evaluate_array_access(ast_node* node, ast_context* ctx);

// Value operations
ast_value* ast_value_add(ast_value* left, ast_value* right);
ast_value* ast_value_multiply(ast_value* left, ast_value* right);
ast_value* ast_value_compare_ge(ast_value* left, ast_value* right);
char* ast_value_to_string(ast_value* value);
```

### Evaluation Context:

```c
typedef struct ast_context {
    store* variables;           // Variable storage (from processor)
    store* functions;           // User-defined functions
    store* modules;            // Imported modules
    char* output_buffer;       // For building output string
    size_t output_size;        // Buffer size
    size_t output_pos;         // Current position
    bool return_flag;          // Function return handling
    ast_value* return_value;   // Return value
} ast_context;
```

## Integration Architecture

### Replace Fake Implementation:

```c
// Current FAKE implementation (native_xmd_consolidated.c:817)
char* ast_process_xmd_content(const char* input, store* variables) {
    // FAKE: Just calls string parser
    processor_context ctx = {.variables = variables};
    return xmd_dispatch_process(input, &ctx);
}

// NEW REAL implementation
char* ast_process_xmd_content(const char* input, store* variables) {
    // Parse source to AST
    ast_node* program = ast_parse_program(input);
    if (!program) {
        return xmd_strdup("Parse error");
    }
    
    // Create evaluation context
    ast_context ctx = {
        .variables = variables,
        .functions = store_create(),
        .modules = store_create(),
        .output_buffer = xmd_malloc(4096),
        .output_size = 4096,
        .output_pos = 0
    };
    
    // Evaluate AST
    ast_value* result = ast_evaluate(program, &ctx);
    
    // Convert to string output
    char* output;
    if (ctx.output_pos > 0) {
        // Use accumulated output buffer
        ctx.output_buffer[ctx.output_pos] = '\0';
        output = xmd_strdup(ctx.output_buffer);
    } else if (result) {
        // Use final expression value
        output = ast_value_to_string(result);
    } else {
        output = xmd_strdup("");
    }
    
    // Cleanup
    ast_free(program);
    ast_value_free(result);
    store_destroy(ctx.functions);
    store_destroy(ctx.modules);
    free(ctx.output_buffer);
    
    return output;
}
```

## Implementation Phases

### Phase 1: Basic Expressions (Week 1)
- ✅ Mathematical expressions: `2 + 3 * 4`
- ✅ Variable assignment: `set result 14`
- ✅ Variable substitution: `{{result}}`

### Phase 2: Control Flow (Week 2)
- ✅ Conditionals: `if score >= 90; return "Excellent"`
- ✅ Basic loops: `for i in 1..5; print i`

### Phase 3: Functions (Week 3)
- ✅ Function definitions: `function greet name; return "Hello " + name`
- ✅ Function calls: `{{greet("Alice")}}`

### Phase 4: Advanced Features (Week 4)
- ✅ Arrays: `set items 1, 2, 3`
- ✅ Objects: `set user name "Alice", age 30`
- ✅ Full Genesis language compliance

## Testing Strategy

Each phase must pass comprehensive tests:

```xmd
// Phase 1 tests
set x 10
set y 20
set result x + y * 2
print "Result: {{result}}"  // Should output: Result: 50

// Phase 2 tests
if result >= 40
    print "High value"
else
    print "Low value"
// Should output: High value

// Phase 3 tests
function calculate a b
    return a * b + 10

set value calculate(5, 6)
print "Calculated: {{value}}"  // Should output: Calculated: 40

// Phase 4 tests
set numbers 1, 2, 3, 4, 5
for num in numbers
    print "Number: {{num}}"
// Should output: Number: 1, Number: 2, etc.
```

## Success Metrics

- ✅ All Genesis language features working
- ✅ Backward compatibility with current templating
- ✅ Performance acceptable for typical XMD files
- ✅ Error messages helpful for debugging
- ✅ Memory management leak-free

This architecture transforms XMD from a templating engine into the full programming language Genesis envisioned.