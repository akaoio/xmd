# Arrays & Objects Architecture Implementation Guide

## Current Status Analysis

### ✅ Foundation Complete (Phase 1):
- **Functions**: Developer2 implementing (`function greet name`, `greet "Alice"`)
- **Control Flow**: Developer completed (ranges, break/continue, elif/else)  
- **Build System**: 100% success (35,800 byte binary)
- **Evaluation Engine**: Mathematical expressions and conditionals working
- **Genesis Syntax**: Fully compliant (`=` comparison, `set` assignment)

### 🎯 Phase 2 Assignment: Arrays & Objects Architecture

## Genesis Specification Analysis

### Arrays Syntax (from leader.md):
```xmd
# Inline Arrays (Preferred)
set scores 1, 2, 3

# Equivalent to:
[1, 2, 3]

# Multiline Arrays
set items
    "pen",
    "book", 
    "lamp",

# Must use commas , to separate elements
# Indentation required in multiline format
```

### Objects Syntax (from leader.md):
```xmd
# Inline Objects (Preferred)  
set user name "Alice", age 30, active true

# Equivalent to:
{ "name": "Alice", "age": 30, "active": true }

# Multiline Objects
set config
    debug true,
    retries 3,
    timeout 1000,

# Each entry is key value pair
# No colons :, no curly braces {}
# Comma , required between entries
```

### Important Distinction (from leader.md):
```xmd
set a 1, b 2, c "3"  # Sets multiple variables inline
# vs
set user name "Alice", age 30  # Sets one object variable
```

## Array Implementation Architecture

### 1. Array Value Type
```c
// In ast_node.h - Add array value type
typedef struct {
    ast_value** elements;
    size_t count;
    size_t capacity;
} array_value;

// In ast_value union
typedef struct ast_value {
    ast_value_type type;
    union {
        double number;
        char* string;
        bool boolean;
        array_value array;     // Add this
        object_value object;   // Add this
    } data;
} ast_value;

// Add new value types
typedef enum {
    AST_VALUE_NULL,
    AST_VALUE_NUMBER,
    AST_VALUE_STRING, 
    AST_VALUE_BOOLEAN,
    AST_VALUE_ARRAY,    // Add this
    AST_VALUE_OBJECT    // Add this
} ast_value_type;
```

### 2. Array Assignment Parser
```c
// Parse: set scores 1, 2, 3
ast_node* ast_parse_array_assignment() {
    advance_token(); // skip "set"
    char* var_name = parse_identifier();
    
    // Check for multiline array
    if (current_line_empty()) {
        return ast_parse_multiline_array(var_name);
    }
    
    // Parse inline comma-separated values
    array_elements* elements = NULL;
    do {
        ast_node* element = ast_parse_expression();
        add_array_element(&elements, element);
    } while (consume_comma());
    
    return ast_create_array_assignment(var_name, elements);
}

// Parse multiline array with indentation
ast_node* ast_parse_multiline_array(char* var_name) {
    array_elements* elements = NULL;
    
    while (is_indented_line()) {
        ast_node* element = ast_parse_expression();
        add_array_element(&elements, element);
        
        if (!consume_comma() && !at_end_of_line()) {
            parser_error("Expected comma in multiline array");
        }
    }
    
    return ast_create_array_assignment(var_name, elements);
}
```

### 3. Array Access Parser
```c
// Parse: scores[0] or get scores 0
ast_node* ast_parse_array_access() {
    char* array_name = parse_identifier();
    
    if (consume_token("[")) {
        // Square bracket syntax: scores[0]
        ast_node* index = ast_parse_expression();
        consume_token("]");
        return ast_create_array_access(array_name, index);
    }
    
    return ast_create_identifier(array_name);
}

// Alternative get syntax: get matrix 1 2 (for multidimensional)
ast_node* ast_parse_get_statement() {
    advance_token(); // skip "get"
    char* array_name = parse_identifier();
    
    // Parse multiple indices
    index_list* indices = NULL;
    while (!at_end_of_line()) {
        ast_node* index = ast_parse_expression();
        add_index(&indices, index);
    }
    
    return ast_create_get_access(array_name, indices);
}
```

## Object Implementation Architecture

### 1. Object Value Type
```c
// Object property structure
typedef struct object_property {
    char* key;
    ast_value* value;
    struct object_property* next;
} object_property;

// Object value structure
typedef struct {
    object_property* properties;
    size_t count;
} object_value;
```

### 2. Object Assignment Parser
```c
// Parse: set user name "Alice", age 30, active true
ast_node* ast_parse_object_assignment() {
    advance_token(); // skip "set"
    char* var_name = parse_identifier();
    
    // Check for multiline object
    if (current_line_empty()) {
        return ast_parse_multiline_object(var_name);
    }
    
    // Parse inline key-value pairs (no colons!)
    object_properties* props = NULL;
    while (!at_end_of_line()) {
        char* key = parse_identifier();
        ast_node* value = ast_parse_expression();
        add_object_property(&props, key, value);
        
        if (!consume_comma()) break;
    }
    
    return ast_create_object_assignment(var_name, props);
}

// Distinguish between multiple variables and object
bool is_object_assignment() {
    // Look ahead to see if pattern is: key value, key value
    // vs: var value, var value (which would be multiple variables)
    
    // Heuristic: if second token after first value is identifier 
    // followed by value, it's likely an object
    return lookahead_shows_key_value_pattern();
}
```

