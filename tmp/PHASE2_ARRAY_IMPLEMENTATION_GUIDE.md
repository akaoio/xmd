# Phase 2: Array Implementation Step-by-Step Guide

## Implementation Order

### Step 1: Extend AST Value Types
**File**: `include/ast_node.h`

Add new value types and structures:
```c
// Add to ast_value_type enum
typedef enum {
    AST_VALUE_NULL,
    AST_VALUE_NUMBER,
    AST_VALUE_STRING,
    AST_VALUE_BOOLEAN,
    AST_VALUE_ARRAY,    // ADD THIS
    AST_VALUE_OBJECT    // ADD THIS
} ast_value_type;

// Add array structure
typedef struct {
    struct ast_value** elements;
    size_t count;
    size_t capacity;
} array_value;

// Add object property structure  
typedef struct object_property {
    char* key;
    struct ast_value* value;
    struct object_property* next;
} object_property;

// Add object structure
typedef struct {
    object_property* properties;
    size_t count;
} object_value;

// Update ast_value union
typedef struct ast_value {
    ast_value_type type;
    union {
        double number;
        char* string;
        bool boolean;
        array_value array;     // ADD THIS
        object_value object;   // ADD THIS
    } data;
} ast_value;
```

### Step 2: Add AST Node Types
**File**: `include/ast_node.h`

```c
// Add to ast_node_type enum
typedef enum {
    // ... existing types ...
    AST_ARRAY_ASSIGNMENT,   // ADD THIS
    AST_ARRAY_ACCESS,       // ADD THIS
    AST_OBJECT_ASSIGNMENT,  // ADD THIS
    AST_PROPERTY_ACCESS,    // ADD THIS
    AST_MULTIPLE_ASSIGNMENT // ADD THIS
} ast_node_type;

// Add array assignment data
typedef struct {
    char* var_name;
    struct ast_node** elements;
    size_t element_count;
} array_assignment_data;

// Add object assignment data
typedef struct {
    char* var_name;
    object_property* properties;
} object_assignment_data;

// Add array access data
typedef struct {
    char* array_name;
    struct ast_node* index;
} array_access_data;

// Add property access data
typedef struct {
    char* object_name;
    char* property_name;
} property_access_data;
```

### Step 3: Array Value Creation Functions
**File**: `src/ast_consolidated.c`

```c
// Array value creation
ast_value* ast_value_create_array(array_value array) {
    ast_value* value = calloc(1, sizeof(ast_value));
    value->type = AST_VALUE_ARRAY;
    value->data.array = array;
    return value;
}

// Array element access
ast_value* ast_array_get_element(ast_value* array_val, size_t index) {
    if (!array_val || array_val->type != AST_VALUE_ARRAY) {
        return ast_value_create_null();
    }
    
    if (index >= array_val->data.array.count) {
        return ast_value_create_null();
    }
    
    return ast_value_copy(array_val->data.array.elements[index]);
}

// Array element assignment
void ast_array_set_element(ast_value* array_val, size_t index, ast_value* value) {
    if (!array_val || array_val->type != AST_VALUE_ARRAY) return;
    
    // Expand array if needed
    if (index >= array_val->data.array.capacity) {
        size_t new_capacity = index + 1;
        array_val->data.array.elements = realloc(
            array_val->data.array.elements,
            new_capacity * sizeof(ast_value*)
        );
        array_val->data.array.capacity = new_capacity;
    }
    
    // Free old value if exists
    if (index < array_val->data.array.count && 
        array_val->data.array.elements[index]) {
        ast_value_free(array_val->data.array.elements[index]);
    }
    
    array_val->data.array.elements[index] = ast_value_copy(value);
    
    // Update count
    if (index >= array_val->data.array.count) {
        array_val->data.array.count = index + 1;
    }
}
```

### Step 4: Array Assignment Parser
**File**: `src/ast_consolidated.c`

```c
// Parse array assignment: set scores 1, 2, 3
ast_node* ast_parse_array_assignment() {
    // Skip "set" token - already consumed
    char* var_name = ast_strdup(current_token()->value);
    advance_token();
    
    // Count elements first
    size_t element_count = 0;
    lexer_state saved_state = save_lexer_state();
    
    do {
        if (at_end_of_line()) break;
        skip_expression();
        element_count++;
    } while (consume_comma());
    
    restore_lexer_state(saved_state);
    
    // Allocate element array
    ast_node** elements = calloc(element_count, sizeof(ast_node*));
    
    // Parse elements
    size_t i = 0;
    do {
        if (at_end_of_line()) break;
        elements[i] = ast_parse_expression();
        i++;
    } while (consume_comma() && i < element_count);
    
    // Create array assignment node
    ast_node* node = calloc(1, sizeof(ast_node));
    node->type = AST_ARRAY_ASSIGNMENT;
    node->data.array_assignment.var_name = var_name;
    node->data.array_assignment.elements = elements;
    node->data.array_assignment.element_count = i;
    
    return node;
}

// Detect if set statement is array assignment
bool is_array_assignment() {
    // Look ahead to see if we have comma-separated values
    lexer_state saved = save_lexer_state();
    
    advance_token(); // skip variable name
    skip_expression(); // skip first value
    
    bool has_comma = current_token_equals(",");
    
    restore_lexer_state(saved);
    return has_comma;
}
```

### Step 5: Array Access Parser  
**File**: `src/ast_consolidated.c`

