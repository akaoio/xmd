# Advanced XMD Language Features Architecture

## Phase 1: Functions & Classes Implementation

### Current Status: FOUNDATION COMPLETE ✅
- **Mathematical Evaluation**: Working (`set result 2 + 3` → 5)
- **Conditional Execution**: Working (`if score = 100 then print "Perfect!"`)
- **Variable System**: Complete storage and substitution
- **Genesis Syntax**: Fully compliant (`=` comparison, `set` assignment)

## Functions Implementation Guide

### 1. Function Definition Parser
**Target Syntax**: `function greet name`

```c
// In ast_parse_statement():
case TOKEN_FUNCTION:
    return ast_parse_function_definition();

ast_node* ast_parse_function_definition() {
    // function greet name age
    advance_token(); // skip "function"
    
    char* function_name = parse_identifier();
    
    // Parse space-separated parameters (no parentheses!)
    parameter_list* params = NULL;
    while (!at_end_of_line() && current_token_type() == TOKEN_IDENTIFIER) {
        add_parameter(&params, parse_identifier());
    }
    
    // Parse function body (indented block)
    ast_node* body = parse_indented_block();
    
    return ast_create_function_def(function_name, params, body);
}
```

### 2. Function Call Parser  
**Target Syntax**: `greet "Alice"`

```c
// In ast_parse_statement():
if (is_function_call(current_token)) {
    return ast_parse_function_call();
}

ast_node* ast_parse_function_call() {
    // greet "Alice" 30
    char* function_name = parse_identifier();
    
    // Parse space-separated arguments (no parentheses!)
    argument_list* args = NULL;
    while (!at_end_of_line()) {
        ast_node* arg = ast_parse_expression();
        add_argument(&args, arg);
    }
    
    return ast_create_function_call(function_name, args);
}
```

### 3. Function Evaluation
```c
case AST_FUNCTION_DEF:
    // Store function in function table
    store_function(context->functions, node->name, node);
    return ast_value_create_null(); // No output for definition
    
case AST_FUNCTION_CALL:
    // Look up function
    ast_node* func_def = get_function(context->functions, node->name);
    if (!func_def) return ast_value_create_null();
    
    // Create new scope with parameters
    evaluation_context* func_context = create_function_context(context);
    bind_parameters(func_context, func_def->parameters, node->arguments);
    
    // Execute function body
    ast_value* result = ast_evaluate_statement(func_def->body, func_context);
    
    // Clean up and return
    free_context(func_context);
    return result;
```

## Classes Implementation Guide

### 1. Class Definition Parser
**Target Syntax**: 
```xmd
class Animal
    constructor name
        set self.name name
    
    speak
        return self.name + " makes a sound"
```

```c
ast_node* ast_parse_class_definition() {
    advance_token(); // skip "class"
    
    char* class_name = parse_identifier();
    char* parent_class = NULL;
    
    // Check for inheritance: class Dog extends Animal
    if (current_token_equals("extends")) {
        advance_token(); // skip "extends"
        parent_class = parse_identifier();
    }
    
    // Parse class body (constructor + methods)
    method_list* methods = NULL;
    ast_node* constructor = NULL;
    
    while (in_class_body()) {
        if (current_token_equals("constructor")) {
            constructor = parse_constructor();
        } else {
            ast_node* method = parse_method();
            add_method(&methods, method);
        }
    }
    
    return ast_create_class_def(class_name, parent_class, constructor, methods);
}
```

### 2. Object Creation and Method Calls
```c
// Object instantiation: Dog "Buddy" "Golden"
case AST_CLASS_INSTANTIATION:
    class_def* class = get_class(context->classes, node->class_name);
    object_instance* obj = create_object(class);
    
    // Call constructor with arguments
    if (class->constructor) {
        call_constructor(obj, class->constructor, node->arguments);
    }
    
    return ast_value_create_object(obj);

// Method calls: obj.speak
case AST_METHOD_CALL:
    object_instance* obj = get_object(context, node->object_name);
    method_def* method = get_method(obj->class, node->method_name);
    
    // Create method context with 'self' reference
    evaluation_context* method_context = create_method_context(context, obj);
    
    return ast_evaluate_statement(method->body, method_context);
```

## Arrays & Objects Implementation Guide

### 1. Array Syntax Parser
**Target Syntax**: `set scores 1, 2, 3`

```c
ast_node* ast_parse_array_assignment() {
    // set scores 1, 2, 3
    advance_token(); // skip "set"
    char* var_name = parse_identifier();
    
    // Parse comma-separated values
    array_elements* elements = NULL;
    do {
        ast_node* element = ast_parse_expression();
        add_element(&elements, element);
    } while (consume_comma());
    
    return ast_create_array_assignment(var_name, elements);
}
```

### 2. Object Syntax Parser  
**Target Syntax**: `set user name "Alice", age 30, active true`

```c
ast_node* ast_parse_object_assignment() {
    // set user name "Alice", age 30, active true
    advance_token(); // skip "set"
    char* var_name = parse_identifier();
    
    // Parse key-value pairs (no colons!)
    object_properties* props = NULL;
    while (!at_end_of_line()) {
        char* key = parse_identifier();
        ast_node* value = ast_parse_expression();
        add_property(&props, key, value);
        
        if (!consume_comma()) break;
    }
    
    return ast_create_object_assignment(var_name, props);
}
```

## Implementation Priority Order

### Phase 1 (Immediate - Parallel):
1. **Developer2**: Functions (definition + calls)
2. **Developer**: Enhanced loops (range syntax, break/continue)

### Phase 2 (Sequential):  
3. **Architect**: Arrays & Objects architecture
4. **Developer2**: Classes (after functions complete)

### Phase 3 (Advanced):
5. **DevOps**: File I/O and imports
6. **Tester**: String operations and regex

## Testing Strategy

### Function Tests:
```xmd
function add a b
    return a + b

set result add 5 3
{{result}}  // Should output: 8
```

### Class Tests:
```xmd
class Dog
    constructor name
        set self.name name
    
    speak
        return self.name + " says woof!"

set buddy Dog "Buddy"
{{buddy.speak}}  // Should output: Buddy says woof!
```

### Array Tests:
```xmd
set numbers 1, 2, 3, 4, 5
{{numbers[0]}}  // Should output: 1
```

## Architecture Notes

1. **Function Scope**: Create isolated contexts for function execution
2. **Class Inheritance**: Support `extends` keyword for inheritance chains  
3. **Memory Management**: Proper cleanup for objects and arrays
4. **Genesis Compliance**: Maintain space-separated syntax throughout
5. **Self Reference**: Implement `self` keyword for object methods

This builds on the solid evaluation engine foundation to create Genesis's complete XMD programming language vision!