### 3. Multiple Variable Assignment Parser
```c
// Parse: set a 1, b 2, c "3" (multiple variables)
ast_node* ast_parse_multiple_assignment() {
    advance_token(); // skip "set"
    
    assignment_list* assignments = NULL;
    do {
        char* var_name = parse_identifier();
        ast_node* value = ast_parse_expression();
        add_assignment(&assignments, var_name, value);
    } while (consume_comma());
    
    return ast_create_multiple_assignment(assignments);
}
```

## Property Access Architecture

### 1. Dot Notation Parser
```c
// Parse: user.name or user.address.city
ast_node* ast_parse_property_access() {
    char* object_name = parse_identifier();
    property_chain* chain = NULL;
    
    while (consume_token(".")) {
        char* property = parse_identifier();
        add_property_to_chain(&chain, property);
    }
    
    return ast_create_property_access(object_name, chain);
}
```

### 2. Nested Structure Support
```c
// Handle: set profile name "Linh", scores scores, active true
// where scores is another variable containing an array
ast_node* ast_parse_nested_object() {
    // When parsing value in object, check if it's a variable reference
    if (is_identifier_token()) {
        char* var_ref = parse_identifier();
        // This creates a reference to existing variable
        return ast_create_variable_reference(var_ref);
    }
    return ast_parse_expression();
}
```

## Evaluation Architecture

### 1. Array Evaluation
```c
case AST_ARRAY_ASSIGNMENT:
    // Create array value
    array_value array = {0};
    array.capacity = node->elements->count;
    array.elements = calloc(array.capacity, sizeof(ast_value*));
    
    // Evaluate each element
    for (size_t i = 0; i < node->elements->count; i++) {
        array.elements[i] = ast_evaluate_expression(
            node->elements->items[i], context);
        array.count++;
    }
    
    // Store in variables
    ast_value* array_val = ast_value_create_array(array);
    store_set(context->variables, node->var_name, 
              variable_from_ast_value(array_val));
    
    return ast_value_create_null(); // No output for assignment

case AST_ARRAY_ACCESS:
    // Get array from variables
    variable* array_var = store_get(context->variables, node->array_name);
    if (!array_var || array_var->type != VAR_ARRAY) {
        return ast_value_create_null();
    }
    
    // Evaluate index
    ast_value* index_val = ast_evaluate_expression(node->index, context);
    int index = (int)ast_value_to_number(index_val);
    
    // Bounds checking
    if (index < 0 || index >= array_var->value.array.count) {
        return ast_value_create_null();
    }
    
    return ast_value_copy(array_var->value.array.elements[index]);
```

### 2. Object Evaluation
```c
case AST_OBJECT_ASSIGNMENT:
    // Create object value
    object_value object = {0};
    
    // Evaluate each property
    for (object_property* prop = node->properties; prop; prop = prop->next) {
        ast_value* value = ast_evaluate_expression(prop->value_node, context);
        add_object_property(&object, prop->key, value);
        object.count++;
    }
    
    // Store in variables
    ast_value* obj_val = ast_value_create_object(object);
    store_set(context->variables, node->var_name,
              variable_from_ast_value(obj_val));
    
    return ast_value_create_null();

case AST_PROPERTY_ACCESS:
    // Get object from variables
    variable* obj_var = store_get(context->variables, node->object_name);
    if (!obj_var || obj_var->type != VAR_OBJECT) {
        return ast_value_create_null();
    }
    
    // Walk property chain
    ast_value* current = ast_value_from_variable(obj_var);
    for (property_chain* prop = node->chain; prop; prop = prop->next) {
        current = get_object_property(current, prop->name);
        if (!current) return ast_value_create_null();
    }
    
    return current;
```

## Testing Strategy

### Array Tests:
```xmd
# Basic array
set numbers 1, 2, 3, 4, 5
{{numbers[0]}}  # Should output: 1
{{numbers[4]}}  # Should output: 5

# Multiline array
set items
    "apple",
    "banana", 
    "cherry",
{{items[1]}}    # Should output: banana

# Mixed types
set mixed 42, "hello", true
{{mixed[0]}} {{mixed[1]}} {{mixed[2]}}  # Should output: 42 hello true
```

### Object Tests:
```xmd
# Basic object
set user name "Alice", age 30, active true
{{user.name}}   # Should output: Alice
{{user.age}}    # Should output: 30

# Nested object
set scores 95, 87, 92
set student name "Bob", scores scores, grade "A"
{{student.name}}     # Should output: Bob
{{student.scores[0]}} # Should output: 95

# Multiple variables (NOT object)
set a 1, b 2, c 3
{{a}} {{b}} {{c}}    # Should output: 1 2 3
```

## Memory Management

### Array Cleanup:
```c
void ast_value_free_array(array_value* array) {
    for (size_t i = 0; i < array->count; i++) {
        ast_value_free(array->elements[i]);
    }
    free(array->elements);
    array->elements = NULL;
    array->count = 0;
    array->capacity = 0;
}
```

### Object Cleanup:
```c
void ast_value_free_object(object_value* object) {
    object_property* prop = object->properties;
    while (prop) {
        object_property* next = prop->next;
        free(prop->key);
        ast_value_free(prop->value);
        free(prop);
        prop = next;
    }
    object->properties = NULL;
    object->count = 0;
}
```

## Integration Notes

1. **Genesis Syntax Compliance**: No brackets `[]` or braces `{}` in definitions, only in access
2. **Comma Requirements**: All array and object entries must be comma-separated
3. **Variable vs Object**: Clear distinction between multiple variable assignment and object creation
4. **Indentation**: Multiline structures require proper indentation
5. **Type Safety**: Proper type checking for array access and property access
6. **Memory Safety**: Complete cleanup for nested structures

This architecture supports Genesis's minimal, comma-based syntax while providing full array and object functionality!