```c
// Parse array access: scores[0]
ast_node* ast_parse_array_access(char* array_name) {
    // array_name already parsed, current token should be "["
    consume_token("[");
    
    ast_node* index = ast_parse_expression();
    
    if (!consume_token("]")) {
        parser_error("Expected ']' after array index");
        return NULL;
    }
    
    ast_node* node = calloc(1, sizeof(ast_node));
    node->type = AST_ARRAY_ACCESS;
    node->data.array_access.array_name = ast_strdup(array_name);
    node->data.array_access.index = index;
    
    return node;
}

// Update identifier parsing to handle array access
ast_node* ast_parse_identifier_or_access() {
    char* name = ast_strdup(current_token()->value);
    advance_token();
    
    // Check for array access
    if (current_token_equals("[")) {
        return ast_parse_array_access(name);
    }
    
    // Regular identifier
    ast_node* node = calloc(1, sizeof(ast_node));
    node->type = AST_IDENTIFIER;
    node->data.identifier.name = name;
    return node;
}
```

### Step 6: Array Evaluation
**File**: `src/ast_consolidated.c`

```c
// Update ast_evaluate_statement to handle arrays
ast_value* ast_evaluate_statement(ast_node* node, evaluation_context* context) {
    switch (node->type) {
        // ... existing cases ...
        
        case AST_ARRAY_ASSIGNMENT: {
            // Create array value
            array_value array = {0};
            array.capacity = node->data.array_assignment.element_count;
            array.elements = calloc(array.capacity, sizeof(ast_value*));
            
            // Evaluate each element
            for (size_t i = 0; i < node->data.array_assignment.element_count; i++) {
                array.elements[i] = ast_evaluate_expression(
                    node->data.array_assignment.elements[i], context);
                if (array.elements[i]) {
                    array.count++;
                }
            }
            
            // Store in variables as array type
            ast_value* array_val = ast_value_create_array(array);
            variable* var = variable_create_from_ast_value(array_val);
            store_set(context->variables, 
                     node->data.array_assignment.var_name, var);
            
            return ast_value_create_null(); // No output for assignment
        }
        
        case AST_ARRAY_ACCESS: {
            // Get array from variables
            variable* var = store_get(context->variables, 
                                    node->data.array_access.array_name);
            if (!var || var->type != VAR_ARRAY) {
                return ast_value_create_null();
            }
            
            // Evaluate index
            ast_value* index_val = ast_evaluate_expression(
                node->data.array_access.index, context);
            int index = (int)ast_value_to_number(index_val);
            ast_value_free(index_val);
            
            // Bounds checking
            if (index < 0 || index >= var->value.array.count) {
                return ast_value_create_null();
            }
            
            return ast_value_copy(var->value.array.elements[index]);
        }
        
        // ... other cases ...
    }
}
```

### Step 7: Update Parser Integration
**File**: `src/ast_consolidated.c`

```c
// Update ast_parse_statement to handle array assignments
ast_node* ast_parse_statement() {
    if (current_token_equals("set")) {
        advance_token();
        
        // Check if it's array assignment
        if (is_array_assignment()) {
            return ast_parse_array_assignment();
        }
        
        // Regular assignment
        return ast_parse_assignment_simple();
    }
    
    // ... other statement types ...
}

// Update ast_parse_primary to handle array access
ast_node* ast_parse_primary() {
    if (current_token_type() == TOKEN_IDENTIFIER) {
        return ast_parse_identifier_or_access();
    }
    
    // ... other primary expressions ...
}
```

### Step 8: Memory Management
**File**: `src/ast_consolidated.c`

```c
// Update ast_free to handle arrays
void ast_free(ast_node* node) {
    if (!node) return;
    
    switch (node->type) {
        // ... existing cases ...
        
        case AST_ARRAY_ASSIGNMENT:
            free(node->data.array_assignment.var_name);
            for (size_t i = 0; i < node->data.array_assignment.element_count; i++) {
                ast_free(node->data.array_assignment.elements[i]);
            }
            free(node->data.array_assignment.elements);
            break;
            
        case AST_ARRAY_ACCESS:
            free(node->data.array_access.array_name);
            ast_free(node->data.array_access.index);
            break;
            
        // ... other cases ...
    }
    
    free(node);
}

// Update ast_value_free to handle arrays
void ast_value_free(ast_value* value) {
    if (!value) return;
    
    switch (value->type) {
        // ... existing cases ...
        
        case AST_VALUE_ARRAY:
            for (size_t i = 0; i < value->data.array.count; i++) {
                ast_value_free(value->data.array.elements[i]);
            }
            free(value->data.array.elements);
            break;
            
        // ... other cases ...
    }
    
    free(value);
}
```

### Step 9: Testing Implementation
Create test file: `test_arrays.xmd`

```xmd
# Basic array assignment
set numbers 1, 2, 3, 4, 5
{{numbers[0]}}
{{numbers[2]}}
{{numbers[4]}}

# Mixed type array
set mixed 42, "hello", true
{{mixed[0]}}
{{mixed[1]}} 
{{mixed[2]}}

# Array with expressions
set x 10
set y 20
set calculated x + 5, y * 2, x + y
{{calculated[0]}}
{{calculated[1]}}
{{calculated[2]}}
```

Expected output:
```
1
3
5
42
hello
true
15
40
30
```

## Implementation Notes

1. **Start Simple**: Implement basic array assignment and access first
2. **Test Incrementally**: Test each step before moving to next
3. **Memory Safety**: Ensure proper cleanup for all array operations
4. **Bounds Checking**: Always validate array indices
5. **Type Safety**: Check variable types before array operations
6. **Genesis Compliance**: No `[]` in assignment syntax, only in access

This provides a complete step-by-step implementation guide for Phase 2 arrays!