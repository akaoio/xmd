# Array Parser Fix Guide - Architect Emergency Response

## Problem Analysis

The current `ast_parse_expression_simple` function has a critical flaw when parsing arrays with quoted strings:

```xmd
set names "Alice", "Bob", "Charlie"  # FAILS - only parses "Alice"
set nums 1, 2, 3                      # WORKS - parses all numbers
```

## Root Cause

In `ast_parse_expression_simple`, the parser doesn't properly handle quoted strings within comma-separated lists. It treats the first quoted string as a complete expression and ignores the rest.

## Solution Design

### Enhanced Expression Parser

```c
ast_node* ast_parse_expression_simple(const char** pos) {
    const char* start = *pos;
    
    // Skip whitespace
    while (*start && isspace(*start)) start++;
    
    // Check if this is an array (has commas outside quotes)
    bool has_comma = false;
    bool in_quotes = false;
    const char* scan = start;
    
    while (*scan && *scan != '\n') {
        if (*scan == '"') {
            in_quotes = !in_quotes;
        } else if (*scan == ',' && !in_quotes) {
            has_comma = true;
            break;
        }
        scan++;
    }
    
    if (has_comma) {
        // Parse as array
        source_location loc = {1, 1, "input"};
        ast_node* array = ast_create_array_literal(loc);
        
        // Parse comma-separated elements
        while (*start && *start != '\n') {
            // Skip whitespace
            while (*start && isspace(*start)) start++;
            if (!*start || *start == '\n') break;
            
            // Parse one element
            ast_node* element = NULL;
            
            if (*start == '"') {
                // Parse quoted string
                start++; // Skip opening quote
                const char* str_start = start;
                while (*start && *start != '"') start++;
                
                if (*start == '"') {
                    size_t len = start - str_start;
                    char* str = xmd_malloc(len + 1);
                    strncpy(str, str_start, len);
                    str[len] = '\0';
                    
                    element = ast_create_string_literal(str, loc);
                    free(str);
                    
                    start++; // Skip closing quote
                }
            } else if (isdigit(*start) || *start == '-') {
                // Parse number
                char* end;
                double val = strtod(start, &end);
                element = ast_create_number_literal(val, loc);
                start = end;
            } else if (strncmp(start, "true", 4) == 0 || strncmp(start, "false", 5) == 0) {
                // Parse boolean
                bool val = (strncmp(start, "true", 4) == 0);
                element = ast_create_boolean_literal(val, loc);
                start += val ? 4 : 5;
            } else {
                // Parse identifier
                const char* id_start = start;
                while (*start && (isalnum(*start) || *start == '_')) start++;
                
                size_t len = start - id_start;
                if (len > 0) {
                    char* id = xmd_malloc(len + 1);
                    strncpy(id, id_start, len);
                    id[len] = '\0';
                    
                    element = ast_create_identifier(id, loc);
                    free(id);
                }
            }
            
            if (element) {
                ast_add_element(array, element);
            }
            
            // Skip whitespace and comma
            while (*start && isspace(*start)) start++;
            if (*start == ',') {
                start++;
                while (*start && isspace(*start)) start++;
            }
        }
        
        *pos = start;
        return array;
    }
    
    // Not an array - parse single expression (existing code)
    // ... rest of the function
}
```

## Array Access Parser

For `scores[0]` syntax:

```c
// In ast_parse_primary or after identifier parsing:
if (tok->type == TOKEN_IDENTIFIER) {
    ast_node* id = ast_create_identifier(tok->value, loc);
    parser_advance_token(parser);
    
    // Check for array access
    if (parser->current_token && parser->current_token->value && 
        strcmp(parser->current_token->value, "[") == 0) {
        parser_advance_token(parser); // Skip '['
        
        ast_node* index = ast_parse_expression(parser);
        
        if (parser->current_token && strcmp(parser->current_token->value, "]") == 0) {
            parser_advance_token(parser); // Skip ']'
            return ast_create_array_access(id, index, loc);
        }
    }
    
    return id;
}
```

## Object Parser Design

For Genesis comma-based object syntax:

```xmd
set user name "Alice", age 30, active true
```

This requires detecting key-value pairs:

```c
// Detect object: identifier followed by value (not comma)
bool is_object = false;
const char* scan = start;
while (*scan && *scan != '\n' && *scan != ',') {
    if (isalpha(*scan)) {
        // Skip identifier
        while (*scan && (isalnum(*scan) || *scan == '_')) scan++;
        // Skip whitespace
        while (*scan && isspace(*scan)) scan++;
        // Check if followed by value (not comma or newline)
        if (*scan && *scan != ',' && *scan != '\n') {
            is_object = true;
            break;
        }
    }
    scan++;
}
```

## Testing Strategy

1. Test string arrays: `set names "Alice", "Bob", "Charlie"`
2. Test mixed arrays: `set data 42, "hello", true, 3.14`
3. Test array access: `print names[0]` should output "Alice"
4. Test objects: `set user name "Alice", age 30`
5. Test object access: `print user.name` should output "Alice"

## Genesis Compliance Checklist

- ✅ Arrays use comma separation, no brackets
- ✅ Objects use key-value pairs, no braces
- ✅ Minimal syntax throughout
- ✅ Compatible with existing variable system