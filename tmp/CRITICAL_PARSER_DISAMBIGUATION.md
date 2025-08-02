# Critical Parser Disambiguation - Arrays vs Objects vs Multiple Variables

## The Genesis Design Challenge

From leader.md, we have THREE different uses of comma-separated syntax after `set`:

### 1. Array Creation
```xmd
set scores 1, 2, 3
// Creates: scores = [1, 2, 3]
```

### 2. Object Creation  
```xmd
set user name "Alice", age 30, active true
// Creates: user = {name: "Alice", age: 30, active: true}
```

### 3. Multiple Variable Assignment
```xmd
set a 1, b 2, c "3"
// Creates: a = 1, b = 2, c = "3"
```

## Parser Disambiguation Rules

### Rule 1: Multiple Variables
If the pattern is: `set identifier value, identifier value, ...`
Then it's multiple variable assignment.

### Rule 2: Object Creation
If the pattern is: `set identifier key value, key value, ...`
Where keys are identifiers not followed by assignment operator.

### Rule 3: Array Creation
If the pattern is: `set identifier value, value, value, ...`
Where values are not preceded by identifiers.

## Detection Algorithm

```c
// After parsing "set identifier"
// Peek at the pattern after first value:

1. If next token after value is comma:
   a. If token after comma is an identifier:
      - If identifier is followed by another identifier -> OBJECT
      - If identifier is followed by a value -> MULTIPLE VARS
   b. If token after comma is a value -> ARRAY

2. Special case for multiline:
   - If newline with indentation -> multiline array/object
   - Check first indented line for pattern
```

## Examples with Parse Trees

### Array: `set scores 1, 2, 3`
```
set -> scores -> 1 -> , -> 2 -> , -> 3
                 ^         ^         ^
                value    value    value
Result: ARRAY
```

### Object: `set user name "Alice", age 30`
```
set -> user -> name -> "Alice" -> , -> age -> 30
               ^        ^               ^      ^
              key     value           key   value
Result: OBJECT
```

### Multiple: `set a 1, b 2, c "3"`
```
set -> a -> 1 -> , -> b -> 2 -> , -> c -> "3"
       ^    ^         ^    ^         ^     ^
      var  val       var  val       var   val
Result: MULTIPLE VARIABLES
```

## Current Implementation Issue

My current array implementation assumes ALL comma-separated values create an array. This is WRONG according to Genesis design.

The parser needs to:
1. Look ahead after the first value
2. Determine which of the three patterns we're parsing
3. Create appropriate AST nodes

## Corrected Parser Flow

```c
ast_node* ast_parse_set_statement(const char** pos) {
    // Skip "set"
    // Parse identifier
    
    // Look ahead to determine pattern:
    if (is_multiple_variable_pattern()) {
        return parse_multiple_assignments();
    } else if (is_object_pattern()) {
        return parse_object_creation();
    } else {
        return parse_array_creation();
    }
}
```

This is a critical design insight that affects the entire parser architecture!